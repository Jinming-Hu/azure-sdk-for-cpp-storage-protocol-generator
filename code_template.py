import inspect

models_cache = {}

global_header = """
// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
"""

include_headers = """
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <iostream>
#include <functional>
#include <stdexcept>

#include "json.hpp"
#include "nullable.hpp"
#include "http/http.hpp"
#include "http/pipeline.hpp"
#include "common/storage_error.hpp"
"""

namespace_begin = ""

namespace_end = ""

details_namespace_begin = "namespace Details {"
details_namespace_end = "} // namespace Details"

parameter_string = ""
model_definitions = ""
rest_client_begin = ""
main_body = ""
rest_client_end = ""

c_API_VERSION = ""
c_API_VERSION_CONST_NAME = "c_DefaultServiceApiVersion"
c_PARAMETER_CPP_TYPE = "constexpr static const char*"

def gen_service_namespace(service_name):
    global namespace_begin
    global namespace_end

    namespace_begin = "\nnamespace Azure  {{  namespace Storage  {{  namespace  {}  {{\n".format(service_name)

    namespace_end = "\n}}}}}} // Azure::Storage::{}\n".format(service_name)

def gen_rest_client(service_name):
    global rest_client_begin
    global rest_client_end

    if service_name.endswith("s"):
        service_name = service_name[:-1]
    class_name = service_name + "RestClient"
    rest_client_begin = "class {} {{ public:".format(class_name)
    rest_client_begin += "\n"
    rest_client_end = "}};  // class {}\n".format(class_name)

def get_reference_type_from_ref(ref_dict):
    if ref_dict == None:
        raise RuntimeError("ref_dict should not be null.")
    result = ref_dict.get("$ref")
    if result == None:
        raise RuntimeError("There should be a {'$ref' : '#/definitions/#itemName'} formatted dictionary.")
    result = result.replace("#/definitions/", "")
    return result.replace("#/parameters/", "")

def cpp_name_unify(str):
    result = ""
    # split on '-'
    l = str.split("-")
    result += ("".join(string[0].upper() + string[1:] for string in l))
    return result[0].upper() + result[1:]

def get_cpp_type_from_value(key, value):
    if isinstance(value, dict):
        value_type = value.get("type")
    else:
        value_type = value.type
    if value_type == "string":
        if value.get("enum") != None and len(value.get("enum")) > 1:
            return value.get("x-ms-enum").get("name")
        else:
            return "std::string"
    elif value_type == "integer":
        format = value.get("format")
        if format:
            return "int64_t" if format == "int64" else "int32_t"
        else:
            return "int32_t"
    elif value_type == "boolean":
        return "bool"
    elif value_type == "array":
        return "std::vector<{}>".format(get_cpp_type_from_value(key, value.get("items")))
    if value_type == "object":
        return key[0].upper() + key[1:]
    elif value_type == None:
        return get_reference_type_from_ref(value)
    else:
        raise RuntimeError("Not supported value type: " + value_type)

def get_cpp_type_nullable_from_value(key, value):
    is_required = True
    if isinstance(value, dict):
        is_required = False if value.get("required") == False else True
    else:
        is_required = value.isRequired
    if not is_required:
        return "Azure::Core::Nullable<{}>".format(get_cpp_type_from_value(key, value))
    else:
        return get_cpp_type_from_value(key, value)

def get_cpp_nullable_type_from_parameter(parameter):
    if parameter.isRequired:
        return get_cpp_type_from_parameter(parameter)  
    else:
        return "Azure::Core::Nullable<{}>".format(get_cpp_type_from_parameter(parameter))

def get_cpp_type_from_parameter(parameter):
    myType = parameter.type
    name = parameter.name
    if myType == "string":
        if parameter.referencedEnum != None:
            return parameter.referencedEnum.get("name")
        else:
            return "std::string"
    elif myType == "integer":
        format = parameter.format
        if format:
            return "int64_t" if format == "int64" else "int32_t"
        else:
            return "int32_t"
    elif myType == "boolean":
        return "bool"
    if myType == "object":
        return name[0].upper() + name[1:]
    elif myType == "array":
        return "std::vector<{}>".format(parameter.arrayItemType)
    else:
        raise RuntimeError("Not supported value type: " + myType)

def get_cpp_comment_from_value(value):
    if hasattr(value, 'description'):
        if value.description != None:
            return "// " + value.description + "\n"
    if not isinstance(value, dict):
        return ""
    comment = value.get("description")
    # TODO: Get reference type's comments
    if comment != None:
        return " // " + comment + "\n"
    else:
        return ""

