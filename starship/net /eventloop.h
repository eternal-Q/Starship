#ifndef STARSHIP_NET_EVENTLOOP_H
#define STARSHIP_NET_EVENTLOOP_H

#include <pthread.h>
#include <set>
#include <functional>
#include <queue>
#include "rocket/common/mutex.h"

namespace starship{

class Eventloop
{
 public:
    Eventloop();

    ~Eventloop();

    void loop();

    void wakeup();

    void stop();
 private:
    void dealWakeup();
 private:
    pid_t m_pid {0};
    //这啥意思？初始化为0？
    int m_epoll_fd {0};
    int m_wakeup_fd {0};
    bool m_stop_flag {false};
    std::set<int> m_listen_fds;
    std::queue<std::functional<void()>> m_pending_tasks;
    Mutex m_mutex;
};


}


#endif