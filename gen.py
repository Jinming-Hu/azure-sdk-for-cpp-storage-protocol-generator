#!/usr/bin/env python3

import subprocess
import pathlib
import re
import ruamel.yaml
import toposort

import code_template
from code_template import models_cache
from code_template import HttpBodyType


class class_definition:
    def __init__(self, class_name, class_type):
        self.name = class_name
        self.type = class_type
        self.noexport = False
        self.external = False
        self.member = []
        # only for struct
        self.member_type = []
        self.member_default_value = []
        self.member_nullable = []
        # only for enum
        self.member_literal = []
        self.member_comment = []
        self.dependency = set()
        # for xml
        self.fromxml_actions = None
        self.toxml_actions = None


    def __eq__(self, other):
        if not isinstance(other, class_definition):
            return NotImplemented
        return (self.name == other.name and self.type == other.type and self.noexport == other.noexport and
               self.member == other.member and self.member_type == other.member_type and
               self.member_default_value == other.member_default_value and self.member_nullable == other.member_nullable and
               self.member_literal == other.member_literal and self.member_comment == other.member_comment and
               self.dependency == other.dependency and self.fromxml_actions == other.fromxml_actions and
               self.toxml_actions == other.toxml_actions)

    def add_dependency(self, type_name):
        if type_name is None:
            return

        types = list(filter(None, re.split("<|>|,| |\\*", type_name)))

        for t in types:
            if t in [None, "bool", "char", "int", "unsigned int", "long", "unsigned long", "long long", "unsigned long long",
                     "int8_t", "uint8_t", "int16_t", "uint16_t", "int32_t", "uint32_t", "int64_t", "uint64_t", "float", "double", "long double"]:
                continue
            if t.startswith("std::"):
                continue
            if t.startswith("Azure::"):
                continue
            if t in ["Metadata"]:
                continue
            self.dependency.add(t)

    def add_member(self, name, **kwargs):
        member_type = kwargs.get("member_type", None)
        member_literal = kwargs.get("member_literal", None)
        member_comment = kwargs.get("member_comment", None)
        member_default_value = kwargs.get("member_default_value", None)
        member_nullable = kwargs.get("member_nullable", False)

        self.member.append(name)
        self.member_type.append(member_type)
        self.member_default_value.append(member_default_value)
        self.member_nullable.append(member_nullable)
        self.member_literal.append(member_literal)
        self.member_comment.append(member_comment)
        self.add_dependency(member_type)

    def add_inline_class(self, other):
        self.member.extend(other.member)
        self.member_type.extend(other.member_type)
        self.member_default_value.extend(other.member_default_value)
        self.member_nullable.extend(other.member_nullable)
        self.member_literal.extend(other.member_literal)
        self.member_comment.extend(other.member_comment)
        self.dependency |= other.dependency
        if self.fromxml_actions is None:
            self.fromxml_actions = other.fromxml_actions
        elif other.fromxml_actions is not None:
            self.fromxml_actions.extend(other.fromxml_actions)
        if self.toxml_actions is None:
            self.toxml_actions = other.toxml_actions
        elif other.toxml_actions is not None:
            self.toxml_actions = other.toxml_actions


try:
    config = ruamel.yaml.round_trip_load(open("blob.yaml"), preserve_quotes=True)
except ruamel.yaml.YAMLError as e:
    print(e)


service_name = config["service_name"]
code_template.gen_service_namespace(service_name)
code_template.gen_rest_client(service_name)

export_models = {}


def splitq(s, sep):
    res = []
    stack = []
    stage = str()
    for c in s:
        if c == sep:
            if len(stack) == 0:
                res.append(stage)
                stage = str()
            else:
                stage += c
        else:
            stage += c
            if len(stack) != 0 and c == stack[-1]:
                stack.pop()
            elif c == "(":
                stack += ")"
            elif c == "[":
                stack += "]"
            elif c == "{":
                stack += "}"
            elif c == "<":
                stack += ">"
            elif c == "\"":
                stack += "\""
            elif c == "'":
                stack += "'"
    if len(stack) != 0:
        raise RuntimeError("unclosed pair in " + s)
    if len(stage) != 0:
        res.append(stage)
    return res


