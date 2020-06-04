import inspect


models_cache = {}

global_header = """
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
"""

include_headers = """
#include <type_traits>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <stdexcept>

namespace libXML2 {
#include "libxml/tree.h"
}

#include "context.hpp"
#include "http/http.hpp"
#include "http/pipeline.hpp"
"""

namespace_begin = """
namespace Azure
{
namespace Storage
{
"""

namespace_end = """
}  // namespace Storage
}  // namspace Azure
"""

constant_string = ""
model_definitions = ""
rest_client_begin = ""
main_body = ""
rest_client_end = ""


def gen_service_namespace(service_name):
    global namespace_begin
    global namespace_end

    namespace_begin += inspect.cleandoc(
        """
        namespace {}
        {{
        """.format(service_name))

    namespace_end = inspect.cleandoc(
        """
        }}  // namespace {}
        """.format(service_name)) + namespace_end


def gen_rest_client(service_name):
    global rest_client_begin
    global rest_client_end

    if service_name.endswith("s"):
        service_name = service_name[:-1]
    class_name = service_name + "RestClient"
    rest_client_begin = "class {} {{ public:".format(class_name)

    rest_client_end = "}};  // class {}\n".format(class_name)


def gen_model_definition(service_name, class_name, class_def):
    content = "{} {} {{".format(class_def.type, class_name)
    for i in range(len(class_def.member)):
        if class_def.member_type[i]:
            if class_def.member_type[i] == class_def.member[i]:
                ns_prefix = service_name + "::"
            else:
                ns_prefix = ""
            content += ns_prefix + class_def.member_type[i] + " " + class_def.member[i]
            if class_def.member_default_value[i]:
                if class_def.member_default_value[i].startswith(class_def.member[i] + "::"):
                    content += "=" + ns_prefix + class_def.member_default_value[i]
                else:
                    content += "=" + class_def.member_default_value[i]
            content += ";"
            if class_def.member_comment[i]:
                content += "// " + class_def.member_comment[i] + "\n"
        else:
            content += class_def.member[i] + ","
            if class_def.member_comment[i]:
                content += "// " + class_def.member_comment[i] + "\n"
    content += "}};  // {} {}\n\n".format(class_def.type, class_name)

    if class_def.type == "enum class":
        snake_case_name = "".join([s for s in map(lambda c: "_" + c.lower() if c.isupper() else c, class_def.name)])
        if snake_case_name.startswith("_"):
            snake_case_name = snake_case_name[1:]
        # To string converter
        content += inspect.cleandoc(
            """
            inline std::string {0}ToString(const {0}& {1})
            {{
                switch ({1})
                {{
            """.format(class_def.name, snake_case_name))

        for i, enum_v in enumerate(class_def.member):
            enum_literal = class_def.member_literal[i]
            if enum_literal is None:
                enum_literal = enum_v
            content += "case {0}::{1}: return \"{2}\";".format(class_def.name, enum_v, enum_literal)

        content += "default: return std::string(); }}\n\n"

        # From string converter
        content += inspect.cleandoc(
            """
            inline {0} {0}FromString(const std::string& {1})
            {{
            """.format(class_def.name, snake_case_name))

        for i, enum_v in enumerate(class_def.member):
            enum_literal = class_def.member_literal[i]
            if enum_literal is None:
                enum_literal = enum_v
            content += "if ({1} == \"{3}\") {{ return {0}::{2}; }}".format(class_def.name, snake_case_name, enum_v, enum_literal)

        content += "throw std::runtime_error(\"cannot convert \" + {1} + \" to {0}\"); }}\n\n".format(class_def.name, snake_case_name)

    global model_definitions
    model_definitions += content


def gen_resource_begin(resource_name):
    content = "class {} {{ public:".format(resource_name)

    global main_body
    main_body += content


def gen_resource_end(resource_name):
    content = "}};  // class {}\n\n".format(resource_name)

    global main_body
    main_body += content


