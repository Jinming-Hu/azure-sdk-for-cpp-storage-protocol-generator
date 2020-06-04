#!/usr/bin/env python3

import subprocess
import pathlib
import re
import ruamel.yaml
import toposort

import code_template
from code_template import models_cache


class class_definition:
    def __init__(self, class_name, class_type):
        self.name = class_name
        self.type = class_type
        self.noexport = False
        self.member = []
        # only for struct
        self.member_type = []
        self.member_default_value = []
        # only for enum
        self.member_literal = []
        self.member_comment = []
        self.dependency = set()

    def add_dependency(self, type_name):
        if type_name is None:
            return

        types = list(filter(None, re.split("<|>|,| |\*", type_name)))

        for t in types:
            if t in [None, "bool", "char", "int", "unsigned int", "long", "unsigned long", "long long", "unsigned long long",
                     "int8_t", "uint8_t", "int16_t", "uint16_t", "int32_t", "uint32_t", "int64_t", "uint64_t", "float", "double", "long double"]:
                continue
            if t.startswith("std::"):
                continue
            if t.startswith("Azure::Core::"):
                continue
            self.dependency.add(t)

    def add_member(self, name, **kwargs):
        member_type = kwargs.get("member_type", None)
        member_literal = kwargs.get("member_literal", None)
        member_comment = kwargs.get("member_comment", None)
        member_default_value = kwargs.get("member_default_value", None)

        self.member.append(name)
        self.member_type.append(member_type)
        self.member_default_value.append(member_default_value)
        self.member_literal.append(member_literal)
        self.member_comment.append(member_comment)
        self.add_dependency(member_type)

    def add_inline_class(self, other):
        self.member.extend(other.member)
        self.member_type.extend(other.member_type)
        self.member_default_value.extend(other.member_default_value)
        self.member_literal.extend(other.member_literal)
        self.member_comment.extend(other.member_comment)
        self.dependency |= other.dependency


try:
    config = ruamel.yaml.round_trip_load(open("blob.yaml"), preserve_quotes=True)
except yaml.YAMLError as e:
    print(e)


service_name = config["service_name"]
code_template.gen_service_namespace(service_name)
code_template.gen_rest_client(service_name)

export_models = {}


def get_class_definition(class_name, config_class_def=None):
    if class_name in models_cache:
        return models_cache[class_name]

    if config_class_def is None and class_name in config["Models"]:
        return get_class_definition(class_name, config["Models"][class_name])

    # Find type
    type_index = [i for i, v in enumerate(config_class_def) if next(iter(v)) == "type"]
    if len(type_index) == 0:
        class_type = "struct"
    elif len(type_index) == 1:
        index = type_index[0]
        class_type = next(iter(config_class_def[index].values()))
        del config_class_def[index]
    else:
        raise RuntimeError("multiple types of class " + class_name)

    # Find noexport
    noexport_index = [i for i, v in enumerate(config_class_def) if next(iter(v)) == "noexport"]
    if len(noexport_index) == 0:
        noexport = False
    elif len(noexport_index) == 1:
        index = noexport_index[0]
        noexport = True
        del config_class_def[index]
    else:
        raise RuntimeError("multiple noexport")

    class_def = class_definition(class_name, class_type)
    if noexport:
        class_def.noexport = True
    for i, m in enumerate(config_class_def):
        if type(m) is ruamel.yaml.comments.CommentedMap:
            member_name, member_type = next(iter(m.items()))
            if "=" in member_type:
                (member_type, member_default_value) = [i.strip() for i in member_type.split("=")]
            else:
                member_default_value = None
            member_comment = m.ca.items[member_name][2].value.strip(" \t\r\n#") if member_name in m.ca.items else None
            if member_type == "inline":
                class_def.add_inline_class(get_class_definition(member_name))
            elif class_type == "struct":
                class_def.add_member(member_name, member_type=member_type, member_comment=member_comment, member_default_value=member_default_value)
            elif class_type == "enum class":
                member_literal = member_type
                class_def.add_member(member_name, member_literal=member_literal, member_comment=member_comment, member_default_value=member_default_value)
            else:
                raise RuntimeError("unknown member type " + member_type)
        elif type(m) is str:  # This is only for enum
            member_comment = config_class_def.ca.items[i][0].value.strip(" \t\r\n#") if i < len(config_class_def.ca.items) else None
            member_name = m
            class_def.add_member(member_name, member_comment=member_comment)

    models_cache[class_name] = class_def
    return class_def