def gen_parameter_code(parameterObject):
    usedIn = parameterObject.usedIn
    if usedIn == "header" or usedIn == "query":
        if parameterObject.type == "string" or \
        parameterObject.type == "integer" or \
        parameterObject.type == "boolean":
            parameterCppType = c_PARAMETER_CPP_TYPE
        else:
            return
        return "{} {} = \"{}\";\n".format(parameterCppType, parameterObject.parameterName, parameterObject.actualName)
    if parameterObject.default != None:
        parameterCppType = c_PARAMETER_CPP_TYPE
        parameterName = "c_" + parameterObject.usedIn[0].upper() + parameterObject.usedIn[1:] + cpp_name_unify(parameterObject.name)
        return "{} {}Default = \"{}\";\n".format(parameterCppType, parameterName, parameterObject.default)


def gen_get_xml_node_value_with_key(nodeName, key):
    return gen_get_xml_node_value(gen_get_xml_node(nodeName, key))

def gen_get_xml_node(nodeName, key):
    return "{}[\"{}\"]".format(nodeName, key)

def gen_get_xml_node_value(nodeCode):
    return "{}.value".format(nodeCode)

def gen_get_xml_node_key(nodeCode):
    return "{}.key".format(nodeCode)

def gen_model_from_xml_code(model, models):
    result = "\nstatic {} CreateFromXml(const XmlNode& node)\n{{\n".format(model.name)
    result += "{} result;\n".format(model.name)
    # Deal with attributes.
    for k, v in model.properties.items():
        memberName = cpp_name_unify(k)
        if v.get("xml") and v.get("xml").get("attribute"):
            result += "result.{} = node.getAttribute(\"{}\");\n".format(memberName, k)
        elif v.get("type") == "array":
            # TODO: figure out how the enumeration should be in this case.
            result += "for (const auto& n : node)\n{\n"
            if v.get("items").get("$ref"):
                memberObjectName = get_reference_type_from_ref(v.get("items"))
                result += "result.{}.push_back({}::CreateFromXml({}));\n".format(memberName, memberObjectName, gen_get_xml_node("n", models[memberObjectName].xmlTag))
            else:
                result += "result.{}.push_back({});\n".format(memberName, gen_get_xml_node_value_with_key("n", v.get("items").get("xml").get("name")))
            result += "}\n"
        elif v.get("$ref"):
            memberObjectName = get_reference_type_from_ref(v)
            result += gen_ref_from_xml_code(models[memberObjectName], memberName)
        else:
            result += "result.{} = {};\n".format(memberName, gen_get_xml_node_value_with_key("node", k))
    result += "return result;\n}\n"
    return result

def gen_ref_from_xml_code(model, memberName):
    if model.type == "object":
        return "result.{} = {}::CreateFromXml({});\n".format(memberName, model.name, gen_get_xml_node("node", model.xmlTag))
    elif model.type == "enum":
        return "result.{} = {}FromString({});\n".format(memberName, model.enumName, gen_get_xml_node_value_with_key("node", model.name))
    elif model.type == "dictionary":
        return "for (const auto& n : {})\n{{\nresult.{}[{}] = {};\n}}\n".format(gen_get_xml_node_value_with_key("node", model.xmlTag), memberName, gen_get_xml_node_key("n"), gen_get_xml_node_value("n"))
    else:
        raise RuntimeError("Not supported model type: " + model.type)

def gen_ref_to_xml_code(model, memberName):
    if model.type == "object":
        return "result.AddChildNode({}::SerializeToXml(object.{}));\n".format(model.name, memberName)
    elif model.type == "enum":
        return "result.AddChildNode(XmlNode(\"{}\", {}ToString(object.{})));\n".format(model.xmlTag if hasattr(model, "xmlTag") else model.name, model.enumName, memberName)
    elif model.type == "dictionary":
        print ("Dictionary is skipped when generating to_xml methods.")
        return ""
    else:
        raise RuntimeError("Not supported model type: " + model.type)

def gen_get_json_node_value(nodeName, key, cppType):
    if cppType == "std::string":
        return "{}.get<std::string>()".format(gen_get_json_node(nodeName, key))
    elif cppType == "int64_t":
        return "std::stoll({}.get<std::string>())".format(gen_get_json_node(nodeName, key))
    elif cppType == "int32_t":
        return "std::stoi({}.get<std::string>())".format(gen_get_json_node(nodeName, key))
    elif cppType == "bool":
        return "({}.get<std::string>() == \"true\")".format(gen_get_json_node(nodeName, key))