def gen_function_option_definition(service_name, function_name, class_def):
    class_name = function_name + "Options"
    content = "struct {} {{".format(class_name)
    for i in range(len(class_def.member)):
        if class_def.member_type[i] == class_def.member[i]:
            ns_prefix = service_name + "::"
        else:
            ns_prefix = ""
        content += ns_prefix + class_def.member_type[i] + " " + class_def.member[i]
        if class_def.member_default_value[i]:
            if class_def.member_default_value[i].startswith(class_def.member[i] + "::"):
                content += "=" + ns_prefix + class_def.member_default_value[i]
            else:
                content += "=" + class_def.member_default_value[i]
        content += ";"

    content += "}};  // struct {}\n\n".format(class_name)

    global main_body
    main_body += content


def gen_construct_request_function_begin(function_name):
    content = inspect.cleandoc(
        """
        static Azure::Core::Http::Request {0}ConstructRequest(const std::string& url, const {0}Options& options)
        {{
        """.format(function_name))

    global main_body
    main_body += content


def gen_request_definition(http_method, *args, **kwargs):
    if args:
        body = args[0]
        body_type = kwargs[body + ".type"]
    else:
        body = None

    if not body:
        content = "auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::{}, url);".format(http_method)
        content += "request.AddHeader(\"Content-Length\", \"0\");"
    else:
        if body_type == "std::vector<uint8_t>*":
            content = "auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::{}, url, *{});".format(http_method, body)
            content += "request.AddHeader(\"Content-Length\", std::to_string({0}->size()));".format(body)
        elif body_type == "std::string":
            content = "auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::{}, url, {});".format(http_method, body)
            content += "request.AddHeader(\"Content-Length\", std::to_string({0}.size()));".format(body)
        else:
            raise RuntimeError("unknown body type " + body_type)

    global main_body
    main_body += content


def gen_construct_request_function_end():
    content = "return request;}\n\n"

    global main_body
    main_body += content


def gen_parse_response_function_begin(function_name, http_status_code, return_type):
    content = inspect.cleandoc(
        """
        static {1} {0}ParseResponse(Azure::Core::Http::Response& http_response)
        {{
            {1} response;
            auto http_status_code = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(http_response.GetStatusCode());
            if (!(
        """.format(function_name, return_type))
    for i, code in enumerate(http_status_code):
        if i != 0:
            content += "||"
        content += "http_status_code == {}".format(code)

    content += inspect.cleandoc(
        """
        ))
        {
            throw std::runtime_error("HTTP status code " + std::to_string(http_status_code));
        }
        """)

    global main_body
    main_body += content


def gen_parse_response_function_end():
    content = "return response;}\n\n"

    global main_body
    main_body += content


def gen_resource_function(function_name, return_type):
    content = inspect.cleandoc(
        """
        static {1} {0}(Azure::Core::Context context, Azure::Core::Http::HttpPipeline& pipeline, const std::string& url, const {0}Options& options)
        {{
            auto request = {0}ConstructRequest(url, options);
            auto response = pipeline.Send(context, request);
            return {0}ParseResponse(*response);
        }}
        """.format(function_name, return_type))
    content += "\n\n"

    global main_body
    main_body += content


