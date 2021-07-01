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
"""

pragma_once = """
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

#include <azure/core/etag.hpp>
#include <azure/core/datetime.hpp>
#include <azure/core/internal/strings.hpp>
#include <azure/core/nullable.hpp>
#include <azure/core/context.hpp>
#include <azure/core/response.hpp>
#include <azure/core/http/http.hpp>
#include <azure/core/internal/http/pipeline.hpp>
#include <azure/storage/common/crypt.hpp>
#include <azure/storage/common/internal/xml_wrapper.hpp>
#include <azure/storage/common/storage_common.hpp>
#include <azure/storage/common/storage_exception.hpp>

#include "azure/storage/{service_name}/dll_import_export.hpp"

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

constant_string = """

"""

model_definitions_begin = """
namespace Models
{
"""

model_definitions = """

"""

details_begin = """
namespace _detail 
{

    using namespace Models;

"""

details = ""

details_end = """
}  // namespace _detail

"""

model_definitions_end = """
}  // namespace Models

"""

source_model_definitions = """

"""

rest_client_begin = ""
main_body = ""
rest_client_end = ""

fromxml_classes = set()
toxml_classes = set()
toxml_options_def_cache = {}

constants_map = {}
comments_map = {}


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
    content = "namespace _detail {"
    if len(constants_map):
        for k, v in sorted(constants_map.items()):
            content += "constexpr static const char* {key} = \"{value}\";".format(key=k, value=v)
    content += "} // namespace _detail\n\n"

    global constant_string
    constant_string += content


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
    rest_client_begin = "class {} final {{ public:".format(class_name)

    rest_client_end = "}};  // class {}\n".format(class_name)