def gen_get_json_node(nodeName, key):
    return "{}[\"{}\"]".format(nodeName, key)

def gen_model_from_json_code(model, models):
    result = "\nstatic {} CreateFromJson(const nlohmann::json& node)\n{{\n".format(model.name)
    result += "{} result;\n".format(model.name)
    # Deal with attributes.
    for k, v in model.properties.items():
        memberName = cpp_name_unify(k)
        if v.get("type") == "array":
            result += "for (const auto& element : node[\"{}\"])\n{{\n".format(k)
            if v.get("items").get("$ref"):
                memberObjectName = get_reference_type_from_ref(v.get("items"))
                result += "result.{}.emplace_back({}::CreateFromJson(element));\n".format(memberName, memberObjectName)
            result += "}\n"
        elif v.get("$ref"):
            memberObjectName = get_reference_type_from_ref(v)
            result += gen_ref_from_json_code(models[memberObjectName], memberName)
        else:
            result += "result.{} = {};\n".format(memberName, gen_get_json_node_value("node", k, get_cpp_type_nullable_from_value(k, v)))
    result += "return result;\n}\n"
    return result

def gen_ref_from_json_code(model, memberName):
    if model.type == "object":
        return "result.{} = {}::CreateFromJson({});\n".format(memberName, model.name, gen_get_json_node("node", model.name))
    else:
        raise RuntimeError("Not supported model type: " + model.type)

def gen_model_code(model, models, serializationFormat):
    global model_definitions
    # Gen class comment
    content = get_cpp_comment_from_value(model)
    name = model.name
    # Gen model declaration
    if model.type == "object":
        model_type = "struct"
    elif model.type == "enum":
        if not hasattr(model, "enumName"):
            # Skip on one value enums.
            return
        name = model.enumName
        model_type = "enum class"
    elif model.type == "dictionary":
        content += "typedef std::map<std::string, std::string> {};\n\n".format(name)
        return content
    elif model.type == "array":
        # raise RuntimeWarning("Array is skipped when generating models")
        print ("Array is skipped when generating models.")
        return
    else:
        raise RuntimeError("Not supported model type: " + model.type)

    content += "{} {}\n{{\n".format(model_type, name)

    # TODO: Combine this if else with the first one in this function.
    # TODO: Create separate functions for struct/enum
    if model.type == "object":
        # Gen object model
        # Gen subclasses
        for subclass in model.subclasses:
            content += "\n" + gen_model_code(subclass, models, serializationFormat)
        for k, v in model.properties.items():
            parameterType = get_cpp_type_nullable_from_value(k, v)
            content +=  parameterType + " " + cpp_name_unify(k)
            # defaultValue = " = {}()".format(parameterType) if v.get("type") == "integer" or v.get("type") == "boolean" else ""
            defaultValue = ""
            content += "{};".format(defaultValue)
            # Comment block
            comment = get_cpp_comment_from_value(v)
            content += comment if comment else "\n"
    elif model.type == "enum":
        # Gen enum model
        for enumName, enumString in model.enum.items():
            content += enumName + ",\n"
        content += "Unknown\n};\n\n"
        # Gen enum to string
        # Gen enum from string
        camel_case_name = name[0].lower() + name[1:]
        # To string converter
        content += inspect.cleandoc(
            """
            inline std::string {0}ToString(const {0}& {1})
            {{
                switch ({1})
                {{
            """.format(name, camel_case_name))

        for enumName, enumString in model.enum.items():
            content += "case {}::{}: return \"{}\";".format(name, enumName, enumString)

        content += "default: return std::string(); }}\n\n"

        # From string converter
        content += inspect.cleandoc(
            """
            inline {0} {0}FromString(const std::string& {1})
            {{
            """.format(name, camel_case_name))

        for enumName, enumString in model.enum.items():
            content += "if ({} == \"{}\") {{ return {}::{}; }}".format(camel_case_name, enumString, name, enumName)

        # TODO: Throw storage error instead?
        content += "throw std::runtime_error(\"Cannot convert \" + {1} + \" to {0}\");\n}}\n\n".format(name, camel_case_name)

    if serializationFormat == "xml":
        # Generate From/To XML Code.
        if model.xml:
            content += gen_model_from_xml_code(model, models)
        # TODO: Generate only for those used in request bodies.
        # if model.usedIn == "body":
            content += gen_model_to_xml_code(model, models)
    elif serializationFormat == "json":
        # Generate From JSON Code since there isn't ToJson needed for ADLS at the moment.
        if hasattr(model, "properties"):
            # Generate From XML code for error
            if "Error" in model.name:
                # TODO: modify the xml's generation
                # content += gen_model_from_xml_code(model, models)
                pass
            else:
                content += gen_model_from_json_code(model, models)

    if model.type == "object":
        content += "};\n\n"
    return content

