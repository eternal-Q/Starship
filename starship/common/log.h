#ifndef STRASHIP_COMMON_H_
#define STRASHIP_COMMON_H_

#include <string>
#include <sstream>

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

enum LogLevel
{
    Debug = 1,
    Info = 2,
    Error = 3
};

std::string LogLevelToString(LogLevel level);

class LogEvent
{
 public:

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

class Logger
{
 public:
    void log(LogEvent event);
 
 private:
    LogLevel m_set_level;

};



}


#endif