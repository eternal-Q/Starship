#include <tinyxml/tinyxml.h>
#include "config.h"


#define READ_XML_NODE(name, parent) \
TiXmlDocument* name##_node = parent->FirstChildElement(#name); \
if (!name##_node) \
{ \
    printf("Start rocket server error, failed to read node [%s]\n", #name); \
    exit(0); \
} \

#define READ_STR_FROM_XML_NODE(name, parent) \
TiXmlDocument* name##_node = parent->FirstChildElement(#name); \
if (!name##_node || !name##_node->GetText()) \
{ \
    printf("Start rocket server error, failed to read config file %s\n", #name); \
    exit(0); \
} \
//  问题：log_level_node->GetText() 返回的是啥？
std::string name## = std::string(name##->GetText()); \

namespace starship{

static Config* g_config = nullptr;

Config::Config(const char* xmlfile)
{
    TiXmlDocument* xml_document = new TiXmlDocument();

    bool rt = xml_document->LoadFile(xmlfile);
    if (!rt)
    {
        printf("Start rocket server error, failed to read config file %s\n", xmlfile);
        exit(0);
    }
    //下面两段代码重复，可以封装成一个宏
    // TiXmlDocument* root_node = xml_document->FirstChildElement("root");
    // if (!root_node)
    // {
    //     printf("Start rocket server error, failed to read node [%s]\n", "root");
    //     exit(0);
    // }

    // TiXmlDocument* log_node = root_node->FirstChildElement("log");
    // if (!log_node)
    // {
    //     printf("Start rocket server error, failed to read node [%s]\n", "log");
    //     exit(0);
    // }

    READ_XML_NODE(root, xml_document);

    READ_XML_NODE(log, root_node);
    //字符串记录在log_level中
    READ_STR_FROM_XML_NODE(log_level, log_node);
    //将log_level读出来
    m_log_level = log_level;

}

Config::Config* GetGlobalConfig()
{
    return g_config;
}

void Config::SetGlobalConfig(const char* xmlfile)
{
    if (g_config == nullptr)
    {
        g_config =  new Config(xmlfile);
    }
}

}