def gen_model_to_xml_code(model, models):
    if model.type != "object":
        return ""
    # TODO: Serialize to BodyBuffer/BodyStream instead.
    result = "\nstatic XmlNode SerializeToXml(const {}& object)\n{{\n".format(model.name)
    result += "XmlNode result;\n"
        # Deal with attributes.
    for k, v in model.properties.items():
        memberName = cpp_name_unify(k)
        if v.get("xml") and v.get("xml").get("attribute"):
            # TODO: Support attributes.
            continue
        elif v.get("type") == "array":
            # TODO: figure out how the enumeration should be in this case.
            result += "result.addChildNode(XmlEmptyArrayNode(\"{}\"));\n".format(k)
            result += "for (const auto& item : object.{})\n{{\n".format(memberName)
            if v.get("items").get("$ref"):
                memberObjectName = get_reference_type_from_ref(v.get("items"))
                result += "{}.AddChildNode({}::SerializeToXml(item));\n".format(gen_get_xml_node("result", k), memberObjectName)
            else:
                result += "{}.AddChildNode(XmlNode(\"{}\", item));\n".format(gen_get_xml_node("result", k), v.get("items").get("xml").get("name"))
            result += "}\n"
        elif v.get("$ref"):
            memberObjectName = get_reference_type_from_ref(v)
            result += gen_ref_to_xml_code(models[memberObjectName], memberName)
        else:
            result += "result.AddChildNode(XmlNode(\"{}\", object.{}));\n".format(k, memberName)
    result += "return result;\n}\n"
    return result

def get_inline_member_name(parameter):
    if parameter.get("x-ms-enum") != None:
        return parameter.get("x-ms-enum").get("name")
    else:
        return cpp_name_unify(parameter.get("name"))

def gen_method_code(rest_client_subclasses, method, parameters, models, serializationFormat):
    publicContent = ""
    privateContent = ""
    publicContent += gen_method_options_code(method, parameters, models)
    privateContent += gen_method_create_request_code(method, parameters, models, serializationFormat)
    privateContent += gen_method_create_response_code(method, parameters, models, serializationFormat)
    publicContent += gen_method_run_code(method, parameters, models)
    if not method.className in rest_client_subclasses:
        rest_client_subclasses[method.className] = { "public:": "", "private:": ""}
    rest_client_subclasses[method.className]["public:"] += publicContent
    rest_client_subclasses[method.className]["private:"] += privateContent

def gen_subclasses(rest_client_subclasses):
    content = ""
    for k,v in rest_client_subclasses.items():
        content += "class {}\n{{\n".format(k)
        content += "public:\n"
        content += v["public:"]
        content += "private:\n"
        content += v["private:"]
        content += "};\n\n"
    return content


