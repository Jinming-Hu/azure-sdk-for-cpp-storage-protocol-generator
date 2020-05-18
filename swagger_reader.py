import json

    
def cpp_name_unify(str):
    result = ""
    # split on '-'
    l = str.split("-")
    result += ("".join(string[0].upper() + string[1:] for string in l))
    return result[0].upper() + result[1:]

class ModelObject:
    def __init__(self, name, properties, usedIn):
        self.usedIn = usedIn
        self.name = str(name)
        self.type = properties.get("type")
        self.description = properties.get("description")
        self.xml = properties.get("xml")
        self.isRequired = False if properties.get("required") == False else True
        if self.xml:
            self.xmlTag = self.xml.get("name")
        if self.type == "object":
            # special dictionary case
            if properties.get("additionalProperties") != None:
                # TODO: support more than string key/value dictionary.
                self.type = "dictionary"
            # parse object
            self.properties = properties.get("properties")
            self.subclasses = []
            if self.properties:
                for k,v in self.properties.items():
                    if v.get("type") == "object":
                        #Add sub-classes
                        self.subclasses.append(ModelObject(k[0].upper() + k[1:], v, usedIn))
        elif self.type == "string":
            # parse potential enum
            if properties.get("enum") != None:
                self.type = "enum"
                self.enum = {}
                # Fix casing
                for enum in properties.get("enum"):
                    # split on '-'
                    l = enum.split("-")
                    enumName = "".join(string[0].upper() + string[1:] for string in l)
                    self.enum[enumName] = enum
                if properties.get("x-ms-enum"):
                    self.modelAsString = properties.get("x-ms-enum").get("modelAsString")
                    self.enumName = properties.get("x-ms-enum").get("name")
                self.objectName = properties.get("name")
            else:
                raise RuntimeError("Type is string however model is not a enum, name: " + self.name)
        elif self.type == "array":
            self.items = properties.get("items").get("$ref")
        elif self.type == None:
            raise RuntimeError("The type is empty for model, name: " + self.name)
        else:
            raise RuntimeError("This type is not supported for model: " + self.type + " name: " + self.name)

class ParameterObject:
    def __init__(self, name, properties, models, usedIn = ""):
        self.name = str(name)
        self.description = properties.get("description")
        self.actualName = properties.get("name")
        if self.actualName == None:
            self.actualName = self.name
        self.clientName = properties.get("x-ms-client-name")
        if self.clientName == None:
            self.clientName = self.name
        self.usedIn = properties.get("in") if usedIn == "" else usedIn
        self.parameterName = "c_" + self.usedIn[0].upper() + self.usedIn[1:] + self.name
        self.isRequired = False if properties.get("required") == False else True
        self.type = properties.get("type")
        self.format = properties.get("format")
        if properties.get("schema"):
            # Parse parameter that's an object type
            self.type = "object"
        if self.type == "array":
            self.arrayItemType = properties.get("items").get("type")
        self.enum = properties.get("enum")
        self.referencedEnum = properties.get("x-ms-enum")
        if self.referencedEnum == None and properties.get("enum"):
            self.defaultValue = properties.get("enum")[0]
        if self.referencedEnum != None:
            if len(properties.get("enum")) == 1:
                self.defaultValue = properties.get("enum")[0]
            else:
                models[self.referencedEnum.get("name")] = ModelObject(self.referencedEnum.get("name"), properties, self.usedIn)
        self.parameterLocation = properties.get("x-ms-parameter-location")
        self.default = properties.get("default")

