#ifndef STRASHIP_COMMON_H_
#define STRASHIP_COMMON_H_

#include <string>
#include <sstream>
#include <memory>
#include <queue>
#include "config.h"
#include "mutex.h"

namespace starship
{

//C���Ը�ʽ���ַ����ĺ���
template<typename... Args>
std::string formatString(const char* str, Args&&... args)
{
    int size = snprintf(nullptr, 0, str, args...);
    std::string result;
    if (size > 0)
    {
        result.resize(size);
        snprintf(&result[0], size + 1, str, args...);
    }
}

//new starship::LogEvent(starship::LogLevel::Debug) 返回一个LogEvent类型的指针
#define DEBUGLOG(str, ...)\
    if (starship::Logger::GetGlobalLogger()->getLogLevel() >= starship::LogLevel::Debug) \
    { \
    std::string msg = (new starship::LogEvent(starship::LogLevel::Debug)->toString()) + starship::formatString(str, ##__VA_ARGS__); \
    msg += "\n"; \
    starship::Logger::GetGlobalLogger->pushLog(msg); \
    starship::Logger::GetGlobalLogger->log(); \
    } \
    
#define INFOLOG(str, ...)\
    if (starship::Logger::GetGlobalLogger()->getLogLevel() >= starship::LogLevel::Info) \
    { \
    std::string msg = (new starship::LogEvent(starship::LogLevel::Info)->toString()) + starship::formatString(str, ##__VA_ARGS__); \
    msg += "\n"; \
    starship::Logger::GetGlobalLogger->pushLog(msg); \
    starship::Logger::GetGlobalLogger->log(); \
    } \
    
#define ERRORLOG(str, ...)\
    if (starship::Logger::GetGlobalLogger()->getLogLevel() >= starship::LogLevel::Error) \
    { \
    std::string msg = (new starship::LogEvent(starship::LogLevel::Error)->toString()) + starship::formatString(str, ##__VA_ARGS__); \
    msg += "\n"; \
    starship::Logger::GetGlobalLogger->pushLog(msg); \
    starship::Logger::GetGlobalLogger->log(); \
    } \

enum LogLevel
{
    Unknown = 0,
    Debug = 1,
    Info = 2,
    Error = 3
};

class Logger
{
 public:
    typedef std::shared_ptr<Logger> s_ptr;

    Logger(LogLevel level) : m_set_level(level) {}

    void pushLog(const std::string& message);

    static Logger* GetGlobalLogger();

    static void InitGlobalConfig();

    void log();

    LogLevel getLogLevel() const
    {
        return m_set_level;
    }
 
 private:
    LogLevel m_set_level;
    std::queue<std::string> m_buffer;

    Mutex m_mutex;

};

std::string LogLevelToString(LogLevel level);

LogLevel StringToLogLevel(const std::string& log_level);

class LogEvent
{
 public:
    //构造函数
    LogEvent(LogLevel level) : m_level(level) {}

    std::string getFileName() const
    {
        return m_file_name;
    }

    LogLevel getLogLevel() const
    {
        return m_level;
    }

    // void printLog();
    std::string toString();

 private:
    std::string m_file_name; //�ļ���
    int32_t m_file_line; //�к�
    int32_t m_pid; //���̺�
    int32_t m_thread_id; //�̺߳�

    LogLevel m_level; //��־����
    

};



}


#endif