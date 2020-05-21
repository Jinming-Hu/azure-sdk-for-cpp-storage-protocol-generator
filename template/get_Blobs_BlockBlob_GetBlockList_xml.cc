
// TODO: Think about how to initialize
// xmlInitParser();
// TODO: Think about how to free doc on exception

// TODO: Think about how to hanlde xml > 2GB
using namespace libXML2;
xmlDoc* doc = xmlReadMemory(reinterpret_cast<const char*>(http_response.GetBodyBuffer().data()), int(http_response.GetBodyBuffer().size()), nullptr, nullptr, 0);
if (doc == nullptr)
    throw std::runtime_error("failed to parse response xml");

xmlNode* root = xmlDocGetRootElement(doc);
if (root == nullptr || std::string(reinterpret_cast<const char*>(root->name)) != "BlockList")
    throw std::runtime_error("failed to parse response xml");

enum {
    start_tag,
    attribute,
    content,
    end_tag,
};

auto parse_xml_callback = [&response, blob_block = BlobBlock(), in_committed_block = false, in_uncommitted_block = false](const std::string& name, int type, const std::string& value) mutable {
    if (type == start_tag && name == "CommittedBlocks")
        in_committed_block = true;
    else if (type == end_tag && name == "CommittedBlocks")
        in_committed_block = false;
    else if (type == start_tag && name == "UncommittedBlocks")
        in_uncommitted_block = true;
    else if (type == end_tag && name == "UncommittedBlocks")
        in_uncommitted_block = false;
    else if (type == start_tag && name == "Block")
        blob_block = BlobBlock();
    else if (type == end_tag && name == "Block" && in_committed_block)
        response.CommittedBlocks.emplace_back(std::move(blob_block));
    else if (type == end_tag && name == "Block" && in_uncommitted_block)
        response.UncommittedBlocks.emplace_back(std::move(blob_block));
    else if (type == content && name == "Name")
        blob_block.Name = value;
    else if (type == content && name == "Size")
        blob_block.Size = std::stoull(value);
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
