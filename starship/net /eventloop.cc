#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/eventfd.h>
#include "starship/common/eventloop.h"
#include "starship/common/log.h"
#include "starship/common/util.h"

namespace starship{

static thread_local EventLoop* t_current_eventloop = nullptr;
static int g_epoll_max_timeout = 10000;
static int g_epoll_max_events = 10;

Eventloop::Eventloop()
{
    if (t_current_eventloop != nullptr)
    {
        ERRORLOG("failed to create eventloop, this thread has created event loop");
        exit(0);
    }

    m_pid = getThreadId();

    m_epoll_fd = epoll_create(10);
    if (m_epoll_fd == -1)
    {
        ERRORLOG("failed to create eventloop, epoll_create error, error info[%d]", errno);
        exit(0);
    }

    m_wakeup_fd = eventfd(0, EFD_NONBLOCK);
    if (m_wakeup_fd < 0)
    {
        ERRORLOG("failed to create eventloop, eventfd create error, error info[%d]", errno);
        exit(0);
    }

    epoll_event event;
    event.events = EPOLLIN;
    int rt = epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, m_wakeup_fd, &event);
    if (rt == -1)
    {
        ERRORLOG("failed to create eventloop, epoll_ctl create error, error info[%d]", errno);
        exit(0);
    }

    INFOLOG("succ cteate loop in thread %d", m_pid);

    t_current_eventloop = this;
    

}

Eventloop::~Eventloop() {}

void Eventloop::loop()
{
    while (!m_stop_flag)
    {
        ScopeMutext<Mutex> lock(m_mutex);
        std::queue<std::functional<void()>> tmp_tasks = m_pending_tasks;
        m_pending_tasks.swap(tmp_tasks);
        lock.unlock();

        while (!tmp_tasks.empty())
        {
            tmp_tasks.front();
            tmp_tasks.pop();
        }

        int timeout = g_epoll_max_timeout;
        epoll_event result_events[g_epoll_max_events];
        int rt = epoll_wait(m_epoll_fd, result_events, g_epoll_max_events, timeout);

        if (rt < 0)
        {
            ERRORLOG("epoll_wait error,error=%d", errno);
        }else
        {
            for (int i = 0; i < rt; i++)
            {
                epoll_event trigger_event = result_events[i];
                if (trigger_event.events | EPOLLIN)
                {
                    
                }
            }

        }


    }


}

void Eventloop::wakeup()
{

}

void Eventloop::stop()
{
    m_stop_flag = true;
}

void Eventloop::dealWakeup()
{

}



}