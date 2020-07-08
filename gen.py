#!/usr/bin/env python3

# TODO: DataLakeStorageError parsing.
# TODO: Metrics don't have type.
# TODO: Missing ListBlobsIncludeItem in swagger

import subprocess
import pathlib
import re

import code_template
import swagger_reader

from code_template import models_cache

service_name = "DataLake"

if service_name == "Blobs":
    swagger = swagger_reader.loadJson(".\\swagger\\blob.json")
    output_path = pathlib.Path("generated/blob_rest_client_test.hpp")
    serialization_format = "xml"
elif service_name == "DataLake":
    swagger = swagger_reader.loadJson(".\\swagger\\DatalakeStorage.json")
    output_path = pathlib.Path("generated/datalake_rest_client.hpp")
    serialization_format = "json"

modelsRaw = {}
parametersRaw = swagger_reader.constructParameters(swagger, modelsRaw)
modelsRaw.update(swagger_reader.constructModels(swagger, parametersRaw))
methodsRaw = swagger_reader.constructMethods(swagger, parametersRaw, modelsRaw)

code_template.gen_service_namespace(service_name)
code_template.gen_rest_client(service_name)
rest_client_subclasses = {}
method_models = ""
for name, method in methodsRaw.items():
    code_template.gen_method_code(rest_client_subclasses, method, parametersRaw, modelsRaw, serialization_format)
    model_definition = code_template.gen_response_object_code(method, parametersRaw, modelsRaw)
    if model_definition:
        method_models += model_definition

code_template.main_body += code_template.gen_subclasses(rest_client_subclasses)

for name, model in modelsRaw.items():
    model_definition = code_template.gen_model_code(model, modelsRaw, serialization_format)
    if model_definition:
        code_template.model_definitions += model_definition

code_template.model_definitions += method_models

code_template.c_API_VERSION = swagger.get("info").get("version")
code_template.parameter_string += code_template.details_namespace_begin
code_template.parameter_string += "{} {} = \"{}\";\n".format(code_template.c_PARAMETER_CPP_TYPE, code_template.c_API_VERSION_CONST_NAME, code_template.c_API_VERSION)
for name, parameter in parametersRaw.items():
    if parameter.usedIn != "header" and parameter.usedIn != "query":
        parameter_definition = code_template.gen_parameter_code(parameter)
        if parameter_definition:
            code_template.parameter_string += parameter_definition
for name, parameter in parametersRaw.items():
    if parameter.usedIn == "query":
        parameter_definition = code_template.gen_parameter_code(parameter)
        if parameter_definition:
            code_template.parameter_string += parameter_definition
for name, parameter in parametersRaw.items():
    if parameter.usedIn == "header":
        parameter_definition = code_template.gen_parameter_code(parameter)
        if parameter_definition:
            code_template.parameter_string += parameter_definition
code_template.parameter_string += code_template.details_namespace_end

output_path.parents[0].mkdir(parents=True, exist_ok=True)
with open(output_path, "w") as f:
    f.write(code_template.global_header + "\n")
    f.write(code_template.include_headers + "\n")
    f.write(code_template.namespace_begin + "\n")
    f.write(code_template.parameter_string + "\n")
    f.write(code_template.model_definitions + "\n")
    f.write(code_template.rest_client_begin + "\n")
    f.write(code_template.main_body + "\n")
    f.write(code_template.rest_client_end + "\n")
    f.write(code_template.namespace_end + "\n")
subprocess.call(["clang-format", "-style=file", "-i", output_path])