def gen_method_options_member_code(methodParameters, models, parameters):
    result = ""
    for methodParameter in methodParameters:
        parameterComment = ""
        defaultValue = ""
        if methodParameter.get("schema") != None:
            # parameter is an object reference.
            parameterRefType = get_reference_type_from_ref(methodParameter.get("schema"))
            parameterModel = models[parameterRefType]
            parameterType = get_cpp_type_nullable_from_value(parameterModel.name, parameterModel)
            parameterComment = " // {}\n".format(parameterModel.description)
            # if methodParameter.get("type") == "integer" or methodParameter.get("type") == "boolean":
            #     # TODO: What if type is pointer.
            #     defaultValue = " = {}()".format(parameterType)
        elif methodParameter.get("type") != None:
            # parameter is an inline type.
            if methodParameter.get("enum") != None:
                if len(methodParameter.get("enum")) == 1:
                    # constant
                    continue
                else:
                    model = models[methodParameter.get("x-ms-enum").get("name")]
                    if model == None:
                        raise RuntimeError("Model should not be none for: " + methodParameter.get("name"))
                    parameterType = model.enumName
                    if not model.isRequired:
                        parameterType = "Azure::Core::Nullable<{}>".format(parameterType)
                    parameterComment = " // {}\n".format(model.description)
                    if hasattr(model, "objectName"):
                        parameterRefType = cpp_name_unify(model.objectName) if model.objectName else (model.name)
                    else:
                        parameterRefType = cpp_name_unify(model.name)
                    # if not methodParameter.get("required"):
                    #     defaultValue = " = {}::Unknown".format(parameterType)
            else:
                parameterType = get_cpp_type_nullable_from_value("", methodParameter)
                parameterComment = " // {}\n".format(methodParameter.get("description"))
                parameterRefType = get_inline_member_name(methodParameter)
                # if methodParameter.get("type") == "integer" or methodParameter.get("type") == "boolean":
                #     defaultValue = " = {}()".format(parameterType)
        else:
            parameterRefType = get_reference_type_from_ref(methodParameter)
            if parameterRefType == "Body":
                parameterType = "std::unique_ptr<Azure::Core::Http::BodyStream>"
                parameterComment = " // The stream that contains the body of this request.\n"
                defaultValue = ""
            else:
                parameter = parameters[parameterRefType]
                if parameter == None:
                    raise RuntimeError("Parameter should not be None for: " + parameterRefType)
                if hasattr(parameter, "defaultValue"):
                    if parameter.name != "ApiVersionParameter":
                        # Constant
                        continue
                if parameter.enum and parameter.name != "ApiVersionParameter":
                    parameterRefType = cpp_name_unify(parameter.actualName)
                # Get the actual C++ type for the parameter
                parameterType = get_cpp_nullable_type_from_parameter(parameter)
                parameterComment = " // {}\n".format(parameter.description)
                if parameter.name == "Metadata":
                    result += "std::map<std::string, std::string> {} = std::map<std::string, std::string>();{}".format(parameter.name, parameterComment)
                    continue
                if (parameter.isRequired) and (parameter.type == "integer" or parameter.type == "boolean"):
                    defaultValue = " = {}()".format(parameterType)
                if parameter.name == "ApiVersionParameter":
                    defaultValue = " = Details::{}".format(c_API_VERSION_CONST_NAME)
        result += "{} {}{};{}".format(parameterType, parameterRefType, defaultValue, parameterComment)
    return result

def gen_method_options_code(method, parameters, models):
    content = ""
    optionsName = method.methodName + "Options"
    content += "struct {}\n{{\n".format(optionsName)
    # Construct options for method.
    # Construct path's options.
    content += gen_method_options_member_code(method.pathParameters, models, parameters) if method.pathParameters else ""
    # Construct specific method's options.
    content += gen_method_options_member_code(method.parameters, models, parameters) if method.parameters else ""

    content += "\n};\n\n"
    return content

def gen_adding_parameter_in_create_request_code(parameterRefType, parameter, methodOptionsObjectName, models):
    if parameter == None:
        raise RuntimeError("Parameter should not be None for: " + parameterRefType)
    if parameter.name == "ApiVersionParameter":
        return "request.AddHeader(Details::{}, {}.{});\n".format(parameter.parameterName, methodOptionsObjectName, parameter.name)
    
    nullableGetValue = "" if parameter.isRequired else ".GetValue()"
    parameterName = parameter.name
    if parameter.type == "integer":
        parameterAsArgument = "std::to_string({}.{})".format(methodOptionsObjectName, parameterName + nullableGetValue)
    elif parameter.type == "boolean":
        parameterAsArgument = "({}.{} ? \"true\" : \"false\")".format(methodOptionsObjectName, parameterName + nullableGetValue)
    else:
        if parameter.referencedEnum != None:
            if hasattr(parameter, "defaultValue"):
                if parameter.isRequired:
                    parameterAsArgument = "\"{}\"".format(parameter.defaultValue)
                else:
                    raise RuntimeError("Single enum value should be mandatory. Enum name: " + parameterName)
            else:
                model = models[parameter.referencedEnum.get("name")]
                parameterName = cpp_name_unify(model.objectName)
                parameterAsArgument = "{}ToString({}.{})".format(model.enumName, methodOptionsObjectName,  parameterName + nullableGetValue)
        elif parameter.enum != None:
            parameterAsArgument = "\"{}\"".format(parameter.defaultValue)
        else:
            parameterAsArgument = "{}.{}".format(methodOptionsObjectName, parameterName + nullableGetValue)
    if parameter.usedIn == "header":
        # Special case for Metadata
        if parameterName == "Metadata":
            return gen_add_metadata_headers(parameterAsArgument)
        if parameter.isRequired:
            return "request.AddHeader(Details::{}, {});\n".format(parameter.parameterName, parameterAsArgument)
        else:
            firstIfLine = get_check_invalid_if_line("{}.{}".format(methodOptionsObjectName, parameterName))
            return inspect.cleandoc(
            """
            {}
            {{
                request.AddHeader(Details::{}, {});
            }}
            """.format(firstIfLine, parameter.parameterName, parameterAsArgument))
    elif parameter.usedIn == "query":
        # Add query parameters
        if parameter.isRequired:
            return "request.AddQueryParameter(Details::{}, {});\n".format(parameter.parameterName, parameterAsArgument)
        else:
            firstIfLine = get_check_invalid_if_line("{}.{}".format(methodOptionsObjectName, parameterName))
            return inspect.cleandoc(
            """
            {}
            {{
                request.AddQueryParameter(Details::{}, {});
            }}
            """.format(firstIfLine, parameter.parameterName, parameterAsArgument))
    elif parameter.usedIn == "body":
        # TODO: Add request body
        return
    else:
        raise RuntimeError("Parameter should have this used type: {} for: {}.".format(parameter.usedIn, parameterRefType))

