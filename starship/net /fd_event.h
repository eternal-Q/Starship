#ifndef STARSHIP_NET_FDEVENT_H
#define STARSHIP_NET_FDEVENT_H

#include <functional>

namespace starship{

class FdEvent
{
 public:

 private:
    int m_fd {-1};
    std::function<void()> m_read_callback;
    std::function<void()> m_write_callback;

};


}

#endif