def gen_model_definition(service_name, class_name, class_def):
    if class_name.endswith("ResultInternal"):
        class_name = class_name[:-8]
        namespace_name = "_detail"
    else:
        namespace_name = ""

    if namespace_name:
        content = "namespace " + namespace_name + "{"
    else:
        content = ""
    if class_def.type == "struct":
        if class_def.comment:
            content += "\n/**\n* @brief " + class_def.comment + "\n*/\n"
        content += "{} {} final {{".format(class_def.type, class_name)
    elif class_def.type == "enum class":
        if class_def.comment:
            content += "\n/**\n* @brief " + class_def.comment + "\n*/\n"
        content += inspect.cleandoc(
            """
            class {class_name} final {{
            public:
                {class_name}() = default;
                explicit {class_name}(std::string value) : m_value(std::move(value)) {{}}
                bool operator==(const {class_name}& other) const {{ return m_value == other.m_value; }}
                bool operator!=(const {class_name}& other) const {{ return !(*this == other); }}
                const std::string& ToString() const {{ return m_value; }}
            """.format(class_name=class_name))
    elif class_def.type == "bitwise enum":
        content += "enum class {} {{".format(class_name)
    source_content = ""
    for i in range(len(class_def.member)):
        if class_def.member_comment[i]:
            content += "\n/**\n* " + class_def.member_comment[i] + "\n*/\n"
        elif class_def.type == "struct" and class_def.member[i] in comments_map:
            content += "\n/**\n* " + comments_map[class_def.member[i]] + "\n*/\n"
        if class_def.member_type[i]:
            # for struct
            if class_def.member_type[i] == class_def.member[i]:
                if class_def.member_type[i] == "Metadata" or class_def.member_type[i] == "ContentHash":
                    ns_prefix = "Storage::"
                else:
                    ns_prefix = "Models::"
            else:
                ns_prefix = ""
            if class_def.member_type[i].endswith("(ISO8601)") or class_def.member_type[i].endswith("(RFC1123)"):
                real_member_type = class_def.member_type[i][:-9]
            elif class_def.member_type[i].endswith("(ISO8601t)"):
                real_member_type = class_def.member_type[i][:-10]
            else:
                real_member_type = class_def.member_type[i]
            real_member_type = ns_prefix + real_member_type
            if class_def.member_nullable[i]:
                real_member_type = "Azure::Nullable<" + real_member_type + ">"
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
            literal = class_def.member_literal[i]
            if literal is None:
                literal = class_def.member[i]
            content += "AZ_STORAGE_{service_name}_DLLEXPORT const static {class_name} {member_name};".format(
                service_name=service_name.upper(), class_name=class_name, member_name=class_def.member[i])
            source_content += "const {class_name} {class_name}::{member_name}(\"{member_value}\");".format(class_name=class_name,
                                                                                                           member_name=class_def.member[i], member_value=literal)
    if class_def.type == "enum class":
        content += "private: std::string m_value;}};  // extensible enum {}".format(class_name)
    else:
        content += "}};  // {} {}".format(class_def.type, class_name)
    if namespace_name:
        content += "\n}"
    content += "\n\n"
    source_content += "\n\n"

    global model_definitions
    model_definitions += content
    content = ""

    global source_model_definitions
    source_model_definitions += source_content

    if class_def.type == "bitwise enum":
        # Bitwise or, and
        content = inspect.cleandoc(
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
        model_definitions += content
        content = ""

        # To string converter
        content = "inline std::string {typename}ToString(const {typename}& val) {{".format(typename=class_def.name)
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
            for (size_t i = 0; i < sizeof(value_list) / sizeof({typename}); ++i) {{
                if ((val & value_list[i]) == value_list[i]) {{
                    if (!ret.empty()) {{ ret += ","; }}
                    ret += string_list[i];
                }}
            }}
            return ret;}}
            """.format(typename=class_def.name))
        content += "\n\n"

    global details
    details += content


def gen_fromxml_function(class_name):
    global main_body

    if class_name == "Metadata":
        content = inspect.cleandoc(
            """
            static Metadata MetadataFromXml(_internal::XmlReader& reader) {
                Metadata ret;
                int depth = 0;
                std::string key;
                while (true) {
                    auto node = reader.Read();
                    if (node.Type == _internal::XmlNodeType::End) {
                        break;
                    } else if (node.Type == _internal::XmlNodeType::StartTag) {
                        if (depth++ == 0) { key = node.Name; }
                    } else if (node.Type == _internal::XmlNodeType::EndTag) {
                        if (depth-- == 0) { break; }
                    } else if (depth == 1 && node.Type == _internal::XmlNodeType::Text) {
                        ret.emplace(std::move(key), node.Value);
                    }
                }
                return ret;
            }
            """)
        main_body += content + "\n\n"
        return

    if type(class_name) is tuple:
        class_type = class_name[0]
        member_name = class_name[1]
        if class_type == "std::map<std::string, std::string>" and member_name == "Tags":
            content = inspect.cleandoc(
                """
                static std::map<std::string, std::string> {}FromXml(_internal::XmlReader& reader) {{
                    std::map<std::string, std::string> ret;
                    int depth = 0;
                    std::string key;
                    bool is_key = false;
                    bool is_value = false;
                    while (true) {{
                        auto node = reader.Read();
                        if (node.Type == _internal::XmlNodeType::End) {{
                            break;
                        }} else if (node.Type == _internal::XmlNodeType::StartTag) {{
                            ++depth;
                            if (node.Name == "Key") {{ is_key = true; }}
                            else if (node.Name == "Value") {{ is_value = true; }}
                        }} else if (node.Type == _internal::XmlNodeType::EndTag) {{
                            if (depth-- == 0) {{ break; }}
                        }}
                        if (depth == 2 && node.Type == _internal::XmlNodeType::Text) {{
                            if (is_key) {{ key = node.Value; is_key = false; }}
                            else if (is_value) {{ ret.emplace(std::move(key), node.Value); is_value = false; }}
                        }}
                    }}
                    return ret;
                }}
                """.format(member_name))
        elif class_type == "Azure::Core::Http::HttpRange":
            content = inspect.cleandoc(
                """
                static Azure::Core::Http::HttpRange {}FromXml(_internal::XmlReader& reader) {{
                    int depth = 0;
                    bool is_start = false;
                    bool is_end = false;
                    int64_t start = 0;
                    int64_t end = 0;
                    while (true) {{
                        auto node = reader.Read();
                        if (node.Type == _internal::XmlNodeType::End) {{
                            break;
                        }} else if (node.Type == _internal::XmlNodeType::StartTag && node.Name == "Start") {{
                            ++depth;
                            is_start = true;
                        }} else if (node.Type == _internal::XmlNodeType::StartTag && node.Name == "End") {{
                            ++depth;
                            is_end = true;
                        }} else if (node.Type == _internal::XmlNodeType::EndTag) {{
                            is_start = false;
                            is_end = false;
                            if (depth-- == 0) {{ break; }}
                        }}
                        if (depth == 1 && node.Type == _internal::XmlNodeType::Text) {{
                            if (is_start) {{ start = std::stoll(node.Value); }}
                            else if (is_end) {{ end = std::stoll(node.Value); }}
                        }}
                    }}
                    Azure::Core::Http::HttpRange ret;
                    ret.Offset = start;
                    ret.Length = end - start + 1;
                    return ret;
                }}
                """.format(member_name))
        elif class_type == "std::vector<ObjectReplicationPolicy>":
            content = inspect.cleandoc(
                """
                static std::vector<ObjectReplicationPolicy> {}FromXml(_internal::XmlReader& reader) {{
                    int depth = 0;
                    std::map<std::string, std::vector<ObjectReplicationRule>> orPropertiesMap;
                    std::string policyId;
                    std::string ruleId;
                    while (true) {{
                        auto node = reader.Read();
                        if (node.Type == _internal::XmlNodeType::End) {{
                            break;
                        }} else if (node.Type == _internal::XmlNodeType::StartTag) {{
                            ++depth;
                            std::string startTagName = node.Name;
                            if (startTagName.substr(0, 3) == "or-") {{
                                auto underscorePos = startTagName.find('_', 3);
                                policyId = std::string(startTagName.begin() + 3, startTagName.begin() + underscorePos);
                                ruleId = startTagName.substr(underscorePos + 1);
                            }}
                        }} else if (node.Type == _internal::XmlNodeType::EndTag) {{
                            if (depth-- == 0) {{ break; }}
                        }}
                        if (depth == 1 && node.Type == _internal::XmlNodeType::Text) {{
                            ObjectReplicationRule rule;
                            rule.RuleId = std::move(ruleId);
                            rule.ReplicationStatus = ObjectReplicationStatus(node.Value);
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

    class_internal_name = class_name
    if "_detail::" in class_internal_name:
        class_internal_name = class_name[class_name.rfind("::") + 2:] + "Internal"
    class_def = models_cache[class_internal_name]
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
        static {0} {1}FromXml(_internal::XmlReader& reader)
        {{
            {0} ret;
            enum class XmlTagName {{
        """.format(class_name, class_def.name))
    for xml_tag in all_xml_tag:
        content += "k_" + to_cpp_name(xml_tag) + ","
    content += "k_Unknown,"
    content += "};"
    content += inspect.cleandoc(  # end tag
        """
        std::vector<XmlTagName> path;
        while (true) {
            auto node = reader.Read();
            if (node.Type == _internal::XmlNodeType::End) { break; }
            else if (node.Type == _internal::XmlNodeType::EndTag) {
                if (path.size() > 0) { path.pop_back(); }
                else { break; }
            }
            else if (node.Type == _internal::XmlNodeType::StartTag) {
        """)
    # start tag
    for i, xml_tag in enumerate(all_xml_tag):
        if i != 0:
            content += "else "
        content += "if (node.Name ==  \"{0}\") {{ path.emplace_back(XmlTagName::k_{1}); }}".format(xml_tag, to_cpp_name(xml_tag))
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
            function_name = member[member.rfind(".") + 1:]
            content += "ret.{member_name} = {function_name}FromXml(reader);".format(member_name=member, function_name=function_name)
            fromxml_classes.add((member_type, function_name))
        elif member_type.startswith("std::vector<") and member_type.endswith(">"):
            inner_type = member_type[len("std::vector<"): -len(">")]
            if inner_type == "Azure::Core::Http::HttpRange":
                content += "ret.{member_name}.emplace_back({member_name}FromXml(reader));".format(member_name=member)
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
    content += "} else if (node.Type == _internal::XmlNodeType::Text) {"
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
            content += "ret.{} = node.Value == \"true\";".format(member)
        elif member_type == "std::vector<uint8_t>":
            content += "ret.{} = Azure::Core::Convert::Base64Decode(node.Value);".format(member)
        elif member_type == "std::vector<std::string>":
            content += "ret.{}.emplace_back(node.Value);".format(member)
        elif member_type in models_cache and models_cache[member_type].type == "enum class":
            content += "ret.{} = {}(node.Value);".format(member, member_type)
        elif member_type == "Azure::DateTime(ISO8601)":
            content += "ret.{} = Azure::DateTime::Parse(node.Value, Azure::DateTime::DateFormat::Rfc3339);".format(member)
        elif member_type == "Azure::DateTime(RFC1123)":
            content += "ret.{} = Azure::DateTime::Parse(node.Value, Azure::DateTime::DateFormat::Rfc1123);".format(member)
        elif member_type == "std::chrono::seconds":
            content += "ret.{} = std::chrono::seconds(node.Value == \"infinite\" ? -1 : std::stoi(node.Value));".format(member)
        elif member_type == "Azure::ETag":
            content += "ret.{} = Azure::ETag(node.Value);".format(member)
        else:
            content += "ret.{} = node.Value;".format(member)
        content += "}"
    # attribute
    for i, (path, attr_name, member) in enumerate([(a[1], a[2], a[3]) for a in class_def.fromxml_actions if a[0] == "attribute"]):
        if i == 0:
            content += "} else if (node.Type == _internal::XmlNodeType::Attribute) {"
        if i != 0:
            content += "else "
        content += "if (path.size() == {} &&".format(len(path.split(".")))
        for j, k in enumerate(path.split(".")):
            content += "path[{}] == XmlTagName::k_".format(j) + to_cpp_name(k) + "&&"
        content += "node.Name == \"{}\")".format(attr_name)
        content += "{{ ret.{} = node.Value; }}".format(member)

    content += "}} return ret;}\n\n"

    main_body += content


def gen_toxml_function(class_name):
    def toxml_content(member_name, member_type):
        if member_name.endswith(".Tags") and member_type == "std::map<std::string, std::string>":
            content = "for (const auto& i : {}) {{".format(member_name)
            content += "writer.Write(_internal::XmlNode{_internal::XmlNodeType::StartTag, \"Tag\"});"
            content += "writer.Write(_internal::XmlNode{_internal::XmlNodeType::StartTag, \"Key\"});"
            content += toxml_content("i.first", "std::string")
            content += "writer.Write(_internal::XmlNode{_internal::XmlNodeType::EndTag});"
            content += "writer.Write(_internal::XmlNode{_internal::XmlNodeType::StartTag, \"Value\"});"
            content += toxml_content("i.second", "std::string")
            content += "writer.Write(_internal::XmlNode{_internal::XmlNodeType::EndTag});"
            content += "writer.Write(_internal::XmlNode{_internal::XmlNodeType::EndTag});"
            content += "}"
        elif member_type.startswith("std::vector<") and member_type.endswith(">"):
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
            elif inner_type1 in models_cache and models_cache[inner_type1].type == "enum class":
                inner_type1_to_string += ".ToString()"
            else:
                raise RuntimeError("unknown type " + inner_type1)

            if inner_type2 == "std::string":
                pass
            else:
                raise RuntimeError("unknown type " + inner_type2)

            content = "writer.Write(_internal::XmlNode{{_internal::XmlNodeType::StartTag, {0}, {1} }});".format(inner_type1_to_string, inner_type2_to_string)
        elif member_type == "std::string":
            content = "writer.Write(_internal::XmlNode{{_internal::XmlNodeType::Text, std::string(), {}}});".format(member_name)
        elif member_type == "bool":
            content = "writer.Write(_internal::XmlNode{{_internal::XmlNodeType::Text, std::string(), {} ? \"true\":\"false\"}});".format(member_name)
        elif member_type == "Azure::DateTime(ISO8601)":
            content = "writer.Write(_internal::XmlNode{{_internal::XmlNodeType::Text, std::string(), {}.ToString(Azure::DateTime::DateFormat::Rfc3339, Azure::DateTime::TimeFractionFormat::AllDigits)}});".format(
                member_name)
        elif member_type == "Azure::DateTime(ISO8601t)":
            content = "writer.Write(_internal::XmlNode{{_internal::XmlNodeType::Text, std::string(), {}.ToString(Azure::DateTime::DateFormat::Rfc3339, Azure::DateTime::TimeFractionFormat::Truncate)}});".format(
                member_name)
        elif member_type == "Azure::DateTime(RFC1123)":
            content = "writer.Write(_internal::XmlNode{{_internal::XmlNodeType::Text, std::string(), {}.ToString(Azure::DateTime::DateFormat::Rfc1123)}});".format(member_name)
        elif member_type in ["int32_t", "int64_t"]:
            content = "writer.Write(_internal::XmlNode{{_internal::XmlNodeType::Text, std::string(), std::to_string({})}});".format(member_name)
        else:
            content = "{}ToXml(writer, {});".format(member_type, member_name)
            toxml_classes.add(member_type)
            toxml_options_def_cache[member_type] = models_cache[member_type]
        return content

    if class_name in toxml_options_def_cache:
        class_def = toxml_options_def_cache[class_name]

        content = inspect.cleandoc(
            """
            static void {0}ToXml(_internal::XmlWriter& writer, const {0}& options) {{
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
                    content += "writer.Write(_internal::XmlNode{_internal::XmlNodeType::EndTag});"
                    xml_path.pop()
                while len(xml_path) < len(target_xml_path) - 1:
                    p = target_xml_path[len(xml_path)]
                    content += "writer.Write(_internal::XmlNode{{_internal::XmlNodeType::StartTag, \"{}\"}});".format(p)
                    xml_path.append(p)
                if member_nullable:
                    content += "if (options.{}.HasValue()) {{".format(member)
                    member += ".Value()"
                last_path_added = False
                if len(xml_path) < len(target_xml_path):
                    p = target_xml_path[len(xml_path)]
                    content += "writer.Write(_internal::XmlNode{{_internal::XmlNodeType::StartTag, \"{}\"}});".format(p)
                    xml_path.append(p)
                    last_path_added = True
                content += toxml_content("options." + member, member_type)
                if last_path_added:
                    content += "writer.Write(_internal::XmlNode{_internal::XmlNodeType::EndTag});"
                    xml_path.pop()
                if member_nullable:
                    content += "}"
            else:
                raise RuntimeError("unsupported toxml action " + xml_action_type)
        while len(xml_path):
            content += "writer.Write(_internal::XmlNode{_internal::XmlNodeType::EndTag});"
            xml_path.pop()

        content += "}\n\n"
    elif class_name in models_cache:
        raise RuntimeError("generate ToXml() for no-option classes not supported yet")
    else:
        raise RuntimeError("unknown type " + class_name)

    global main_body
    main_body += content


def gen_resource_begin(resource_name):
    content = "class {} final {{ public:".format(resource_name)

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
    content = "struct {} final {{".format(class_name)
    for i in range(len(class_def.member)):
        if class_def.member_type[i] == class_def.member[i]:
            if class_def.member[i] == "Metadata" or class_def.member[i] == "ContentHash":
                ns_prefix = "Storage::"
            else:
                ns_prefix = "Models::"
        else:
            ns_prefix = ""
        if class_def.member_type[i].endswith("(ISO8601)") or class_def.member_type[i].endswith("(RFC1123)"):
            real_member_type = class_def.member_type[i][:-9]
        elif class_def.member_type[i].endswith("(ISO8601t)"):
            real_member_type = class_def.member_type[i][:-10]
        else:
            real_member_type = class_def.member_type[i]
        real_member_type = ns_prefix + real_member_type
        if class_def.member_nullable[i]:
            real_member_type = "Azure::Nullable<" + real_member_type + ">"
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
    content = "static Azure::Core::Http::Request {function_name}CreateMessage(const Azure::Core::Url& url,".format(function_name=function_name)
    if request_body_type == HttpBodyType.PassOn:
        content += "Azure::Core::IO::BodyStream& requestBody,"
    content += "const {option_type}& options) {{ (void)options;".format(option_type=option_type)

    global main_body
    main_body += content


def gen_resource_create_message_function_end():
    content = "return request; }\n\n"

    global main_body
    main_body += content


def gen_resource_create_response_function_begin(function_name, return_type):
    content = "static Azure::Response<{return_type}> {function_name}CreateResponse(std::unique_ptr<Azure::Core::Http::RawResponse> pHttpResponse, const Azure::Core::Context& context) {{ (void)context;".format(
        function_name=function_name, return_type=return_type)

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
            throw StorageException::CreateFromResponse(std::move(pHttpResponse));
        }
        """)

    global main_body
    main_body += content


def gen_resource_create_response_function_end(return_type):
    content = "return Azure::Response<{return_type}>(std::move(response), std::move(pHttpResponse));}}\n\n".format(return_type=return_type)

    global main_body
    main_body += content


def gen_resource_function_glue_function(function_name, option_type, return_type, request_body_type):
    content = "static Azure::Response<{return_type}> {function_name}(Azure::Core::Http::_internal::HttpPipeline& pipeline, const Azure::Core::Url& url,".format(
        function_name=function_name, return_type=return_type)
    if request_body_type == HttpBodyType.PassOn:
        content += "Azure::Core::IO::BodyStream& requestBody,"
    content += "const {option_type}& options, const Azure::Core::Context& context) {{".format(option_type=option_type)
    content += "auto request = {function_name}CreateMessage(url,".format(function_name=function_name, option_type=option_type)
    if request_body_type == HttpBodyType.PassOn:
        content += "requestBody,"
    content += "options);"
    content += inspect.cleandoc(
        """
        auto pHttpResponse = pipeline.Send(request, context);
        return {function_name}CreateResponse(std::move(pHttpResponse), context);
        }}
        """.format(function_name=function_name))
    content += "\n\n"

    global main_body
    main_body += content


def gen_resource_function_begin(function_name, option_type, return_type, request_body_type, response_body_type):
    content = "static Azure::Response<{return_type}> {function_name}(Azure::Core::Http::_internal::HttpPipeline& pipeline, const Azure::Core::Url& url,".format(
        function_name=function_name, return_type=return_type)
    if request_body_type == HttpBodyType.PassOn:
        content += "Azure::Core::IO::BodyStream& requestBody,"
    content += "const {option_type}& options, const Azure::Core::Context& context) {{ (void)options;".format(option_type=option_type)

    global main_body
    main_body += content


def gen_resource_send_request(return_type, http_status_code):
    content = "auto pHttpResponse = pipeline.Send(request, context);"

    global main_body
    main_body += content

    gen_resource_create_response_function_check_status_code(return_type, http_status_code)


def gen_resource_function_end(return_type):
    content = "return Azure::Response<{return_type}>(std::move(response), std::move(pHttpResponse));}}\n\n".format(return_type=return_type)

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
        value += ".Value()"

    need_encoding = True
    if value_type == "std::string" and value.startswith("\"") and value.endswith("\""):
        string_literal = value[1:-1]
        unreserved = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-._~"
        subdelimiters = "!$&'()*+,;="
        no_encode_table = (set(unreserved) | set(subdelimiters) | set("%/:@?")) - set("%+=")
        if all(c in no_encode_table for c in string_literal):
            need_encoding = False

    if optional:
        if value_type == "std::string":
            content += "if (!{}.empty()) {{".format(value)
        elif value_type == "int32_t" or value_type == "int64_t":
            optional_value = kwargs["optional_value"]
            content += "if ({} != {}) {{".format(value, optional_value)
        elif hasattr(value_type, "type") and value_type.type == "bitwise enum":
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
            value += ".ToString()"

    if value_type == "int32_t" or value_type == "int64_t":
        content += "request.GetUrl().AppendQueryParameter({}, std::to_string({}));".format(key, value)
    elif not need_encoding:
        content += "request.GetUrl().AppendQueryParameter({}, {});".format(key, value)
    else:
        content += "request.GetUrl().AppendQueryParameter({}, _internal::UrlEncodeQueryParameter({}));".format(key, value)

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
        value += ".Value()"

    if value_type == "std::vector<uint8_t>":
        value = "Azure::Core::Convert::Base64Encode(" + value + ")"
        value_type = "std::string"

    if value_type == "std::string":
        if not optional:
            content += "request.SetHeader({}, {});".format(key, value)
        else:
            content += inspect.cleandoc(
                """
                if (!{1}.empty())
                {{
                    request.SetHeader({0}, {1});
                }}
                """.format(key, value))
            if default_value:
                content += inspect.cleandoc(
                    """
                    else
                    {{
                        request.SetHeader({0}, {1});
                    }}
                    """.format(key, default_value))
    elif value_type in ["int64_t", "int32_t"]:
        if not optional:
            content += "request.SetHeader({}, std::to_string({}));".format(key, value)
        else:
            content += inspect.cleandoc(
                """if ({member_name} != {member_optional_value}) {{
                    request.SetHeader({header_name}, std::to_string({member_name}));
                }}""".format(member_name=value, member_optional_value=optional_value, header_name=key))
    elif value_type == "bool":
        content += "request.SetHeader({}, {} ? \"true\":\"false\");".format(key, value)
    elif value_type == "std::chrono::seconds":
        content += "request.SetHeader({}, std::to_string({}.count()));".format(key, value)
    elif value_type == "Azure::DateTime(RFC1123)":
        content += "request.SetHeader({}, {}.ToString(Azure::DateTime::DateFormat::Rfc1123));".format(key, value)
    elif value_type == "Azure::ETag":
        assert optional
        content += inspect.cleandoc(
            """
            if ({value}.HasValue() && !{value}.ToString().empty())
            {{
                request.SetHeader({key}, {value}.ToString());
            }}
            """.format(key=key, value=value))
    elif hasattr(value_type, "type") and value_type.type == "enum class":
        if not optional:
            content += "request.SetHeader({key}, {value}.ToString());".format(key=key, value=value)
        else:
            content += inspect.cleandoc(
                """
                if (!{value}.ToString().empty())
                {{
                    request.SetHeader({key}, {value}.ToString());
                }}
                """.format(key=key, value=value))
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
    assert value_type == "Azure::Core::Http::HttpRange"

    if value_nullable:
        content = "if ({}.HasValue())".format(value)
        value += ".Value()"
    else:
        content = ""

    content += inspect.cleandoc(
        """
        {{
            std::string headerValue = \"bytes=\" + std::to_string({var}.Offset) + "-";
            if ({var}.Length.HasValue()) {{
                headerValue += std::to_string({var}.Offset + {var}.Length.Value() - 1);
            }}
            request.SetHeader({key}, std::move(headerValue));
        }}
        """.format(key=key, var=value))

    global main_body
    main_body += content


def gen_add_metadata_code(*args, **kwargs):
    prefix = args[0]
    value = args[1]
    content = inspect.cleandoc(
        """
        for (const auto& pair : {1})
        {{
            request.SetHeader({0} + pair.first, pair.second);
        }}
        """.format(prefix, value))

    global main_body
    main_body += content


def gen_add_content_hash_code(*args, **kwargs):
    value = args[0]
    value_nullable = kwargs[value + ".nullable"]

    if value_nullable:
        content = "if ({var}.HasValue()) {{".format(var=value)
        value += ".Value()"
    else:
        content = ""

    content += inspect.cleandoc(
        """
        if ({var}.Algorithm == HashAlgorithm::Md5) {{
            request.SetHeader("Content-MD5", Azure::Core::Convert::Base64Encode({var}.Value));
        }}
        else if ({var}.Algorithm == HashAlgorithm::Crc64) {{
            request.SetHeader("x-ms-content-crc64", Azure::Core::Convert::Base64Encode({var}.Value));
        }}
        """.format(var=value))

    if value_nullable:
        content += "}"

    global main_body
    main_body += content


def gen_add_source_content_hash_code(*args, **kwargs):
    value = args[0]
    value_nullable = kwargs[value + ".nullable"]

    if value_nullable:
        content = "if ({var}.HasValue()) {{".format(var=value)
        value += ".Value()"
    else:
        content = ""
    content += inspect.cleandoc(
        """
        if ({var}.Algorithm == HashAlgorithm::Md5) {{
            request.SetHeader("x-ms-source-content-md5", Azure::Core::Convert::Base64Encode({var}.Value));
        }}
        else if ({var}.Algorithm == HashAlgorithm::Crc64) {{
            request.SetHeader("x-ms-source-content-crc64", Azure::Core::Convert::Base64Encode({var}.Value));
        }}
        """.format(var=value))
    if value_nullable:
        content += "}"

    global main_body
    main_body += content


def gen_add_hash_algorithm_code(*args, **kwargs):
    value = args[0]
    value_nullable = kwargs[value + ".nullable"]

    assert value_nullable

    content = inspect.cleandoc(
        """
        if ({var}.HasValue()) {{
            if ({var}.Value()== HashAlgorithm::Md5) {{
                request.SetHeader("x-ms-range-get-content-md5", "true");
            }}
            else if ({var}.Value()== HashAlgorithm::Crc64) {{
                request.SetHeader("x-ms-range-get-content-crc64", "true");
            }}
        }}
        """.format(var=value))

    global main_body
    main_body += content


def gen_get_content_hash_code(*args, **kwargs):
    value = args[0]

    content = inspect.cleandoc(
        """
        {{
            const auto& headers = httpResponse.GetHeaders();
            auto content_md5_iterator = headers.find("content-md5");
            if (content_md5_iterator != headers.end()) {{
                ContentHash hash;
                hash.Algorithm = HashAlgorithm::Md5;
                hash.Value = Azure::Core::Convert::Base64Decode(content_md5_iterator->second);
                {var} = std::move(hash);
            }}
            auto x_ms_content_crc64_iterator = headers.find("x-ms-content-crc64");
            if (x_ms_content_crc64_iterator != headers.end()) {{
                ContentHash hash;
                hash.Algorithm = HashAlgorithm::Crc64;
                hash.Value = Azure::Core::Convert::Base64Decode(x_ms_content_crc64_iterator->second);
                {var} = std::move(hash);
            }}
        }}
        """.format(var=value))

    global main_body
    main_body += content


def gen_get_content_range_code(*args, **kwargs):
    key = args[0]
    target = args[1]
    target_type = kwargs[target + ".type"]
    target_nullable = kwargs[target + ".nullable"]

    key2 = "\"Content-Length\""

    if target_type == "Azure::Core::Http::HttpRange":
        content = inspect.cleandoc(
            """
        auto content_range_iterator = httpResponse.GetHeaders().find({key});
        if (content_range_iterator != httpResponse.GetHeaders().end()) {{
            const std::string& content_range = content_range_iterator->second;
            auto bytes_pos = content_range.find("bytes ");
            auto dash_pos = content_range.find("-", bytes_pos + 6);
            auto slash_pos = content_range.find("/", dash_pos + 1);
            int64_t range_start_offset = std::stoll(std::string(content_range.begin() + bytes_pos + 6, content_range.begin() + dash_pos));
            int64_t range_end_offset = std::stoll(std::string(content_range.begin() + dash_pos + 1, content_range.begin() + slash_pos));
            {target} = Azure::Core::Http::HttpRange{{range_start_offset, range_end_offset - range_start_offset + 1}};
        }}
        else {{
            {target} = Azure::Core::Http::HttpRange{{0, std::stoll(httpResponse.GetHeaders().at({key2}))}};
        }}
        """.format(key=key.lower(), key2=key2.lower(), target=target))
    elif target_type == "int64_t":
        content = inspect.cleandoc(
            """
        if (content_range_iterator != httpResponse.GetHeaders().end()) {{
            const std::string& content_range = content_range_iterator->second;
            auto slash_pos = content_range.find("/");
            {target} = std::stoll(content_range.substr(slash_pos + 1));
        }}
        else {{
            {target} = std::stoll(httpResponse.GetHeaders().at({key2}));
        }}
        """.format(key=key.lower(), key2=key2.lower(), target=target))
    else:
        raise RuntimeError("Cannot parse Content-Range to " + target_type)

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
                rule.ReplicationStatus = ObjectReplicationStatus(i->second);
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
        content += ", false"
    content += ");"
    if http_method not in ["Get", "Head", "Delete"]:
        content += "request.SetHeader(\"Content-Length\", \"0\");"

    global main_body
    main_body += content


def gen_add_body_code(*args, **kwargs):
    response_body_type = kwargs["response_body_type"]
    http_method = kwargs["http_method"]
    content = "auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::{http_method}, url, &requestBody".format(http_method=http_method)
    if response_body_type == HttpBodyType.PassOn:
        content += ", false"
    content += ");"
    content += "request.SetHeader(\"Content-Length\", std::to_string(requestBody.Length()));"

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
            _internal::XmlWriter writer;
            {}ToXml(writer, options);
            xml_body = writer.GetDocument();
            writer.Write(_internal::XmlNode{{_internal::XmlNodeType::End}});
        }}
        """.format(option_type))

    content += inspect.cleandoc(
        """
        Azure::Core::IO::MemoryBodyStream xml_body_stream(reinterpret_cast<const uint8_t*>(xml_body.data()), xml_body.length());
        auto request = Azure::Core::Http::Request(Azure::Core::Http::HttpMethod::{http_method}, url, &xml_body_stream
        """.format(http_method=http_method))

    if response_body_type == HttpBodyType.PassOn:
        content += ", true"
    content += ");"
    content += "request.SetHeader(\"Content-Length\", std::to_string(xml_body_stream.Length()));"

    global main_body
    main_body += content


def gen_get_body_code(*args, **kwargs):
    body = args[0]
    value_type = kwargs[body + ".type"]

    if value_type != "std::unique_ptr<Azure::Core::IO::BodyStream>":
        raise RuntimeError("Unknown response body type")

    content = "{0} = httpResponse.ExtractBodyStream();".format(body)

    global main_body
    main_body += content


def gen_get_xml_body_code(*args, **kwargs):
    return_type = kwargs["return_type"]

    class_internal_name = return_type
    if "_detail::" in class_internal_name:
        class_internal_name = return_type[return_type.rfind("::") + 2:] + "Internal"
    content = inspect.cleandoc(
        """
        {{
            const auto& httpResponseBody = httpResponse.GetBody();
            _internal::XmlReader reader(reinterpret_cast<const char*>(httpResponseBody.data()), httpResponseBody.size());
            response = {}FromXml(reader);
        }}
        """.format(class_internal_name))
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
    on_status = kwargs["on_status"] if "on_status" in kwargs else []

    content = ""
    if on_status:
        content += "if ("
        content += "||".join(["http_status_code == {}".format(s) for s in on_status])
        content += ") {"

    if optional or target_nullable:
        ite_name = get_snake_case_name(key) + "_iterator"
        content += inspect.cleandoc(
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
        elif target_type == "std::vector<uint8_t>":
            content += "{} = Azure::Core::Convert::Base64Decode({}->second);".format(target, ite_name)
        elif target_type == "bool":
            content += "{} = {}->second == \"true\";".format(target, ite_name)
        elif target_type == "std::chrono::seconds":
            content += "{target} = std::chrono::seconds({ite}->second == \"infinite\" ? -1 : std::stoi({ite}->second));".format(target=target, ite=ite_name)
        elif target_type == "Azure::DateTime(ISO8601)":
            content += "{} = Azure::DateTime::Parse({}->second, Azure::DateTime::DateFormat::Rfc3339);".format(target, ite_name)
        elif target_type == "Azure::DateTime(RFC1123)":
            content += "{} = Azure::DateTime::Parse({}->second, Azure::DateTime::DateFormat::Rfc1123);".format(target, ite_name)
        elif hasattr(target_type, "type") and target_type.type == "enum class":
            content += "{target} = {target_type}({ite}->second);".format(target=target, ite=ite_name, target_type=target_type.name)
        else:
            raise RuntimeError("unknown type " + target_type.type if hasattr(target_type, "type") else target_type)

        content += "}"
    else:
        if target_type == "int32_t":
            content += "{1} = std::stoi(httpResponse.GetHeaders().at({0}));".format(key.lower(), target)
        elif target_type == "int64_t":
            content += "{1} = std::stoll(httpResponse.GetHeaders().at({0}));".format(key.lower(), target)
        elif target_type == "std::string":
            content += "{1} = httpResponse.GetHeaders().at({0});".format(key.lower(), target)
        elif target_type == "bool":
            content += "{1} = httpResponse.GetHeaders().at({0}) == \"true\";".format(key.lower(), target)
        elif target_type == "Azure::DateTime(ISO8601)":
            content += "{1} = Azure::DateTime::Parse(httpResponse.GetHeaders().at({0}), Azure::DateTime::DateFormat::Rfc3339);".format(key.lower(), target)
        elif target_type == "Azure::DateTime(RFC1123)":
            content += "{1} = Azure::DateTime::Parse(httpResponse.GetHeaders().at({0}), Azure::DateTime::DateFormat::Rfc1123);".format(key.lower(), target)
        elif target_type == "Azure::ETag":
            content += "{1} = Azure::ETag(httpResponse.GetHeaders().at({0}));".format(key.lower(), target)
        elif hasattr(target_type, "type") and target_type.type == "enum class":
            content += "{target} = {target_type}(httpResponse.GetHeaders().at({key}));".format(key=key.lower(), target=target, target_type=target_type.name)
        else:
            raise RuntimeError("unknown type " + target_type.type if hasattr(target_type, "type") else target_type)

    if on_status:
        content += "}"

    global main_body
    main_body += content
