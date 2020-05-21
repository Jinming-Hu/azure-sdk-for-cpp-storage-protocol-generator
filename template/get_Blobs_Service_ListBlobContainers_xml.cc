
// TODO: Think about how to initialize
// xmlInitParser();
// TODO: Think about how to free doc on exception

// TODO: Think about how to hanlde xml > 2GB
using namespace libXML2;
xmlDoc* doc = xmlReadMemory(reinterpret_cast<const char*>(http_response.GetBodyBuffer().data()), int(http_response.GetBodyBuffer().size()), nullptr, nullptr, 0);
if (doc == nullptr)
    throw std::runtime_error("failed to parse response xml");

xmlNode* root = xmlDocGetRootElement(doc);
if (root == nullptr || std::string(reinterpret_cast<const char*>(root->name)) != "EnumerationResults")
    throw std::runtime_error("failed to parse response xml");

enum {
    start_tag,
    attribute,
    content,
    end_tag,
};

auto parse_xml_callback = [&response, blob_container_item = BlobContainerItem(), in_metadata = false](const std::string& name, int type, const std::string& value) mutable {
    if (type == start_tag && name == "Metadata")
        in_metadata = true;
    else if (type == end_tag && name == "Metadata")
        in_metadata = false;
    else if (type == content && in_metadata)
        blob_container_item.Metadata.emplace(name, value);
    else if (type == attribute && name == "ServiceEndpoint")
        response.ServiceEndpoint = value;
    else if (type == content && name == "Prefix")
        response.Prefix = value;
    else if (type == content && name == "Marker")
        response.Marker = value;
    else if (type == content && name == "MaxResults")
        response.MaxResults = std::stoi(value);
    else if (type == content && name == "NextMarker")
        response.NextMarker = value;
    else if (type == start_tag && name == "Container")
        blob_container_item = BlobContainerItem();
    else if (type == end_tag && name == "Container")
        response.BlobContainerItems.emplace_back(std::move(blob_container_item));
    else if (type == content && name == "Name")
        blob_container_item.Name = value;
    else if (type == content && name == "Last-Modified")
        blob_container_item.LastModified = value;
    else if (type == content && name == "Etag")
        blob_container_item.ETag = value;
    else if (type == content && name == "LeaseStatus")
        blob_container_item.LeaseStatus = BlobLeaseStatusFromString(value);
    else if (type == content && name == "LeaseState")
        blob_container_item.LeaseState = BlobLeaseStateFromString(value);
    else if (type == content && name == "LeaseDuration")
        blob_container_item.LeaseDuration = value;
    else if (type == content && name == "PublicAccess")
        blob_container_item.AccessType = PublicAccessTypeFromString(value);
    else if (type == content && name == "HasImmutabilityPolicy")
        blob_container_item.HasImmutabilityPolicy = value == "true";
    else if (type == content && name == "HasLegalHold")
        blob_container_item.HasLegalHold = value == "true";
};

std::function<void(xmlNode*)> parse_xml;
parse_xml = [&parse_xml, &parse_xml_callback](xmlNode* node) {
    if (!(node->type == XML_ELEMENT_NODE || node->type == XML_ATTRIBUTE_NODE)) return;

    std::string node_name(reinterpret_cast<const char*>(node->name));
    parse_xml_callback(node_name, start_tag, "");

    for (xmlAttr* prop = node->properties; prop; prop = prop->next) {
        std::string prop_name(reinterpret_cast<const char*>(prop->name));
        std::string prop_value(reinterpret_cast<const char*>(prop->children->content));
        parse_xml_callback(prop_name, attribute, prop_value);
    }

    bool has_child_element = false;
    for (xmlNode* child = node->children; child; child = child->next) {
        has_child_element |= child->type == XML_ELEMENT_NODE;
        parse_xml(child);
    }

    if (!has_child_element && node->children) {
        std::string node_content(reinterpret_cast<const char*>(node->children->content));
        parse_xml_callback(node_name, content, node_content);
    }

    parse_xml_callback(node_name, end_tag, "");
};

parse_xml(root);

xmlFreeDoc(doc);

// TODO: Think about how to cleanup
// xmlCleanupParser();
