
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

auto parse_xml_callback = [&response, blob_item = BlobItem(), in_metadata = false](const std::string& name, int type, const std::string& value) mutable {
    if (type == start_tag && name == "Metadata")
        in_metadata = true;
    else if (type == end_tag && name == "Metadata")
        in_metadata = false;
    else if (type == content && in_metadata)
        blob_item.Metadata.emplace(name, value);
    else if (type == attribute && name == "ServiceEndpoint")
        response.ServiceEndpoint = value;
    else if (type == attribute && name == "ContainerName")
        response.Container = value;
    else if (type == content && name == "Prefix")
        response.Prefix = value;
    else if (type == content && name == "Marker")
        response.Marker = value;
    else if (type == content && name == "MaxResults")
        response.MaxResults = std::stoi(value);
    else if (type == content && name == "Delimiter")
        response.Delimiter = value;
    else if (type == content && name == "NextMarker")
        response.NextMarker = value;
    else if (type == start_tag && name == "Blob")
        blob_item = BlobItem();
    else if (type == end_tag && name == "Blob")
        response.BlobItems.emplace_back(std::move(blob_item));
    else if (type == content && name == "Name")
        blob_item.Name = value;
    else if (type == content && name == "Deleted")
        blob_item.Deleted = value == "true";
    else if (type == content && name == "Snapshot")
        blob_item.Snapshot = value;
    else if (type == content && name == "Creation-Time")
        blob_item.CreationTime = value;
    else if (type == content && name == "Last-Modified")
        blob_item.LastModified = value;
    else if (type == content && name == "Etag")
        blob_item.ETag = value;
    else if (type == content && name == "Content-Length")
        blob_item.ContentLength = std::stoull(value);
    else if (type == content && name == "BlobType")
        blob_item.BlobType = BlobTypeFromString(value);
    else if (type == content && name == "AccessTier")
        blob_item.Tier = AccessTierFromString(value);
    else if (type == content && name == "AccessTierInferred")
        blob_item.AccessTierInferred = value == "true";
    else if (type == content && name == "LeaseStatus")
        blob_item.LeaseStatus = BlobLeaseStatusFromString(value);
    else if (type == content && name == "LeaseState")
        blob_item.LeaseState = BlobLeaseStateFromString(value);
    else if (type == content && name == "LeaseDuration")
        blob_item.LeaseDuration = value;
    else if (type == content && name == "ServerEncrypted")
        blob_item.ServerEncrypted = value == "true";
    else if (type == content && name == "CustomerProvidedKeySha256")
        blob_item.EncryptionKeySHA256 = value;
    else if (type == content && name == "Content-Type")
        blob_item.Properties.ContentType = value;
    else if (type == content && name == "Content-Encoding")
        blob_item.Properties.ContentEncoding = value;
    else if (type == content && name == "Content-Language")
        blob_item.Properties.ContentLanguage = value;
    else if (type == content && name == "Content-MD5")
        blob_item.Properties.ContentMD5 = value;
    else if (type == content && name == "Cache-Control")
        blob_item.Properties.CacheControl = value;
    else if (type == content && name == "Content-Disposition")
        blob_item.Properties.ContentDisposition = value;
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
