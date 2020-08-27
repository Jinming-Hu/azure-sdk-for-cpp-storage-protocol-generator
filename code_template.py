import os
import inspect
from enum import Enum


class HttpBodyType(Enum):
    NoBody = 0
    PassOn = 1
    Xml = 2
    Json = 3


models_cache = {}

global_header = """
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
"""

include_headers = """
#include <type_traits>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <stdexcept>
#include <limits>

#include "azure/core/nullable.hpp"
#include "azure/core/context.hpp"
#include "azure/core/response.hpp"
#include "azure/core/http/http.hpp"
#include "azure/core/http/pipeline.hpp"
#include "azure/storage/common/xml_wrapper.hpp"
#include "azure/storage/common/storage_common.hpp"
#include "azure/storage/common/storage_error.hpp"

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
model_definitions = """

"""
rest_client_begin = ""
main_body = ""
rest_client_end = ""

fromxml_classes = set()
toxml_classes = set()
toxml_options_def_cache = {}

constants_map = {}


def get_snake_case_name(var):
    res = str()
    last_is_upper = False
    last_is_underscore = False
    for c in var:
        if c.isupper():
            if last_is_upper:
                res += c.lower()
            elif last_is_underscore:
                res += c.lower()
            else:
                res += "_" + c.lower()
            last_is_upper = True
            last_is_underscore = False
        elif c.islower() or c.isdigit():
            res += c
            last_is_upper = False
            last_is_underscore = False
        else:
            res += "_"
            last_is_upper = False
            last_is_underscore = True
    while res.startswith("_"):
        res = res[1:]
    return res


def gen_constant_definition():
    content = str()
    if len(constants_map):
        for k, v in sorted(constants_map.items()):
            content += "constexpr static const char* {key} = \"{value}\";".format(key=k, value=v)
    content += "\n\n"

    global model_definitions
    model_definitions += content


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
    if class_def.type == "enum class" or class_def.type == "struct":
        content = "{} {} {{".format(class_def.type, class_name)
    elif class_def.type == "bitwise enum":
        content = "enum class {} {{".format(class_name)
    for i in range(len(class_def.member)):
        if class_def.member_type[i]:
            # for struct
            if class_def.member_type[i] == class_def.member[i]:
                ns_prefix = service_name + "::"
            else:
                ns_prefix = ""
            if class_def.member_nullable[i]:
                real_member_type = "Azure::Core::Nullable<" + ns_prefix + class_def.member_type[i] + ">"
            else:
                real_member_type = ns_prefix + class_def.member_type[i]
            content += real_member_type + " " + class_def.member[i]
            if class_def.member_default_value[i]:
                if class_def.member_default_value[i].startswith(class_def.member[i] + "::"):
                    content += "=" + ns_prefix + class_def.member_default_value[i]
                else:
                    content += "=" + class_def.member_default_value[i]
            content += ";"
        elif class_def.type == "bitwise enum":
            content += class_def.member[i] + "=" + str(2**i // 2) + ","
        else:
            # for enum
            content += class_def.member[i] + ","
        if class_def.member_comment[i]:
            content += "// " + class_def.member_comment[i] + "\n"
    content += "}};  // {} {}\n\n".format(class_def.type, class_name)

    if class_def.type == "enum class":
        snake_case_name = get_snake_case_name(class_def.name)
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
    elif class_def.type == "bitwise enum":
        # Bitwise or, and
        content += inspect.cleandoc(
            """
            inline {typename} operator|({typename} lhs, {typename} rhs) {{
                using type = std::underlying_type_t<{typename}>;
                return static_cast<{typename}>(static_cast<type>(lhs) | static_cast<type>(rhs));
            }}\n
            inline {typename}& operator|=({typename}& lhs, {typename} rhs) {{
                lhs = lhs | rhs;
                return lhs;
            }}\n
            inline {typename} operator&({typename} lhs, {typename} rhs) {{
                using type = std::underlying_type_t<{typename}>;
                return static_cast<{typename}>(static_cast<type>(lhs) & static_cast<type>(rhs));
            }}\n
            inline {typename}& operator&=({typename}& lhs, {typename} rhs) {{
                lhs = lhs & rhs;
                return lhs;
            }}
            """.format(typename=class_def.name))
        content += "\n\n"
        # To string converter
        content += "inline std::string {typename}ToString(const {typename}& val) {{".format(typename=class_def.name)
        enum_list = class_def.name + " value_list[] = {"
        string_list = "const char* string_list[] = {"
        for i, enum_v in enumerate(class_def.member):
            enum_literal = class_def.member_literal[i]
            if len(enum_literal) == 0:
                continue
            enum_list += class_def.name + "::" + enum_v + ","
            string_list += "\"" + enum_literal + "\"" + ","
        enum_list += "};"
        string_list += "};"
        content += enum_list + string_list
        content += inspect.cleandoc(
            """
            std::string ret;
            for (std::size_t i = 0; i < sizeof(value_list) / sizeof({typename}); ++i) {{
                if ((val & value_list[i]) == value_list[i]) {{
                    if (!ret.empty()) {{ ret += ","; }}
                    ret += string_list[i];
                }}
            }}
            return ret;}}
            """.format(typename=class_def.name))
        content += "\n\n"

    global model_definitions
    model_definitions += content


def gen_fromxml_function(class_name):
    global main_body

    if type(class_name) is tuple:
        class_type = class_name[0]
        member_name = class_name[1]
        if class_type == "std::map<std::string, std::string>":
            content = inspect.cleandoc(
                """
                static std::map<std::string, std::string> {}FromXml(XmlReader& reader) {{
                    std::map<std::string, std::string> ret;
                    int depth = 0;
                    std::string key;
                    while (true) {{
                        auto node = reader.Read();
                        if (node.Type == XmlNodeType::End) {{
                            break;
                        }} else if (node.Type == XmlNodeType::StartTag) {{
                            if (depth++ == 0) {{ key = node.Name; }}
                        }} else if (node.Type == XmlNodeType::EndTag) {{
                            if (depth-- == 0) {{ break; }}
                        }} else if (depth == 1 && node.Type == XmlNodeType::Text) {{
                            ret.emplace(std::move(key), std::string(node.Value));
                        }}
                    }}
                    return ret;
                }}
                """.format(member_name))
        elif class_type == "std::pair<int64_t, int64_t>":
            content = inspect.cleandoc(
                """
                static std::pair<int64_t, int64_t> {}FromXml(XmlReader& reader) {{
                    int depth = 0;
                    bool is_start = false;
                    bool is_end = false;
                    int64_t start = 0;
                    int64_t end = 0;
                    while (true) {{
                        auto node = reader.Read();
                        if (node.Type == XmlNodeType::End) {{
                            break;
                        }} else if (node.Type == XmlNodeType::StartTag && strcmp(node.Name, "Start") == 0) {{
                            ++depth;
                            is_start = true;
                        }} else if (node.Type == XmlNodeType::StartTag && strcmp(node.Name, "End") == 0) {{
                            ++depth;
                            is_end = true;
                        }} else if (node.Type == XmlNodeType::EndTag) {{
                            is_start = false;
                            is_end = false;
                            if (depth-- == 0) {{ break; }}
                        }}
                        if (depth == 1 && node.Type == XmlNodeType::Text) {{
                            if (is_start) {{ start = std::stoll(node.Value); }}
                            else if (is_end) {{ end = std::stoll(node.Value); }}
                        }}
                    }}
                    return std::make_pair(start, end);
                }}
                """.format(member_name))
        elif class_type == "std::vector<ObjectReplicationPolicy>":
            content = inspect.cleandoc(
                """
                static std::vector<ObjectReplicationPolicy> {}FromXml(XmlReader& reader) {{
                    int depth = 0;
                    std::map<std::string, std::vector<ObjectReplicationRule>> orPropertiesMap;
                    std::string policyId;
                    std::string ruleId;
                    while (true) {{
                        auto node = reader.Read();
                        if (node.Type == XmlNodeType::End) {{
                            break;
                        }} else if (node.Type == XmlNodeType::StartTag) {{
                            ++depth;
                            std::string startTagName = node.Name;
                            if (startTagName.substr(0, 3) == "or-") {{
                                auto underscorePos = startTagName.find('_', 3);
                                policyId = std::string(startTagName.begin() + 3, startTagName.begin() + underscorePos);
                                ruleId = startTagName.substr(underscorePos + 1);
                            }}
                        }} else if (node.Type == XmlNodeType::EndTag) {{
                            if (depth-- == 0) {{ break; }}
                        }}
                        if (depth == 1 && node.Type == XmlNodeType::Text) {{
                            ObjectReplicationRule rule;
                            rule.RuleId = std::move(ruleId);
                            rule.ReplicationStatus = ObjectReplicationStatusFromString(node.Value);
                            orPropertiesMap[policyId].emplace_back(std::move(rule));
                        }}
                    }}
                    std::vector<ObjectReplicationPolicy> ret;
                    for (auto& property : orPropertiesMap) {{
                        ObjectReplicationPolicy policy;
                        policy.PolicyId = property.first;
                        policy.Rules = std::move(property.second);
                        ret.emplace_back(std::move(policy));
                    }}
                    return ret;
                }}
                """.format(member_name))
        else:
            raise RuntimeError(class_type + " from xml not supported")
        main_body += content + "\n\n"
        return

    class_def = models_cache[class_name]
    if not class_def.fromxml_actions:
        raise RuntimeError("couldn't find fromxml actions for class " + class_name)

    def to_cpp_name(var_name):
        return "".join(c for c in var_name if c.isalpha() or c.isdigit() or c == "_")

    def get_member_type(member):
        member_def = class_def
        for i, m in enumerate(member.split(".")):
            j = member_def.member.index(m)
            if i == len(member.split(".")) - 1:
                return member_def.member_type[j]
            member_def = models_cache[member_def.member_type[j]]

    all_xml_tag_seen = set()
    all_xml_tag = []
    for i in [x[1] for x in class_def.fromxml_actions if x[0] == "text" or x[0] == "start_tag" or x[0] == "end_tag"]:
        all_xml_tag.extend([j for j in i.split(".") if not (j in all_xml_tag_seen or all_xml_tag_seen.add(j))])

    content = inspect.cleandoc(
        """
        static {0} {0}FromXml(XmlReader& reader)
        {{
            {0} ret;
            enum class XmlTagName {{
        """.format(class_def.name))
    for xml_tag in all_xml_tag:
        content += "k_" + to_cpp_name(xml_tag) + ","
    content += "k_Unknown,"
    content += "};"
    content += inspect.cleandoc(  # end tag
        """
        std::vector<XmlTagName> path;
        while (true) {
            auto node = reader.Read();
            if (node.Type == XmlNodeType::End) { break; }
            else if (node.Type == XmlNodeType::EndTag) {
                if (path.size() > 0) { path.pop_back(); }
                else { break; }
            }
            else if (node.Type == XmlNodeType::StartTag) {
        """)
    # start tag
    for i, xml_tag in enumerate(all_xml_tag):
        if i != 0:
            content += "else "
        content += "if (std::strcmp(node.Name, \"{0}\") == 0) {{ path.emplace_back(XmlTagName::k_{1}); }}".format(xml_tag, to_cpp_name(xml_tag))
        if i == len(all_xml_tag) - 1:
            content += "else { path.emplace_back(XmlTagName::k_Unknown); }"
    # still in start tag, call another FromXml function
    for i, (path, member) in enumerate([(a[1], a[2]) for a in class_def.fromxml_actions if a[0] == "start_tag"]):
        if i != 0:
            content += "else "
        content += "if (path.size() == {} &&".format(len(path.split(".")))
        for j, k in enumerate(path.split(".")):
            content += "path[{}] == XmlTagName::k_".format(j) + to_cpp_name(k)
            if j != len(path.split(".")) - 1:
                content += "&&"
        content += "){"

        member_type = get_member_type(member)
        if member_type == "std::vector<ObjectReplicationPolicy>":
            content += "ret.{member_name} = {member_name}FromXml(reader);".format(member_name=member)
            fromxml_classes.add((member_type, member))
        elif member_type.startswith("std::vector<") and member_type.endswith(">"):
            inner_type = member_type[len("std::vector<"): -len(">")]
            if inner_type.startswith("std::"):
                content += "ret.{member_name}.emplace_back({function_name}FromXml(reader));".format(member_name=member, function_name=member)
                fromxml_classes.add((inner_type, member))
            else:
                content += "ret.{member_name}.emplace_back({inner_type}FromXml(reader));".format(member_name=member, inner_type=inner_type)
                fromxml_classes.add(inner_type)
        elif member_type.startswith("std::"):
            content += "ret.{member_name} = {member_name}FromXml(reader);".format(member_name=member)
            fromxml_classes.add((member_type, member))
        else:
            content += "ret.{member_name} = {member_type}FromXml(reader);".format(member_name=member, member_type=member_type)
            fromxml_classes.add(member_type)
        content += "path.pop_back();"

        content += "}"
    # text
    content += "} else if (node.Type == XmlNodeType::Text) {"
    for i, (path, member) in enumerate([(a[1], a[2]) for a in class_def.fromxml_actions if a[0] == "text"]):
        if i != 0:
            content += "else "
        content += "if (path.size() == {} &&".format(len(path.split(".")))
        for j, k in enumerate(path.split(".")):
            content += "path[{}] == XmlTagName::k_".format(j) + to_cpp_name(k)
            if j != len(path.split(".")) - 1:
                content += "&&"
        content += "){"
        member_type = get_member_type(member)
        if member_type == "int64_t":
            content += "ret.{} = std::stoll(node.Value);".format(member)
        elif member_type == "int32_t":
            content += "ret.{} = std::stoi(node.Value);".format(member)
        elif member_type == "bool":
            content += "ret.{} = std::strcmp(node.Value,\"true\") == 0;".format(member)
        elif member_type in models_cache and models_cache[member_type].type == "enum class":
            content += "ret.{} = {}FromString(node.Value);".format(member, member_type)
        else:
            content += "ret.{} = node.Value;".format(member)
        content += "}"
    # attribute
    for i, (path, attr_name, member) in enumerate([(a[1], a[2], a[3]) for a in class_def.fromxml_actions if a[0] == "attribute"]):
        if i == 0:
            content += "} else if (node.Type == XmlNodeType::Attribute) {"
        if i != 0:
            content += "else "
        content += "if (path.size() == {} &&".format(len(path.split(".")))
        for j, k in enumerate(path.split(".")):
            content += "path[{}] == XmlTagName::k_".format(j) + to_cpp_name(k) + "&&"
        content += "std::strcmp(node.Name,\"{}\") == 0)".format(attr_name)
        content += "{{ ret.{} = node.Value; }}".format(member)

    content += "}} return ret;}\n\n"

    main_body += content


def gen_toxml_function(class_name):
    def toxml_content(member_name, member_type):
        if member_type.startswith("std::vector<") and member_type.endswith(">"):
            inner_type = member_type[len("std::vector<"): -len(">")]
            content = "for (const auto& i : {}) {{".format(member_name)
            content += toxml_content("i", inner_type)
            content += "}"
        elif member_type.startswith("std::pair<") and member_type.endswith(">"):
            comma_pos = member_type.index(",")  # suppose only 1 comma
            inner_type1 = member_type[len("std::pair<"): comma_pos].strip()
            inner_type2 = member_type[comma_pos + 1: -len(">")].strip()

            inner_type1_to_string = member_name + ".first"
            inner_type2_to_string = member_name + ".second"

            if inner_type1 == "std::string":
                pass
            elif inner_type1 == "int32_t" or inner_type1 == "int64_t":
                inner_type1_to_string = "std::to_string(" + inner_type1_to_string + ")"
            elif inner_type1 in models_cache:
                inner_type1_to_string = inner_type1 + "ToString(" + inner_type1_to_string + ")"
            else:
                raise RuntimeError("unknown type " + inner_type1)

            if inner_type2 == "std::string":
                pass
            elif inner_type2 == "int32_t" or inner_type2 == "int64_t":
                inner_type2_to_string = "std::to_string(" + inner_type2_to_string + ")"
            elif inner_type1 in models_cache:
                inner_type2_to_string = inner_type2 + "ToString(" + inner_type2_to_string + ")"
            else:
                raise RuntimeError("unknown type " + inner_type2)

            content = "writer.Write(XmlNode{{XmlNodeType::StartTag, {0}.data(), {1}.data() }});".format(inner_type1_to_string, inner_type2_to_string)
        elif member_type == "std::string":
            content = "writer.Write(XmlNode{{XmlNodeType::Text, nullptr, {}.data()}});".format(member_name)
        elif member_type == "bool":
            content = "writer.Write(XmlNode{{XmlNodeType::Text, nullptr, {} ? \"true\":\"false\"}});".format(member_name)
        elif member_type in ["int32_t", "int64_t"]:
            content = "writer.Write(XmlNode{{XmlNodeType::Text, nullptr, std::to_string({}).data()}});".format(member_name)
        else:
            content = "{}ToXml(writer, {});".format(member_type, member_name)
            toxml_classes.add(member_type)
            toxml_options_def_cache[member_type] = models_cache[member_type]
        return content

    if class_name in toxml_options_def_cache:
        class_def = toxml_options_def_cache[class_name]

        content = inspect.cleandoc(
            """
            static void {0}ToXml(XmlWriter& writer, const {0}& options) {{
            """.format(class_name))

        xml_path = []
        for a in class_def.toxml_actions:
            xml_action_type = a[0]
            target_xml_path = a[1].split(".")
            member = a[2]
            member_type = class_def.member_type[class_def.member.index(member)]
            member_nullable = class_def.member_nullable[class_def.member.index(member)]

            if xml_action_type == "tag":
                common_prefix = os.path.commonprefix([xml_path, target_xml_path])
                while len(xml_path) > len(common_prefix):
                    content += "writer.Write(XmlNode{XmlNodeType::EndTag});"
                    xml_path.pop()
                while len(xml_path) < len(target_xml_path) - 1:
                    p = target_xml_path[len(xml_path)]
                    content += "writer.Write(XmlNode{{XmlNodeType::StartTag, \"{}\"}});".format(p)
                    xml_path.append(p)
                if member_nullable:
                    content += "if (options.{}.HasValue()) {{".format(member)
                    member += ".GetValue()"
                last_path_added = False
                if len(xml_path) < len(target_xml_path):
                    p = target_xml_path[len(xml_path)]
                    content += "writer.Write(XmlNode{{XmlNodeType::StartTag, \"{}\"}});".format(p)
                    xml_path.append(p)
                    last_path_added = True
                content += toxml_content("options." + member, member_type)
                if last_path_added:
                    content += "writer.Write(XmlNode{XmlNodeType::EndTag});"
                    xml_path.pop()
                if member_nullable:
                    content += "}"
            else:
                raise RuntimeError("unsupported toxml action " + xml_action_type)
        while len(xml_path):
            content += "writer.Write(XmlNode{XmlNodeType::EndTag});"
            xml_path.pop()

        content += "}\n\n"
    elif class_name in models_cache:
        raise RuntimeError("generate ToXml() for no-option classes not supported yet")
    else:
        raise RuntimeError("unknown type " + class_name)

    global main_body
    main_body += content


def gen_resource_begin(resource_name):
    content = "class {} {{ public:".format(resource_name)

    global main_body
    main_body += content


def gen_resource_end(resource_name):
    content = "}};  // class {}\n\n".format(resource_name)

    global main_body
    main_body += content


def gen_resource_helper_functions():
    content = "private:"

    global main_body
    main_body += content

    fromxml_classes_generated = set()
    while fromxml_classes_generated != fromxml_classes:
        for class_name in sorted(list(fromxml_classes - fromxml_classes_generated), key=lambda k: str(k)):
            gen_fromxml_function(class_name)
            fromxml_classes_generated.add(class_name)

    fromxml_classes.clear()

    toxml_classes_generated = set()
    while toxml_classes_generated != toxml_classes:
        for class_name in sorted(list(toxml_classes - toxml_classes_generated), key=lambda k: str(k)):
            gen_toxml_function(class_name)
            toxml_classes_generated.add(class_name)

    toxml_classes.clear()


def gen_function_option_definition(service_name, class_name, class_def):
    content = "struct {} {{".format(class_name)
    for i in range(len(class_def.member)):
        if class_def.member_type[i] == class_def.member[i]:
            ns_prefix = service_name + "::"
        else:
            ns_prefix = ""
        if class_def.member_nullable[i]:
            real_member_type = "Azure::Core::Nullable<" + ns_prefix + class_def.member_type[i] + ">"
        else:
            real_member_type = ns_prefix + class_def.member_type[i]
        content += real_member_type + " " + class_def.member[i]
        if class_def.member_default_value[i]:
            if class_def.member_default_value[i].startswith(class_def.member[i] + "::"):
                content += "=" + ns_prefix + class_def.member_default_value[i]
            else:
                content += "=" + class_def.member_default_value[i]
        content += ";"

    content += "}};  // struct {}\n\n".format(class_name)

    if class_def.toxml_actions:
        toxml_classes.add(class_name)
        toxml_options_def_cache[class_name] = class_def

    global main_body
    main_body += content


def gen_resource_create_message_function_begin(function_name, option_type, request_body_type):
    content = "static Azure::Core::Http::Request {function_name}CreateMessage(const std::string& url,".format(function_name=function_name)
    if request_body_type == HttpBodyType.PassOn:
        content += "Azure::Core::Http::BodyStream* requestBody,"
    content += "const {option_type}& options) {{ unused(options);".format(option_type=option_type)

    global main_body
    main_body += content


def gen_resource_create_message_function_end():
    content = "return request; }\n\n"

    global main_body
    main_body += content


def gen_resource_create_response_function_begin(function_name, return_type):
    content = "static Azure::Core::Response<{return_type}> {function_name}CreateResponse(const Azure::Core::Context& context, std::unique_ptr<Azure::Core::Http::RawResponse> pHttpResponse) {{ unused(context);".format(function_name=function_name, return_type=return_type)

    global main_body
    main_body += content


def gen_resource_create_response_function_check_status_code(return_type, http_status_code):
    content = inspect.cleandoc(
        """
        Azure::Core::Http::RawResponse& httpResponse = *pHttpResponse;
        {return_type} response;
        auto http_status_code = static_cast<std::underlying_type<Azure::Core::Http::HttpStatusCode>::type>(httpResponse.GetStatusCode());
        if (!(
        """.format(return_type=return_type))
    for i, code in enumerate(http_status_code):
        if i != 0:
            content += "||"
        content += "http_status_code == {}".format(code)

    content += inspect.cleandoc(
        """
        ))
        {
            throw StorageError::CreateFromResponse(std::move(pHttpResponse));
        }
        """)

    global main_body
    main_body += content


def gen_resource_create_response_function_end(return_type):
    content = "return Azure::Core::Response<{return_type}>(std::move(response), std::move(pHttpResponse));}}\n\n".format(return_type=return_type)

    global main_body
    main_body += content


def gen_resource_function_glue_function(function_name, option_type, return_type, request_body_type):
    content = "static Azure::Core::Response<{return_type}> {function_name}(const Azure::Core::Context& context, Azure::Core::Http::HttpPipeline& pipeline, const std::string& url,".format(function_name=function_name, return_type=return_type)
    if request_body_type == HttpBodyType.PassOn:
        content += "Azure::Core::Http::BodyStream* requestBody,"
    content += "const {option_type}& options) {{".format(option_type=option_type)
    content += "auto request = {function_name}CreateMessage(url,".format(function_name=function_name, option_type=option_type)
    if request_body_type == HttpBodyType.PassOn:
        content += "requestBody,"
    content += "options);"
    content += inspect.cleandoc(
        """
        auto pHttpResponse = pipeline.Send(context, request);
        return {function_name}CreateResponse(context, std::move(pHttpResponse));
        }}
        """.format(function_name=function_name))
    content += "\n\n"

    global main_body
    main_body += content


def gen_resource_function_begin(function_name, option_type, return_type, request_body_type, response_body_type):
    content = "static Azure::Core::Response<{return_type}> {function_name}(const Azure::Core::Context& context, Azure::Core::Http::HttpPipeline& pipeline, const std::string& url,".format(function_name=function_name, return_type=return_type)
    if request_body_type == HttpBodyType.PassOn:
        content += "Azure::Core::Http::BodyStream* requestBody,"
    content += "const {option_type}& options) {{ unused(options);".format(option_type=option_type)

    global main_body
    main_body += content


def gen_resource_send_request(return_type, http_status_code):
    content = "auto pHttpResponse = pipeline.Send(context, request);"

    global main_body
    main_body += content

    gen_resource_create_response_function_check_status_code(return_type, http_status_code)


def gen_resource_function_end(return_type):
    content = "return Azure::Core::Response<{return_type}>(std::move(response), std::move(pHttpResponse));}}\n\n".format(return_type=return_type)

    global main_body
    main_body += content


def gen_add_query_code(*args, **kwargs):
    key = args[0]
    value = args[1]
    value_type = kwargs[value + ".type"]
    value_nullable = kwargs.get(value + ".nullable", False)
    optional = kwargs["optional"]

    content = ""
    if value_nullable:
        content += "if ({}.HasValue()) {{".format(value)
        value += ".GetValue()"

    if optional:
        if value_type == "std::string":
            content += "if (!{}.empty()) {{".format(value)
        elif value_type == "int32_t" or value_type == "int64_t":
            optional_value = kwargs["optional_value"]
            content += "if ({} != {}) {{".format(value, optional_value)
        elif hasattr(value_type, "type") and (value_type.type == "enum class" or value_type.type == "bitwise enum"):
            snake_case_name = get_snake_case_name(value_type.name)
            content += inspect.cleandoc(
                """
                std::string {var_name} = {typename}ToString({var});
                if (!{var_name}.empty())
                {{
                """.format(var=value, var_name=snake_case_name, typename=value_type.name))
            value = snake_case_name
        else:
            raise RuntimeError("unknown type " + value_type.type + " " + value_type.name if hasattr(value_type, "type") else value_type)
    else:
        if hasattr(value_type, "type") and value_type.type == "enum class":
            snake_case_name = get_snake_case_name(value_type.name)
            content += "std::string {var_name} = {typename}ToString({var});".format(var=value, var_name=snake_case_name, typename=value_type.name)
            value = snake_case_name

    if value_type == "int32_t" or value_type == "int64_t":
        content += "request.AddQueryParameter({}, std::to_string({}));".format(key, value)
    else:
        content += "request.AddQueryParameter({}, {});".format(key, value)

    if optional:
        content += "}"

    if value_nullable:
        content += "}"

    global main_body
    main_body += content


def gen_add_header_code(*args, **kwargs):
    key = args[0]
    value = args[1]
    optional = kwargs["optional"]
    optional_value = kwargs.get("optional_value", None)
    value_type = kwargs[value + ".type"]
    value_nullable = kwargs.get(value + ".nullable", False)
    default_value = kwargs.get("default_value", None)

    if default_value and not optional:
        raise RuntimeError("type with default value must be optional")

    content = ""
    if value_nullable:
        content += "if ({}.HasValue()) {{\n".format(value)
        value += ".GetValue()"

    if value_type == "std::string":
        if not optional:
            content += "request.AddHeader({}, {});".format(key, value)
        else:
            content += inspect.cleandoc(
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
    elif value_type in ["int64_t", "int32_t"]:
        if not optional:
            content += "request.AddHeader({}, std::to_string({}));".format(key, value)
        else:
            content += inspect.cleandoc(
                """if ({member_name} != {member_optional_value}) {{
                    request.AddHeader({header_name}, std::to_string({member_name}));
                }}""".format(member_name=value, member_optional_value=optional_value, header_name=key))
    elif value_type == "bool":
        content += "request.AddHeader({}, {} ? \"true\":\"false\");".format(key, value)
    elif hasattr(value_type, "type") and value_type.type == "enum class":
        if not optional:
            content += "request.AddHeader({key}, {typename}ToString({value}));".format(key=key, value=value, typename=value_type.name)
        else:
            str_name = value.replace(".", "_").lower() + "_str"
            content += inspect.cleandoc(
                """
                auto {var_str} = {typename}ToString({value});
                if (!{var_str}.empty())
                {{
                    request.AddHeader({key}, {var_str});
                }}
                """.format(key=key, value=value, var_str=str_name, typename=value_type.name))
    else:
        raise RuntimeError("unknown type " + value_type.type if hasattr(value_type, "type") else value_type)

    if value_nullable:
        content += "}"

    global main_body
    main_body += content


def gen_add_range_header_code(*args, **kwargs):
    key = args[0]
    value = args[1]
    value_type = kwargs[value + ".type"]
    value_nullable = kwargs[value + ".nullable"]
    assert value_type == "std::pair<int64_t, int64_t>"

    if (value_nullable):
        content = inspect.cleandoc(
            """
            if ({var}.HasValue()) {{
                auto startOffset = {var}.GetValue().first;
                auto endOffset = {var}.GetValue().second;
                if (endOffset != std::numeric_limits<decltype(endOffset)>::max()) {{
                    request.AddHeader({key}, \"bytes=\" + std::to_string(startOffset) + \"-\" + std::to_string(endOffset));
                }}
                else {{
                    request.AddHeader({key}, \"bytes=\" + std::to_string(startOffset) + \"-\");
                }}
            }}
            """.format(key=key, var=value))
    else:
        content = "request.AddHeader({key}, \"bytes=\" + std::to_string({var}.first) + \"-\" + std::to_string({var}.second));".format(key=key, var=value)

    global main_body
    main_body += content


def gen_add_metadata_code(*args, **kwargs):
    prefix = args[0]
    value = args[1]
    content = inspect.cleandoc(
        """
        std::set<std::string> metadataKeys;
        for (const auto& pair : {1})
        {{
            std::string key = pair.first;
            std::transform(key.begin(), key.end(), key.begin(), [](unsigned char c) {{ return static_cast<char>(std::tolower(c)); }});
            if (metadataKeys.insert(key).second == false) {{
                throw std::runtime_error("duplicate keys in metadata");
            }}
            request.AddHeader({0} + pair.first, pair.second);
        }}
        metadataKeys.clear();
        """.format(prefix, value))

    global main_body
    main_body += content


def gen_get_metadata_code(*args, **kwargs):
    prefix = args[0]
    value = args[1]

    content = inspect.cleandoc(
        """
        for (auto i = httpResponse.GetHeaders().lower_bound({0}); i != httpResponse.GetHeaders().end() && i->first.substr(0, {1}) == {0}; ++i)
        {{
            {2}.emplace(i->first.substr({1}), i->second);
        }}
        """.format(prefix, len(prefix) - 2, value))

    global main_body
    main_body += content


def gen_get_or_code(*args, **kwargs):
    prefix = args[0]
    value = args[1]

    content = inspect.cleandoc(
        """
        {{
            std::map<std::string, std::vector<ObjectReplicationRule>> orPropertiesMap;
            for (auto i = httpResponse.GetHeaders().lower_bound({prefix}); i != httpResponse.GetHeaders().end() && i->first.substr(0, {prefix_len}) == {prefix}; ++i)
            {{
                const std::string& header = i->first;
                auto underscorePos = header.find('_', {prefix_len});
                if (underscorePos == std::string::npos) {{ continue; }}
                std::string policyId = std::string(header.begin() + {prefix_len}, header.begin() + underscorePos);
                std::string ruleId = header.substr(underscorePos + 1);

                ObjectReplicationRule rule;
                rule.RuleId = std::move(ruleId);
                rule.ReplicationStatus = ObjectReplicationStatusFromString(i->second);
                orPropertiesMap[policyId].emplace_back(std::move(rule));
            }}
            for (auto& property : orPropertiesMap)
            {{
                ObjectReplicationPolicy policy;
                policy.PolicyId = property.first;
                policy.Rules = std::move(property.second);
                {value}.emplace_back(std::move(policy));
            }}
        }}
        """.format(prefix=prefix, prefix_len=len(prefix) - 2, value=value))

    global main_body
    main_body += content


def gen_no_body_code(*args, **kwargs):
    response_body_type = kwargs["response_body_type"]
    http_method = kwargs["http_method"]

    content = "auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::{http_method}, url".format(http_method=http_method)
    if response_body_type == HttpBodyType.PassOn:
        content += ", true"
    content += ");"
    if http_method not in ["Get", "Head", "Delete"]:
        content += "request.AddHeader(\"Content-Length\", \"0\");"

    global main_body
    main_body += content


def gen_add_body_code(*args, **kwargs):
    response_body_type = kwargs["response_body_type"]
    http_method = kwargs["http_method"]
    content = "auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::{http_method}, url, requestBody".format(http_method=http_method)
    if response_body_type == HttpBodyType.PassOn:
        content += ", true"
    content += ");"
    content += "request.AddHeader(\"Content-Length\", std::to_string(requestBody->Length()));"

    global main_body
    main_body += content


def gen_add_xml_body_code(*args, **kwargs):
    response_body_type = kwargs["response_body_type"]
    http_method = kwargs["http_method"]
    option_type = kwargs["option_type"]

    content = inspect.cleandoc(
        """
        std::string xml_body;
        {{
            XmlWriter writer;
            {}ToXml(writer, options);
            xml_body = writer.GetDocument();
            writer.Write(XmlNode{{XmlNodeType::End}});
        }}
        """.format(option_type))

    content += inspect.cleandoc(
        """
        Azure::Core::Http::MemoryBodyStream xml_body_stream(reinterpret_cast<const uint8_t*>(xml_body.data()), xml_body.length());
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::{http_method}, url, &xml_body_stream
        """.format(http_method=http_method))

    if response_body_type == HttpBodyType.PassOn:
        content += ", true"
    content += ");"
    content += "request.AddHeader(\"Content-Length\", std::to_string(xml_body_stream.Length()));"

    global main_body
    main_body += content


def gen_get_body_code(*args, **kwargs):
    body = args[0]
    value_type = kwargs[body + ".type"]

    if value_type != "std::unique_ptr<Azure::Core::Http::BodyStream>":
        raise RuntimeError("Unknown response body type")

    content = "{0} = httpResponse.GetBodyStream();".format(body)

    global main_body
    main_body += content


def gen_get_xml_body_code(*args, **kwargs):
    return_type = kwargs["return_type"]

    content = inspect.cleandoc(
        """
        {{
            const auto& httpResponseBody = httpResponse.GetBody();
            XmlReader reader(reinterpret_cast<const char*>(httpResponseBody.data()), httpResponseBody.size());
            response = {}FromXml(reader);
        }}
        """.format(return_type))
    fromxml_classes.add(return_type)

    global main_body
    main_body += content


def gen_get_header_code(*args, **kwargs):
    key = args[0]
    target = args[1]
    target_type = kwargs[target + ".type"]
    target_nullable = kwargs[target + ".nullable"]
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

    if optional or target_nullable:
        if key == "\"x-ms-blob-content-md5\"" and target.endswith("HttpHeaders.ContentMd5"):
            ite_name = get_snake_case_name("x_ms_blob_content_md5") + "_iterator"
        else:
            ite_name = get_snake_case_name(target) + "_iterator"
        content = inspect.cleandoc(
            """
            auto {1} = httpResponse.GetHeaders().find({0});
            if ({1} != httpResponse.GetHeaders().end())
            {{
            """.format(key.lower(), ite_name))

        if target_type == "int32_t":
            content += "{} = std::stoi({}->second);".format(target, ite_name)
        elif target_type == "int64_t":
            content += "{} = std::stoll({}->second);".format(target, ite_name)
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
        if target_type == "int32_t":
            content = "{1} = std::stoi(httpResponse.GetHeaders().at({0}));".format(key.lower(), target)
        elif target_type == "int64_t":
            content = "{1} = std::stoll(httpResponse.GetHeaders().at({0}));".format(key.lower(), target)
        elif target_type == "std::string":
            content = "{1} = httpResponse.GetHeaders().at({0});".format(key.lower(), target)
        elif target_type == "bool":
            content = "{1} = httpResponse.GetHeaders().at({0}) == \"true\";".format(key.lower(), target)
        elif hasattr(target_type, "type") and target_type.type == "enum class":
            content = "{target} = {typename}FromString(httpResponse.GetHeaders().at({key}));".format(key=key.lower(), target=target, typename=target_type.name)
        else:
            raise RuntimeError("unknown type " + target_type.type if hasattr(target_type, "type") else target_type)

    global main_body
    main_body += content