def get_class_definition(class_name, config_class_def=None):
    if config_class_def is None and class_name in models_cache:
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

    # Find external
    external_index = [i for i, v in enumerate(config_class_def) if next(iter(v)) == "external"]
    if len(external_index) == 0:
        external = False
    elif len(external_index) == 1:
        index = external_index[0]
        external = True
        del config_class_def[index]
    else:
        raise RuntimeError("multiple external")

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

    # from xml
    fromxml_index = [i for i, v in enumerate(config_class_def) if next(iter(v)) == "from_xml"]
    if len(fromxml_index) == 1:
        index = fromxml_index[0]
        fromxml_actions = next(iter(config_class_def[index].values()))
        del config_class_def[index]
    elif len(fromxml_index) > 1:
        raise RuntimeError("multiple from_xml")
    else:
        fromxml_actions = None

    # to xml
    toxml_index = [i for i, v in enumerate(config_class_def) if next(iter(v)) == "to_xml"]
    if len(toxml_index) == 1:
        index = toxml_index[0]
        toxml_actions = next(iter(config_class_def[index].values()))
        del config_class_def[index]
    elif len(toxml_index) > 1:
        raise RuntimeError("multiple to_xml")
    else:
        toxml_actions = None

    class_def = class_definition(class_name, class_type)
    class_def.fromxml_actions = fromxml_actions
    class_def.toxml_actions = toxml_actions
    if noexport:
        class_def.noexport = True
    if external:
        class_def.external = True
    for i, m in enumerate(config_class_def):
        if type(m) is ruamel.yaml.comments.CommentedMap:
            member_name, member_desc = next(iter(m.items()))

            if len(splitq(member_desc, ",")) > 1:
                member_type = splitq(member_desc, ",")[0].strip()
                for desc in [i.strip() for i in splitq(member_desc, ",")[1:]]:
                    if desc == "nullable":
                        member_nullable = True
                    else:
                        raise RuntimeError("unknown member descriptor " + desc)
            else:
                member_type = member_desc
                member_nullable = False

            if "=" in member_type:
                (member_type, member_default_value) = [i.strip() for i in member_type.split("=")]
            else:
                member_default_value = None

            member_comment = m.ca.items[member_name][2].value.strip(" \t\r\n#") if member_name in m.ca.items else None

            if member_type == "inline":
                class_def.add_inline_class(get_class_definition(member_name))
            elif class_type == "struct":
                class_def.add_member(member_name, member_type=member_type, member_comment=member_comment, member_default_value=member_default_value, member_nullable=member_nullable)
            elif class_type == "enum class" or class_type == "bitwise enum":
                member_literal = member_type
                class_def.add_member(member_name, member_literal=member_literal, member_comment=member_comment, member_default_value=member_default_value)
            else:
                raise RuntimeError("unknown member type " + member_type)
        elif type(m) is str:  # This is only for enum
            member_comment = config_class_def.ca.items[i][0].value.strip(" \t\r\n#") if i < len(config_class_def.ca.items) else None
            member_name = m
            class_def.add_member(member_name, member_comment=member_comment)

    if class_name in models_cache and models_cache[class_name] != class_def:
        raise RuntimeError("duplicate definition of " + class_name)

    models_cache[class_name] = class_def
    return class_def


def add_export_model(class_name):
    export_models[class_name] = get_class_definition(class_name).dependency
    for d in get_class_definition(class_name).dependency:
        add_export_model(d)


for c_k, c_v in config["Constants"].items():
    code_template.constants_map[c_k] = c_v