def gen_add_query_code(*args, **kwargs):
    key = args[0]
    value = args[1]
    value_type = kwargs[value + ".type"]
    optional = kwargs["optional"]

    content = ""
    if type(value_type) is str and value_type.startswith("std::vector<") and value_type.endswith(">"):
        template_type = models_cache[value_type[len("std::vector<"): -len(">")]]
        if template_type.type == "enum class":
            str_name = value.replace(".", "_").lower() + "_str"

            content += inspect.cleandoc(
                """
                std::string {var_str};
                for (auto i : {var})
                {{
                    if (!{var_str}.empty())
                    {{
                        {var_str} += ",";
                    }}
                    {var_str} += {typename}ToString(i);
                }}
                """.format(typename=template_type.name, var_str=str_name, var=value))

            if optional:
                content += "if (!{}.empty()){{".format(str_name)
            content += "request.AddQueryParameter({}, {});".format(key, str_name)
            if optional:
                content += "}"
    else:
        if optional:
            if value_type == "std::string":
                content += "if (!{}.empty()) {{".format(value)
            elif value_type == "int" or value_type == "uint64_t":
                optional_value = kwargs["optional_value"]
                content += "if ({} != {}) {{".format(value, optional_value)
            elif hasattr(value_type, "type") and value_type.type == "enum class":
                snake_case_name = "".join([s for s in map(lambda c: "_" + c.lower() if c.isupper() else c, value_type.name)])
                if snake_case_name.startswith("_"):
                    snake_case_name = snake_case_name[1:]
                content += inspect.cleandoc(
                    """
                    std::string {var_name} = {typename}ToString({var});
                    if (!{var_name}.empty())
                    {{
                    """.format(key=key, var=value, var_name=snake_case_name, typename=value_type.name))
                value = snake_case_name
            else:
                raise RuntimeError("unknown type " + value_type.type + " " + value_type.name if hasattr(value_type, "type") else value_type)

        if value_type == "int" or value_type == "uint64_t":
            content += "request.AddQueryParameter({}, std::to_string({}));".format(key, value)
        else:
            content += "request.AddQueryParameter({}, {});".format(key, value)

        if optional:
            content += "}"

    global main_body
    main_body += content


def gen_add_header_code(*args, **kwargs):
    key = args[0]
    value = args[1]
    optional = kwargs["optional"]
    value_type = kwargs[value + ".type"]
    default_value = kwargs.get("default_value", None)

    if default_value and not optional:
        raise RuntimeError("type with default value must be optional")

    if value_type == "std::string":
            #content = "request.AddHeader({}, {});".format(key, default_value)
        if not optional:
            content = "request.AddHeader({}, {});".format(key, value)
        else:
            content = inspect.cleandoc(
                """
                if (!{1}.empty())
                {{
                    request.AddHeader({0}, {1});
                }}
                """.format(key, value))
            if default_value:
                content += inspect.cleandoc(
                """
                else
                {{
                    request.AddHeader({0}, {1});
                }}
                """.format(key, default_value))
    elif hasattr(value_type, "type") and value_type.type == "enum class":
        if not optional:
            content = "request.AddHeader({key}, {typename}ToString({value}));".format(key=key, value=value, typename=value_type.name)
        else:
            str_name = value.replace(".", "_").lower() + "_str"
            content = inspect.cleandoc(
                """
                auto {var_str} = {typename}ToString({value});
                if (!{var_str}.empty())
                {{
                    request.AddHeader({key}, {var_str});
                }}
                """.format(key=key, value=value, var_str=str_name, typename=value_type.name))
    else:
        raise RuntimeError("unknown type " + value_type.type if hasattr(value_type, "type") else value_type)

    global main_body
    main_body += content


def gen_add_range_header_code(*args, **kwargs):
    key = args[0]
    value = args[1]
    value_type = kwargs[value + ".type"]
    assert value_type == "std::pair<uint64_t, uint64_t>"

    content = inspect.cleandoc(
        """
        if ({1}.first <= {1}.second)
        {{
            request.AddHeader({0}, \"bytes=\" + std::to_string({1}.first) + \"-\" + std::to_string({1}.second));
        }}
        """.format(key, value))

    global main_body
    main_body += content


def gen_add_metadata_code(*args, **kwargs):
    prefix = args[0]
    value = args[1]
    content = inspect.cleandoc(
        """
        for (const auto& pair : {1})
        {{
            request.AddHeader({0} + pair.first, pair.second);
        }}
        """.format(prefix, value))

    global main_body
    main_body += content


def gen_get_metadata_code(*args, **kwargs):
    prefix = args[0]
    value = args[1]

    content = inspect.cleandoc(
        """
        for (auto i = http_response.GetHeaders().lower_bound({0}); i != http_response.GetHeaders().end() && i->first.substr(0, {1}) == {0}; ++i)
        {{
            {2}.emplace(i->first.substr({1}), i->second);
        }}
        """.format(prefix, len(prefix) - 2, value))

    global main_body
    main_body += content


