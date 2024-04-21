#ifndef STARSHIP_COMMON_MUTEX_H
#define STARSHIP_COMMON_MUTEX_H

#include <pthread.h>

namespace starship{

template <class T>
class ScopeMutext
{
 public:
    ScopeMutext(T& mutex) : m_mutex(mutex)
    {
        m_mutex.lock();
        m_is_lock = true;
    }

    ~ScopeMutext()
    {
        m_mutex.unlock();
        m_is_lock = false;
    }

    void lock()
    {
        if (!m_is_lock)
        {
            m_mutex.lock();
        }
    }
    
    void unlock()
    {
        if (m_is_lock)
        {
            m_mutex.unlock();
        }
    }


 private:
    T& m_mutex;
    //这个是啥意思？
    bool m_is_lock {false};

};


//互斥锁
class Mutex
{
 public:
    Mutex()
    {
        pthread_mutex_init(&m_mutex, NULL);
    }

    ~Mutex()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    void lock()
    {
        pthread_mutex_lock(&m_mutex);
    }

    void unlock()
    {
        pthread_mutex_unlock(&m_mutex);
    }

 private:
    pthread_mutex_t m_mutex;

};


}

#endif