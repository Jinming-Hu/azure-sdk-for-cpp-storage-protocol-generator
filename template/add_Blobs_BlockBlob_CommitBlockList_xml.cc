
// TODO: Think about how to initialize
// xmlInitParser();
// TODO: Think about how to free doc on exception
using namespace libXML2;
xmlDocPtr doc = xmlNewDoc(BAD_CAST("1.0"));
xmlNodePtr block_list_node = xmlNewNode(nullptr, BAD_CAST("BlockList"));
xmlDocSetRootElement(doc, block_list_node);

for (const auto& block : options.BlockList)
{
    const char* tag_name = nullptr;
    if (block.first == BlockType::Uncommitted)
        tag_name = "Uncommitted";
    else if (block.first == BlockType::Committed)
        tag_name = "Committed";
    else if (block.first == BlockType::Latest)
        tag_name = "Latest";
    else
        throw std::runtime_error("unexpected block type");

    xmlNewChild(block_list_node, nullptr, BAD_CAST(tag_name), BAD_CAST(block.second.data()));
}

xmlChar* xml_dump;
int xml_dump_size;
xmlDocDumpMemory(doc, &xml_dump, &xml_dump_size);
xmlFreeDoc(doc);
if (xml_dump == nullptr)
{
    throw std::runtime_error("failed to allocate memory when building xml body");
}

// TODO: Think about how to free memory
// xmlFree(xml_dump);

// TODO: Think about how to cleanup
// xmlCleanupParser();

// TODO: Think about how to avoid copy
std::vector<uint8_t> body_buffer(static_cast<const uint8_t*>(xml_dump), static_cast<const uint8_t*>(xml_dump) + xml_dump_size);
request.setBodyBuffer(body_buffer);
// TODO: Set Content-MD5 or x-ms-content-crc64 header
request.AddHeader("Content-Length", std::to_string(body_buffer.size()));
