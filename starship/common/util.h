#ifndef STRASHIP_COMMON_H_
#define STRASHIP_COMMON_H_

#include <sys/types.h>
#include <unistd.h>

namespace starship
{
    pid_t getPid();

    pid_t getThreadId();
}


#endif