for config_resource in config["Services"]:
    resource_name = next(iter(config_resource))
    code_template.gen_resource_begin(resource_name)

    for config_function in config_resource[resource_name]:
        function_name = next(iter(config_function))
        print("Processing:", resource_name, function_name)
        config_function_def = config_function[function_name]
        separate_functions = config_function_def.get("separate_functions", False)
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

        if return_type.endswith("ResultInternal"):
            return_type = "Models::Details::" + return_type[:-8]

        if type(config_function_def["options"]) is ruamel.yaml.comments.CommentedMap:
            option_type, config_option_def = next(iter(config_function_def["options"].items()))
        else:
            raise RuntimeError("Unsupported option definition")

        option_def = class_definition(option_type, "struct")
        for m in config_option_def:
            member_name, member_desc = next(iter(m.items()))

            if member_name == "to_xml":
                toxml_actions = member_desc
                option_def.toxml_actions = toxml_actions
                continue

            if len(splitq(member_desc, ",")) > 1:
                member_type = splitq(member_desc, ",")[0].strip()
                for desc in [i.strip() for i in splitq(member_desc, ",")[1:]]:
                    if desc == "nullable":
                        member_nullable = True
                    else:
                        raise RuntimeError("unknown member descriptor " + desc)
            else:
                member_type = member_desc
                member_nullable = False

            if "=" in member_type:
                (member_type, member_default_value) = [i.strip() for i in member_type.split("=")]
            else:
                member_default_value = None
            if member_type == "inline":
                option_def.add_inline_class(get_class_definition(member_name))
            else:
                option_def.add_member(member_name, member_type=member_type, member_default_value=member_default_value, member_nullable=member_nullable)

        code_template.gen_function_option_definition(service_name, option_type, option_def)
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

        request_body_type = HttpBodyType.NoBody
        response_body_type = HttpBodyType.NoBody
        config_request_action = flatten_actions(config_function_def["request_action"])
        config_response_action = flatten_actions(config_function_def["response_action"])
        for i in range(len(config_request_action)):
            action = config_request_action[i]
            move_to_first = True
            if action[0] == "add_body_code":
                request_body_type = HttpBodyType.PassOn
            elif action[0] == "add_xml_body_code":
                request_body_type = HttpBodyType.Xml
            else:
                move_to_first = False
            if move_to_first:
                del config_request_action[i]
                config_request_action.insert(0, action)
        if request_body_type == HttpBodyType.NoBody:
            config_request_action.insert(0, ["no_body_code"])

        for i in range(len(config_response_action)):
            action = config_response_action[i]
            move_to_first = True
            if action[0] == "get_body_code":
                response_body_type = HttpBodyType.PassOn
            elif action[0] == "get_xml_body_code":
                response_body_type = HttpBodyType.Xml
            else:
                move_to_first = False
            if move_to_first:
                del config_response_action[i]
                config_response_action.insert(0, action)

        if separate_functions:
            if request_body_type in [HttpBodyType.Xml, HttpBodyType.Json]:
                raise RuntimeError("separate functions for xml or json body is not supported")
            code_template.gen_resource_create_message_function_begin(function_name, option_type, request_body_type)
        else:
            code_template.gen_resource_function_begin(function_name, option_type, return_type, request_body_type, response_body_type)
        for action in config_request_action:
            method_to_call = getattr(code_template, "gen_" + action[0])
            args = []
            kwargs = {"optional": False, "service_name": service_name, "resource_name": resource_name, "function_name": function_name, "option_type": option_type, "request_body_type": request_body_type, "response_body_type": response_body_type, "http_method": http_method}

            should_ignore = False
            ignorable = "ignorable" in action[1:]

            for i in range(1, len(action)):
                a = action[i]
                if a == "ignorable":
                    continue
                elif a == "optional":
                    kwargs["optional"] = True
                elif match_res := re.match("optional\\((.*)\\)", a):
                    kwargs["optional"] = True
                    kwargs["optional_value"] = match_res.group(1)
                elif match_res := re.match("default\\((.*)\\)", a):
                    kwargs["default_value"] = match_res.group(1)
                elif type(a) is str:
                    request_options_used = True
                    arg = "options"
                    arg_types = a.split(".")
                    arg_def = option_def
                    for j, t in enumerate(arg_types):
                        if t not in arg_def.member:
                            if j < len(arg_types) - 1:  # Not the last one
                                continue
                            else:
                                if ignorable:
                                    should_ignore = True
                                    break
                                raise RuntimeError("cannot find " + a + " in request options")
                        arg += "." + t
                        arg_type = arg_def.member_type[arg_def.member.index(t)]
                        arg_nullable = arg_def.member_nullable[arg_def.member.index(t)]
                        if arg_type in models_cache:
                            arg_def = models_cache[arg_type]
                    args.append(arg)
                    arg_def = models_cache[arg_type] if arg_type in models_cache else arg_type
                    kwargs[arg + ".type"] = arg_def
                    kwargs[arg + ".nullable"] = arg_nullable
                elif type(a) is ruamel.yaml.scalarstring.DoubleQuotedScalarString:
                    # maybe add const string definition
                    arg = "\"{}\"".format(a)
                    args.append(arg)
                    kwargs[arg + ".type"] = "std::string"  # we may need to change this to literal string to distinguish from std::string variable
                elif type(action[i]) is ruamel.yaml.scalarstring.SingleQuotedScalarString:
                    arg = "\"{}\"".format(a)
                    args.append(arg)
                    kwargs[arg + ".type"] = "std::string"
            if not should_ignore:
                method_to_call(*args, **kwargs)

        if separate_functions:
            code_template.gen_resource_create_message_function_end()
            code_template.gen_resource_create_response_function_begin(function_name, return_type)
            code_template.gen_resource_create_response_function_check_status_code(return_type, http_status_code)
        else:
            code_template.gen_resource_send_request(return_type, http_status_code)

        for action in config_response_action:
            method_to_call = getattr(code_template, "gen_" + action[0])
            args = []
            kwargs = {"optional": False, "service_name": service_name, "resource_name": resource_name, "function_name": function_name, "return_type": return_type, "request_body_type": request_body_type, "response_body_type": response_body_type, "http_method": http_method}

            for i in range(1, len(action)):
                a = action[i]
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
                        arg_nullable = arg_def.member_nullable[arg_def.member.index(t)]
                        if arg_type in models_cache:
                            arg_def = models_cache[arg_type]
                    args.append(arg)
                    arg_def = models_cache[arg_type] if arg_type in models_cache else arg_type
                    kwargs[arg + ".type"] = arg_def
                    kwargs[arg + ".nullable"] = arg_nullable
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

        if separate_functions:
            code_template.gen_resource_create_response_function_end(return_type)
            code_template.gen_resource_function_glue_function(function_name, option_type, return_type, request_body_type)
        else:
            code_template.gen_resource_function_end(return_type)


    code_template.gen_resource_helper_functions()
    code_template.gen_resource_end(resource_name)


