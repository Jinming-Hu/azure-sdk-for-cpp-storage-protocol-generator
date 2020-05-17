import inspect


models_cache = {}

global_header = """
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

/***************************************************************
 * ALL THE CODE IN THIS FILE IS HANDWRITTEN, NOT AUTO-GENERATED.
 **************************************************************/

#pragma once
"""

include_headers = """
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <stdexcept>

#include "libxml/tree.h"

#include "http/http.hpp"
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


def gen_model_definition(class_name, class_def):
    content = "{} {} {{".format(class_def.type, class_name)
    for i in range(len(class_def.member)):
        if class_def.member_type[i]:
            content += class_def.member_type[i] + " " + class_def.member[i]
            if class_def.member_default_value[i]:
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
            static std::string {0}ToString(const {0}& {1})
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
            static {0} {0}FromString(const std::string& {1})
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


def gen_function_option_definition(function_name, class_def):
    class_name = function_name + "Options"
    content = "struct {} {{".format(class_name)
    for i in range(len(class_def.member)):
        content += class_def.member_type[i] + " " + class_def.member[i]
        if class_def.member_default_value[i]:
            content += "=" + class_def.member_default_value[i]
        content += ";"

    content += "}};  // struct {}\n\n".format(class_name)

    global main_body
    main_body += content


def gen_construct_request_function_begin(function_name, http_method):
    content = inspect.cleandoc(
        """
        static azure::core::http::Request {0}ConstructRequest(const std::string& url, const {0}Options& options)
        {{
        auto request = azure::core::http::Request(azure::core::http::HttpMethod::{1}, url);
        """.format(function_name, http_method))

    global main_body
    main_body += content


def gen_construct_request_function_end():
    content = "return request;}\n\n"

    global main_body
    main_body += content


def gen_parse_response_function_begin(function_name, http_status_code, return_type):
    content = inspect.cleandoc(
        """
        static {1} {0}ParseResponse(/* TODO: const */ azure::core::http::Response& http_response)
        {{
            {1} response;
            if (!(
        """.format(function_name, return_type))
    for i, code in enumerate(http_status_code):
        if i != 0:
            content += "||"
        content += "http_response.getStatusCode() == {}".format(code)

    content += inspect.cleandoc(
        """
        ))
        {
            throw std::runtime_error("HTTP status code " + std::to_string(http_response.getStatusCode()));
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
        static {1} {0}(const std::string& url, const {0}Options& options)
        {{
            return {0}ParseResponse(azure::core::http::Client::send({0}ConstructRequest(url, options)));
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
    if value_type.startswith("std::vector<") and value_type.endswith(">"):
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
            content += "request.addQueryParameter({}, {});".format(key, str_name)
            if optional:
                content += "}"
    else:
        if optional:
            if value_type == "std::string":
                content += "if (!{}.empty()) {{".format(value)
            elif value_type == "int" or value_type == "uint64_t":
                optional_value = kwargs["optional_value"]
                content += "if ({} != {}) {{".format(value, optional_value)
            else:
                raise RuntimeError("unknown type " + value_type.type if hasattr(value_type, "type") else value_type)

        if value_type == "int" or value_type == "uint64_t":
            content += "request.addQueryParameter({}, std::to_string({}));".format(key, value)
        else:
            content += "request.addQueryParameter({}, {});".format(key, value)

        if optional:
            content += "}"

    global main_body
    main_body += content


def gen_add_header_code(*args, **kwargs):
    key = args[0]
    value = args[1]
    optional = kwargs["optional"]
    value_type = kwargs[value + ".type"]
    if value_type == "std::string":
        if not optional:
            content = "request.addHeader({}, {});".format(key, value)
        else:
            content = inspect.cleandoc(
                """
                if (!{1}.empty())
                {{
                    request.addHeader({0}, {1});
                }}
                """.format(key, value))
    elif hasattr(value_type, "type") and value_type.type == "enum class":
        if not optional:
            content = "request.addHeader({key}, {typename}ToString({value}));".format(key=key, value=value, typename=value_type.name)
        else:
            str_name = value.replace(".", "_").lower() + "_str"
            content = inspect.cleandoc(
                """
                auto {var_str} = {typename}ToString({value});
                if (!{var_str}.empty())
                {{
                    request.addHeader({key}, {var_str});
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
            request.addHeader({0}, \"bytes=\" + std::to_string({1}.first) + \"-\" + std::to_string({1}.second));
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
            request.addHeader({0} + pair.first, pair.second);
        }}
        """.format(prefix, value))

    global main_body
    main_body += content


def gen_get_metadata_code(*args, **kwargs):
    prefix = args[0]
    value = args[1]

    content = inspect.cleandoc(
        """
        for (auto i = http_response.getHeaders().lower_bound({0}); i != http_response.getHeaders().end() && i->first.substr(0, {1}) == {0}; ++i)
        {{
            {2}.emplace(i->first.substr({1}), i->second);
        }}
        """.format(prefix, len(prefix) - 2, value))

    global main_body
    main_body += content


def gen_add_body_code(*args, **kwargs):
    body = args[0]
    value_type = kwargs[body + ".type"]

    if value_type == "azure::core::http::BodyBuffer*":
        func_name = "setBodyBuffer"
    elif value_type == "azure::core::http::BodyStream*":
        func_name = "setBodyStream"
    content = inspect.cleandoc(
        """
        if ({0})
        {{
            request.{1}({0});
            request.addHeader("Content-Length", std::to_string({0}->_bodyBufferSize));
        }}
        """.format(body, func_name))

    global main_body
    main_body += content


def gen_get_body_code(*args, **kwargs):
    body = args[0]
    value_type = kwargs[body + ".type"]

    if value_type == "azure::core::http::BodyBuffer*":
        func_name = "getBodyBuffer"
    elif value_type == "azure::core::http::BodyStream*":
        func_name = "getBodyStream"

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
            auto {1} = http_response.getHeaders().find({0});
            if ({1} != http_response.getHeaders().end())
            {{
            """.format(key, ite_name))

        if target_type == "uint64_t":
            content += "{} = std::stoull({}->second);".format(target, ite_name)
        elif target_type == "std::string":
            content += "{} = {}->second;".format(target, ite_name)
        elif target_type == "bool":
            content += "{} = {}->second == \"true\"".format(target, ite_name)
        elif hasattr(target_type, "type") and target_type.type == "enum class":
            content += "{target} = {typename}FromString({ite}->second);".format(target=target, ite=ite_name, typename=target_type.name)
        else:
            raise RuntimeError("unknown type " + target_type.type if hasattr(target_type, "type") else target_type)

        content += "}"
    else:
        if target_type == "uint64_t":
            content = "{1} = std::stoull(http_response.getHeaders().at({0}));".format(key, target)
        elif target_type == "std::string":
            content = "{1} = http_response.getHeaders().at({0});".format(key, target)
        elif target_type == "bool":
            content = "{1} = http_response.getHeaders().at({0}) == \"true\";".format(key, target)
        elif hasattr(target_type, "type") and target_type.type == "enum class":
            content = "{target} = {typename}FromString(http_response.getHeaders().at({key}));".format(key=key, target=target, typename=target_type.name)
        else:
            raise RuntimeError("unknown type " + target_type.type if hasattr(target_type, "type") else target_type)

    global main_body
    main_body += content
