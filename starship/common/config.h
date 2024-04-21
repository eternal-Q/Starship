#ifndef STRASHIP_COMMON_CONFIG_H_
#define STRASHIP_COMMON_CONFIG_H_

#include <map>

namespace starship{

class Config
{
 public:
    Config(const char* xmlfile);

    static Config* GetGlobalConfig();
    static void SetGlobalConfig(const char* xmlfile);

    std::string m_log_level;

};


}


#endif