def get_check_invalid_if_line(parameterName):
    return "if ({}.HasValue())".format(parameterName)

def gen_method_create_request_parameter_code(methodParameters, methodOptionsObjectName, models, parameters, serializationFormat):
    result = ""
    for params in methodParameters:
        if params.get("schema") != None:
            # TODO: Serialize object schema and set to body.
            continue
        elif params.get("type") != None:
            # explicit inline type.
            if params.get("x-ms-enum"):
                parameterRefType = params.get("x-ms-enum").get("name")
            else:
                parameterRefType = cpp_name_unify(params.get("name"))
            if params.get("enum"):
                if len(params.get("enum")) == 1:
                    # constant.
                    if params.get("in") ==  "query":
                        result += "request.AddQueryParameter(Details::c_Query{}, \"{}\");\n".format(cpp_name_unify(params.get("name")), params.get("enum")[0])
                    elif params.get("in") == "header":
                        result += "request.AddHeader(Details::c_Header{}, {});\n".format(cpp_name_unify(params.get("name")), params.get("enum")[0])
                    continue
        else:
            parameterRefType = get_reference_type_from_ref(params)
            if parameterRefType == "Body":
                # skip body
                continue

        parameter = parameters[parameterRefType]
        result += gen_adding_parameter_in_create_request_code(parameterRefType, parameter, methodOptionsObjectName, models)
    return result

def gen_method_create_request_code(method, parameters, models, serializationFormat):
    content = ""
    methodName = method.methodName + "CreateRequest"
    methodReturnType = "Azure::Core::Http::Request"
    methodOptionsClassName = method.methodName + "Options"
    methodOptionsObjectName = methodOptionsClassName[0].lower() + methodOptionsClassName[1:]
    # Declaration of the method.
    content += "static {} {}(std::string url, {}& {})\n{{\n".format(methodReturnType, methodName, methodOptionsClassName, methodOptionsObjectName)
    # Line 1 is always request initialization.
    if method.hasBody:
        content += "{} request(Azure::Core::Http::HttpMethod::{}, std::move(url), std::move({}.Body));\n".format(methodReturnType, method.method[0] + method.method[1:], methodOptionsObjectName)
    elif method.hasBodyToSerialize:
        if serializationFormat == "xml":
            bodyParam = method.bodyParameter
            bodyParamType = get_reference_type_from_ref(bodyParam.get("schema"))
            content += "{} request(Azure::Core::Http::HttpMethod::{}, url, XmlWrapper::SerializeNode({}::SerializeToXml({})));\n".format(methodReturnType, method.method[0] + method.method[1:], bodyParamType, cpp_name_unify(bodyParam.get("name")))
    else:
        content += "{} request(Azure::Core::Http::HttpMethod::{}, url);\n".format(methodReturnType, method.method[0] + method.method[1:])

    # Adding Query/Headers/Body for the operation.
    content += gen_method_create_request_parameter_code(method.pathParameters, methodOptionsObjectName, models, parameters, serializationFormat) if method.pathParameters else ""
    content += gen_method_create_request_parameter_code(method.parameters, methodOptionsObjectName, models, parameters, serializationFormat) if method.parameters else ""

    # Return request.
    content += "return request;\n}\n\n"
    return content