def add_export_model(class_name):
    export_models[class_name] = get_class_definition(class_name).dependency
    for d in get_class_definition(class_name).dependency:
        add_export_model(d)


for config_resource in config["Services"]:
    resource_name = next(iter(config_resource))
    code_template.gen_resource_begin(resource_name)

    for config_function in config_resource[resource_name]:
        function_name = next(iter(config_function))
        print("Processing:", resource_name, function_name)
        config_function_def = config_function[function_name]
        http_method = config_function_def["http_method"]
        http_status_code = config_function_def["http_status_code"]
        if type(http_status_code) is ruamel.yaml.comments.CommentedSeq:
            http_staus_code = list(http_status_code)
        else:
            http_status_code = [http_status_code]

        if type(config_function_def["return_type"]) is ruamel.yaml.comments.CommentedMap:
            return_type, config_return_type = next(iter(config_function_def["return_type"].items()))
            return_type_def = get_class_definition(return_type, config_return_type)
        elif type(config_function_def["return_type"]) is str:
            return_type = config_function_def["return_type"]
            return_type_def = get_class_definition(return_type)
        add_export_model(return_type)

        config_option_def = config_function_def["options"]
        option_def = class_definition(function_name + "Options", "struct")
        for m in config_option_def:
            member_name, member_type = next(iter(m.items()))
            if "=" in member_type:
                (member_type, member_default_value) = [i.strip() for i in member_type.split("=")]
            else:
                member_default_value = None
            if member_type == "inline":
                option_def.add_inline_class(get_class_definition(member_name))
            else:
                option_def.add_member(member_name, member_type=member_type, member_default_value=member_default_value)

        code_template.gen_function_option_definition(service_name, function_name, option_def)
        for d in option_def.dependency:
            add_export_model(d)

        def flatten_actions(l):
            res = []
            for i in l:
                if type(i) is ruamel.yaml.comments.CommentedSeq and len(i) and type(i[0]) is ruamel.yaml.comments.CommentedSeq:
                    res.extend(i)
                else:
                    res.append(i)
            return res

        config_request_action = flatten_actions(config_function_def["request_action"])
        code_template.gen_construct_request_function_begin(function_name)
        request_declared = False
        for action in config_request_action:
            method_to_call = getattr(code_template, "gen_" + action[0])
            args = []
            kwargs = {"optional": False, "service_name": service_name, "resource_name": resource_name, "function_name": function_name}

            for i in range(1, len(action)):
                if action[i] == "optional":
                    kwargs["optional"] = True
                elif match_res := re.match("optional\\((.*)\\)", action[i]):
                    kwargs["optional"] = True
                    kwargs["optional_value"] = match_res.group(1)
                elif match_res := re.match("default\\((.*)\\)", action[i]):
                    kwargs["default_value"] = match_res.group(1)
                elif type(action[i]) is str:
                    arg = "options"
                    arg_types = action[i].split(".")
                    arg_def = option_def
                    for j, t in enumerate(arg_types):
                        if t not in arg_def.member:
                            if j < len(arg_types) - 1:  # Not the last one
                                continue
                            else:
                                raise RuntimeError("cannot find " + action[i] + " in " + return_type)
                        arg += "." + t
                        arg_type = arg_def.member_type[arg_def.member.index(t)]
                        if arg_type in models_cache:
                            arg_def = models_cache[arg_type]
                    args.append(arg)
                    arg_def = models_cache[arg_type] if arg_type in models_cache else arg_type
                    kwargs[arg + ".type"] = arg_def
                elif type(action[i]) is ruamel.yaml.scalarstring.DoubleQuotedScalarString:
                    # maybe add const string definition
                    arg = "\"{}\"".format(action[i])
                    args.append(arg)
                    kwargs[arg + ".type"] = "std::string"  # we may need to change this to literal string to distinguish from std::string variable
                elif type(action[i]) is ruamel.yaml.scalarstring.SingleQuotedScalarString:
                    arg = "\"{}\"".format(action[i])
                    args.append(arg)
                    kwargs[arg + ".type"] = "std::string"
            if not request_declared:
                request_declared = True
                if action[0] == "add_body_code":
                    code_template.gen_request_definition(http_method, *args, **kwargs)
                elif action[0] == "add_xml_body_code":
                    method_to_call(*args, **kwargs)
                    arg = "body_buffer"
                    args.append(arg)
                    kwargs[arg + ".type"] = "std::string"
                    code_template.gen_request_definition(http_method, *args, **kwargs)
                else:
                    code_template.gen_request_definition(http_method)
                    method_to_call(*args, **kwargs)
            else:
                method_to_call(*args, **kwargs)
        code_template.gen_construct_request_function_end()

        config_response_action = flatten_actions(config_function_def["response_action"])
        code_template.gen_parse_response_function_begin(function_name, http_status_code, return_type)
        for action in config_response_action:
            method_to_call = getattr(code_template, "gen_" + action[0])
            args = []
            kwargs = {"optional": False, "service_name": service_name, "resource_name": resource_name, "function_name": function_name}

            for i in range(1, len(action)):
                if action[i] == "optional":
                    kwargs["optional"] = True
                elif type(action[i]) is str:
                    arg = "response"
                    arg_types = action[i].split(".")
                    arg_def = return_type_def
                    for j, t in enumerate(arg_types):
                        if t not in arg_def.member:
                            if j < len(arg_types) - 1:  # Not the last one
                                continue
                            else:
                                raise RuntimeError("cannot find " + action[i] + " in " + return_type)
                        arg += "." + t
                        arg_type = arg_def.member_type[arg_def.member.index(t)]
                        if arg_type in models_cache:
                            arg_def = models_cache[arg_type]
                    args.append(arg)
                    arg_def = models_cache[arg_type] if arg_type in models_cache else arg_type
                    kwargs[arg + ".type"] = arg_def
                elif type(action[i]) is ruamel.yaml.scalarstring.DoubleQuotedScalarString:
                    # maybe add const string definition
                    arg = "\"{}\"".format(action[i])
                    args.append(arg)
                    kwargs[arg + ".type"] = "std::string"
                elif type(action[i]) is ruamel.yaml.scalarstring.SingleQuotedScalarString:
                    arg = "\"{}\"".format(action[i])
                    args.append(arg)
                    kwargs[arg + ".type"] = "std::string"
            method_to_call(*args, **kwargs)
        code_template.gen_parse_response_function_end()

        code_template.gen_resource_function(function_name, return_type)

    code_template.gen_resource_end(resource_name)


for class_name in toposort.toposort_flatten(export_models):
    if models_cache[class_name].noexport:
        raise RuntimeError("Trying to export a non-export class " + class_name)
    code_template.gen_model_definition(service_name, class_name, models_cache[class_name])

output_path = pathlib.Path(config["output"])
output_path.parents[0].mkdir(parents=True, exist_ok=True)
with open(output_path, "w") as f:
    f.write(code_template.global_header)
    f.write(code_template.include_headers)
    f.write(code_template.namespace_begin)
    f.write(code_template.constant_string)
    f.write(code_template.model_definitions)
    f.write(code_template.rest_client_begin)
    f.write(code_template.main_body)
    f.write(code_template.rest_client_end)
    f.write(code_template.namespace_end)
subprocess.call(["clang-format", "-style=file", "-i", output_path])