code_template.gen_constant_definition()
for class_name in toposort.toposort_flatten(export_models):
    if models_cache[class_name].external:
        continue
    if models_cache[class_name].noexport:
        raise RuntimeError("Trying to export a non-export class " + class_name)
    code_template.gen_model_definition(service_name, class_name, models_cache[class_name])

generated_dir = pathlib.Path("generated")
output_path = generated_dir / pathlib.Path(config["output_hpp"]).name
output_path.parents[0].mkdir(parents=True, exist_ok=True)
with open(output_path, "w") as f:
    f.write(code_template.global_header.lstrip())
    f.write(code_template.pragma_once)
    f.write(code_template.include_headers)
    f.write(code_template.namespace_begin)
    f.write(code_template.constant_string)
    f.write(code_template.model_definitions_begin)
    f.write(code_template.model_definitions)
    f.write(code_template.model_definitions_end)
    f.write(code_template.details_begin)
    f.write(code_template.details)
    f.write(code_template.rest_client_begin)
    f.write(code_template.main_body)
    f.write(code_template.rest_client_end)
    f.write(code_template.details_end)
    f.write(code_template.namespace_end)
subprocess.call(["clang-format", "-style=file", "-i", output_path])

output_path = generated_dir / pathlib.Path(config["output_cpp"]).name
with open(output_path, "w") as f:
    f.write(code_template.global_header.lstrip())
    f.write("\n#include \"" + config["output_hpp"] + "\"\n")
    f.write(code_template.namespace_begin)
    f.write(code_template.model_definitions_begin)
    f.write(code_template.source_model_definitions)
    f.write(code_template.model_definitions_end)
    f.write(code_template.namespace_end)
subprocess.call(["clang-format", "-style=file", "-i", output_path])