class MethodObject:
    def __init__(self, method, path, properties, pathParameters, models, parameters):
        method = method[0].upper() + method[1:]
        self.method = method
        self.path = str(path)
        self.description = properties.get("description")
        self.name = properties.get("operationId")
        splitted = self.name.split("_")
        self.className = splitted[0]
        self.methodName = splitted[1]
        # TODO: parse the methods actual name. E.g. Service_SetProperties should be SetProperties.
        # TODO: Create parent class from operation ID naming convention. e.g. Service_SetProperties should be in class Service.
        self.parameters = properties.get("parameters")
        self.hasBody = False
        self.hasBodyToSerialize = False
        if self.parameters:
            for parameter in self.parameters:
                if parameter.get("$ref") and ("#/parameters/Body" in parameter.get("$ref")):
                    self.hasBody = True
                elif parameter.get("in") == "body":
                    self.hasBodyToSerialize = True
                    self.bodyParameter = parameter
                if parameter.get("enum") and len(parameter.get("enum")) > 1:
                    name = parameter.get("x-ms-enum").get("name")
                    models[name] = ModelObject(name, parameter, parameter.get("in"))
                    parameters[name] = ParameterObject(name, parameter, models)
                elif parameter.get("in") == "header" or parameter.get("in") == "query":
                    value = next((value for key, value in parameters.items() if value.name == cpp_name_unify(parameter.get("name"))), None)
                    if value == None:
                        parameters[cpp_name_unify(parameter.get("name"))] = ParameterObject(cpp_name_unify(parameter.get("name")), parameter, models)
        self.responses = properties.get("responses")
        for k, v in self.responses.items():
            if v.get("headers"):
                for name, values in v.get("headers").items():
                    parameter = next((value for key, value in parameters.items() if value.name == cpp_name_unify(name)), None)
                    if parameter == None:
                        valueName = cpp_name_unify(name)
                        parameters[valueName] = ParameterObject(valueName, values, models, "header")
                        parameters[valueName].actualName = name
                        parameters[valueName].clientName = name
        self.pathParameters = pathParameters
        if self.pathParameters:
            for parameter in self.pathParameters:
                if parameter.get("$ref") and ("#/parameters/Body" in parameter.get("$ref")):
                    self.hasBody = True
                elif parameter.get("in") == "body":
                    self.hasBodyToSerialize = True
                    self.bodyParameter = parameter
                if parameter.get("enum"):
                    if parameter.get("x-ms-enum"):
                        name = parameter.get("x-ms-enum").get("name")
                        models[name] = ModelObject(name, parameter, parameter.get("in"))
                        parameters[name] = ParameterObject(name, parameter, models)
                    else:
                        name = parameter.get("name")
                        models[name] = ModelObject(name, parameter, parameter.get("in"))
                        parameters[cpp_name_unify(name)] = ParameterObject(cpp_name_unify(name), parameter, models)
                elif parameter.get("in") == "header" or parameter.get("in") == "query":
                    value = next((value for key, value in parameters.items() if value.name == cpp_name_unify(parameter.get("name"))), None)
                    if value == None:
                        parameters[cpp_name_unify(parameter.get("name"))] = ParameterObject(cpp_name_unify(parameter.get("name")), parameter, models)
    
def printJson(data):
    print("type of data is " + type(data).__name__)
    if isinstance(data, dict):
        for key, value in data.items():
            if isinstance(value, dict):
                print("key: " + key + "\n\n")
                printJson(value)
            elif isinstance(value, list):
                print("key: " + key + "\n\n")
                printJson(value)
            else:
                print("key: " + key, "value: ", value)
    elif isinstance(data, list):
        for i, value in enumerate(data):
            printJson("Element " + str(i) + " is: " + value)
            print("\n")
    elif isinstance(data, str):
        print("value: ", data)

def loadJson(path):
    with open(path, "r") as read_file:
        return json.load(read_file)

def constructModels(swagger_json, parameters):
    rawModels = swagger_json.get("definitions")
    # TODO: resolve model references
    models = {}
    for name, properties in rawModels.items():
        usedIn = parameters[name].usedIn if parameters.get(name) else ""
        models[name] = ModelObject(name, properties, usedIn)
    return models

def constructParameters(swagger_json, models):
    rawParameters = swagger_json.get("parameters")
    parameters = {}
    for name, properties in rawParameters.items():
        parameters[name] = ParameterObject(name, properties, models)
    # Patch for body parameter.
    parameters["Body"].name = "Body"
    parameters["Body"].type = "array"
    parameters["Body"].arrayItemType = "uint8_t"
    return parameters

def constructMethods(swagger_json, parameters, models):
    methods = {}
    rawMethodPaths = swagger_json.get("x-ms-paths")
    for k,v in rawMethodPaths.items():
        parentParams = v.get("parameters")
        for method, properties in v.items():
            if method == "parameters":
                continue
            method = MethodObject(method, k, properties, parentParams, models, parameters)
            methods[method.name] = method
    return methods
# test()