def gen_add_metadata_headers(metadataName):
    content = inspect.cleandoc(
        """
        for (const auto& pair : {0})
        {{
            request.AddHeader(Details::c_HeaderMetadata + pair.first, pair.second);
        }}
        """.format(metadataName))

    return content

def get_success_status_code_identifier(statusCodeStr):
    if statusCodeStr == "200":
        return "Ok"
    elif statusCodeStr == "201":
        return "Created"
    elif statusCodeStr == "202":
        return "Accepted"
    elif statusCodeStr == "204":
        return "NoContent"
    elif statusCodeStr == "206":
        return "PartialContent"
    else:
        return ""

def get_response_object_name(methodName, methodClassName, statusCodeStr):
    # return "{}{}Response".format(methodName, get_success_status_code_identifier(statusCodeStr))
    return "{}{}Response".format(methodClassName, methodName)

def get_member_object_name(key, value):
    return value.get("x-ms-client-name") if value.get("x-ms-client-name") else cpp_name_unify(key)

def gen_resposne_object_from_body_code(responseClassName, refType, model):
    result = "\nstatic {0} {0}From{1}({1} object)\n{{".format(responseClassName, refType)
    result += "{} result;\n".format(responseClassName)
    for k, v in model.properties.items():
        valueType = get_cpp_type_nullable_from_value(k, v)
        memberName = get_member_object_name(k, v)
        if valueType == "int32_t" or valueType == "int64_t" or valueType == "bool":
            # primitive type:
            result += "result.{0} = object.{0};\n".format(memberName)
        else:
            # complex type:
            result += "result.{0} = std::move(object.{0});\n".format(memberName)
    result += "\nreturn result;\n}\n"
    return result

def gen_response_object_code(method, parameters, models):
    content = ""
    # Header of the struct
    content += "struct {}\n{{\n".format(get_response_object_name(method.methodName, method.className, ""))
    bodyNotAdded = True
    headers = {}
    generate_from_body_code = ""
    for status, value in method.responses.items():
        if status == "default":
            continue
        # Headers of the response
        for k, v in value.get("headers").items():
            # merge the headers.
            headers[k] = v
        # Body schema
        if bodyNotAdded and value.get("schema"):
            schema = value.get("schema")
            if schema.get("type") and schema.get("format") == "file":
                content += "std::unique_ptr<Azure::Core::Http::BodyStream> BodyStream;\n"
                bodyNotAdded = False
            else:
                refType = get_reference_type_from_ref(schema)
                # content += "{0} {0}Object;\n".format(refType)
                # expand this to response item.
                model = models[refType]
                for k, v in model.properties.items():
                    headers[k] = v
                generate_from_body_code = gen_resposne_object_from_body_code(get_response_object_name(method.methodName, method.className, ""), refType, model)


    for k, v in headers.items():
        valueType = get_cpp_type_nullable_from_value(k, v)
        defaultValue = " = {}()".format(valueType) if valueType == "int32_t" or valueType == "int64_t" or valueType == "bool" else ""
        content += "{} {}{};\n".format(valueType, get_member_object_name(k, v), defaultValue)
    content += generate_from_body_code
    content += "};\n\n" if content != "" else ""

    return content

