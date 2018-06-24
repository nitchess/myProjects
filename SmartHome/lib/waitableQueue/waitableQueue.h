/** 
* @author           : Or Erlich (erlich11@gmail.com / +972 523893693)
* @creationDate     : 27. 05. 18
* @dateLastModified : 27. 05. 18
* @brief            : Waitable queue class 
*/ 
#ifndef __WAITABLE_QUEUE_H__
#define __WAITABLE_QUEUE_H__

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <cassert>
#include <iostream>
#include <queue>

template <class T>
class WaitableQueue 
{
private:
    
    std::queue<T>          m_queue;
    pthread_mutex_t     push_pop_mutex;
    pthread_cond_t      is_empty_cond;

    // Non-Copyable
    WaitableQueue(const WaitableQueue & _wq);
    WaitableQueue & operator=(const WaitableQueue & _wq);

public:

    // CTOR
    WaitableQueue();
    // DTOR
    ~WaitableQueue();

    // Add element to queue end
    void Push(const T & _data);
    // Remove element from queue front
    T Pop();

};

template <class T>
WaitableQueue<T>::WaitableQueue()
{
    pthread_mutex_init(&push_pop_mutex, NULL);
    pthread_cond_init(&is_empty_cond, NULL);
}

template <class T>
WaitableQueue<T>::~WaitableQueue()
{
    assert (pthread_mutex_destroy(&push_pop_mutex) == 0);
    assert (pthread_cond_destroy(&is_empty_cond) == 0);
}

template <class T>
void WaitableQueue<T>::Push(const T & _data)
{
    pthread_mutex_lock(&push_pop_mutex);

    m_queue.push(_data);

    pthread_cond_signal(&is_empty_cond);
    pthread_mutex_unlock(&push_pop_mutex);
}

template <class T>
T WaitableQueue<T>::Pop( )
{
    pthread_mutex_lock(&push_pop_mutex);

    while (m_queue.empty() == true)
    {
        pthread_cond_wait(&is_empty_cond, &push_pop_mutex);
    }

    T popped_data = m_queue.front();
    m_queue.pop();

    pthread_mutex_unlock(&push_pop_mutex);

    return popped_data;
}

#endif /*__WAITABLE_QUEUE_H__*/
