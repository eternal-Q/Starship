#include <sys/time.h>
#include "log.h"
#include "starship/common/util.h"
#include "starship/common/util.cc"

namespace starship{

std::string LogLevelToString(LogLevel level)
{
    switch (level)
    {
    case Debug:
        return "DEBUG";
    case Info:
        return "INFO";
    case Error:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}


std::string LogEvent::toString()
{
    struct timeval now_time;

    gettimeofday(&now_time, nullptr);

    struct tm now_time_t;
    localtime_r(&(now_time.tv_sec), &now_time_t); //����

    char buf[128];
    strftime(buf, 128, "%y-%m-%d %H:%M:%S", &now_time_t);
    std::string time_str(buf); //��ʼ��һ��string����

    //����
    int ms = now_time.tv_usec / 1000;
    time_str += "." + std::to_string(ms);

    m_pid = getPid();
    m_thread_id = getThreadId();

    std::stringstream ss;
    ss << "[" << LogLevelToString(m_level) << "]\t"
       << "[" << time_str << "]\t"
       << "[" << std::string(__FILE__) << ":" << __LINE__ << "]\t";

    return ss.str();  
}


}

//23��09��