def gen_method_create_response_code(method, parameters, models, serializationFormat):
    content = ""
    methodName = method.methodName + "ParseResponse"
    # TODO: Support more colorful response.
    methodReturnType = get_response_object_name(method.methodName, method.className, "")
    methodReturnName = "result"
    methodResponseParameterName = "std::unique_ptr<Azure::Core::Http::Response>"
    methodResponsePtrName = "responsePtr"
    methodResponseObjectName = "response"
    # Declaration of the method.
    content += "static {} {}({} {})\n{{\n".format(methodReturnType, methodName, methodResponseParameterName, methodResponsePtrName)
    # response object.
    content += "/* const */auto& {} = *{};\n".format(methodResponseObjectName, methodResponsePtrName)
    # Branch on status code.
    firstBranch = True
    for status, value in method.responses.items():
        if status == "default":
            continue
        if firstBranch:
            firstBranch = False
        else:
            content += "else "
        statusEnumCode = "Azure::Core::Http::HttpStatusCode::{}".format(get_success_status_code_identifier(status))
        content += "if ({}.GetStatusCode() == {})\n{{\n".format(methodResponseObjectName, statusEnumCode)
        currentBranchComment = value.get("description")
        content += ("// {}\n").format(currentBranchComment) if currentBranchComment else ""
        # Parse body of the response if needed:
        if value.get("schema"):
            schema = value.get("schema")
            if schema.get("type") and schema.get("format") == "file":
                content += "{} {};\n".format(methodReturnType, methodReturnName)
                content += "{}.BodyStream = {}.GetBodyStream();\n".format(methodReturnName, methodResponseObjectName)
            else:
                refType = get_reference_type_from_ref(schema)
                if serializationFormat == "xml":
                    content += "{0}.{1}Object = {1}::CreateFromXml(XmlWrapper::CreateFromBodyBuffer(*Azure::Core::Http::Response::ConstructBodyBufferFromStream({2}.GetBodyStream().get())));\n".format(methodReturnName, refType, methodResponseObjectName)
                elif serializationFormat == "json":
                    # Declare the return value.
                    content += "{1} {0} = {1}::{1}From{2}({2}::CreateFromJson(nlohmann::json::parse(*Azure::Core::Http::Response::ConstructBodyBufferFromStream({3}.GetBodyStream().get()))));\n".format(methodReturnName, methodReturnType, refType, methodResponseObjectName)
        else:
            # empty body.
            # Declare the return value.
            content += "{} {};\n".format(methodReturnType, methodReturnName)
        # Parse headers of the response:
        for k, v in value.get("headers").items():
            parameter = next((parameter for name, parameter in parameters.items() if parameter.name == cpp_name_unify(k)), None)
            parameterName = parameter.parameterName if parameter else "\"{}\"".format(k)
            # Parse as different type:
            cppType = get_cpp_type_from_value(k, v)
            if cppType == "std::string":
                parseString = "{}.GetHeaders().at(Details::{})".format(methodResponseObjectName, parameterName)
            elif cppType == "int64_t":
                parseString = "std::stoll({}.GetHeaders().at(Details::{}))".format(methodResponseObjectName, parameterName)
            elif cppType == "int32_t":
                parseString = "std::stoi({}.GetHeaders().at(Details::{}))".format(methodResponseObjectName, parameterName)
            elif cppType == "bool":
                parseString = "{}.GetHeaders().at(Details::{}) == \"true\"".format(methodResponseObjectName, parameterName)
            else:
                raise RuntimeError("The type is not supported as a header type: " + cppType)
            if parameter.isRequired:
                content += "{}.{} = {};\n".format(methodReturnName, get_member_object_name(k, v), parseString)
            else:
                content += "if ({0}.GetHeaders().find(Details::{1}) != {0}.GetHeaders().end())\n{{\n".format(methodResponseObjectName, parameterName)
                content += "{}.{} = {};\n".format(methodReturnName, get_member_object_name(k, v), parseString)
                content += "}\n"

        content += "return {};\n".format(methodReturnName)
        content += "}\n"

    # Parse error:
    content += "else\n{\n"
    errorType = get_reference_type_from_ref(method.responses.get("default").get("schema"))
    # TODO: remove the temporary work around for error parsing.
    content += "throw Azure::Storage::StorageError::CreateFromResponse(std::move({}));\n".format(methodResponsePtrName)
    content += "}\n}\n\n"
    return content

def gen_method_run_code(method, parameters, models):
    content = ""
    methodName = method.methodName
    createRequestMethodName = method.methodName + "CreateRequest"
    parseResponseMethodName = method.methodName + "ParseResponse"
    methodReturnType = get_response_object_name(method.methodName, method.className, "")
    methodOptionsClassName = method.methodName + "Options"
    methodOptionsObjectName = methodOptionsClassName[0].lower() + methodOptionsClassName[1:]
    # Declaration of the method.
    content += "static {} {}(std::string url, Azure::Core::Http::HttpPipeline& pipeline, Azure::Core::Context context, {}& {})\n{{\n".format(methodReturnType, methodName, methodOptionsClassName, methodOptionsObjectName)
    content += "auto request = {}(std::move(url), {});\n".format(createRequestMethodName, methodOptionsObjectName)
    content += "return {}(pipeline.Send(context, request));\n}}\n\n".format(parseResponseMethodName)
    return content