def gen_add_body_code(*args, **kwargs):
    raise RuntimeError("this function should never be called")
    pass


def gen_get_body_code(*args, **kwargs):
    body = args[0]
    value_type = kwargs[body + ".type"]

    if value_type == "std::vector<uint8_t>":
        func_name = "GetBodyBuffer"
    elif value_type == "Azure::Core::Http::BodyStream*":
        func_name = "GetBodyStream"

    content = "{0} = http_response.{1}();".format(body, func_name)

    global main_body
    main_body += content


def gen_add_xml_body_code(*args, **kwargs):
    service_name = kwargs["service_name"]
    resource_name = kwargs["resource_name"]
    function_name = kwargs["function_name"]
    template_file = "template/add_{}_{}_{}_xml.cc".format(service_name, resource_name, function_name)

    global main_body
    main_body += open(template_file).read()


def gen_get_xml_body_code(*args, **kwargs):
    service_name = kwargs["service_name"]
    resource_name = kwargs["resource_name"]
    function_name = kwargs["function_name"]
    template_file = "template/get_{}_{}_{}_xml.cc".format(service_name, resource_name, function_name)

    global main_body
    main_body += open(template_file).read()


def gen_get_header_code(*args, **kwargs):
    key = args[0]
    target = args[1]
    target_type = kwargs[target + ".type"]
    target_str_name = target.replace(".", "_").lower() + "_str"
    optional = kwargs["optional"]

    if hasattr(target_type, "type") and target_type.type == "enum class":
        enum_class_if_blocks = ""
        for i, enum_v in enumerate(target_type.member):
            enum_literal = target_type.member_literal[i]
            if enum_literal is None:
                enum_literal = enum_v
            if i != 0:
                enum_class_if_blocks += "else "
            enum_class_if_blocks += inspect.cleandoc(
                """
                if ({1} == \"{4}\")
                {{
                    {0} = {2}::{3};
                }}
                """.format(target, target_str_name, target_type.name, enum_v, enum_literal))

    if optional:
        ite_name = target.replace(".", "_").lower() + "_iterator"
        content = inspect.cleandoc(
            """
            auto {1} = http_response.GetHeaders().find({0});
            if ({1} != http_response.GetHeaders().end())
            {{
            """.format(key, ite_name))

        if target_type == "int":
            content += "{} = std::stoi({}->second);".format(target, ite_name)
        elif target_type == "uint64_t":
            content += "{} = std::stoull({}->second);".format(target, ite_name)
        elif target_type == "std::string":
            content += "{} = {}->second;".format(target, ite_name)
        elif target_type == "bool":
            content += "{} = {}->second == \"true\";".format(target, ite_name)
        elif hasattr(target_type, "type") and target_type.type == "enum class":
            content += "{target} = {typename}FromString({ite}->second);".format(target=target, ite=ite_name, typename=target_type.name)
        else:
            raise RuntimeError("unknown type " + target_type.type if hasattr(target_type, "type") else target_type)

        content += "}"
    else:
        if target_type == "int":
            content = "{1} = std::stoi(http_respone.GetHeaders().at({0}));".format(key, target)
        elif target_type == "uint64_t":
            content = "{1} = std::stoull(http_response.GetHeaders().at({0}));".format(key, target)
        elif target_type == "std::string":
            content = "{1} = http_response.GetHeaders().at({0});".format(key, target)
        elif target_type == "bool":
            content = "{1} = http_response.GetHeaders().at({0}) == \"true\";".format(key, target)
        elif hasattr(target_type, "type") and target_type.type == "enum class":
            content = "{target} = {typename}FromString(http_response.GetHeaders().at({key}));".format(key=key, target=target, typename=target_type.name)
        else:
            raise RuntimeError("unknown type " + target_type.type if hasattr(target_type, "type") else target_type)

    global main_body
    main_body += content
