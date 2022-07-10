#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "locker.h"

template< typename T >              // T是任务类
class threadpool
{
public:
    threadpool( int thread_number = 8, int max_requests = 10000 );
    ~threadpool();
    bool append( T* request );      // 往工作队列中添加任务

private:
    static void* worker( void* arg );   // 工作线程运行的函数
                                        // 它不断从工作队列中取出任务并执行之
    void run();

private:
    int m_thread_number;            // 线程池中线程的数量
    int m_max_requests;             // 工作队列中最多允许的请求数量
    pthread_t* m_threads;           // 线程
    std::list< T* > m_workqueue;    // 工作队列,链表实现
    locker m_queuelocker;           // 对工作队列加的互斥锁
    sem m_queuestat;                // 是否有任务需要处理
    bool m_stop;                    // 是否结束线程
};

template< typename T >
threadpool< T >::threadpool( int thread_number, int max_requests ) : 
        m_thread_number( thread_number ), m_max_requests( max_requests ), m_stop( false ), m_threads( NULL )
{
    if( ( thread_number <= 0 ) || ( max_requests <= 0 ) )
    {
        throw std::exception();
    }

    m_threads = new pthread_t[ m_thread_number ];
    if( ! m_threads )
    {
        throw std::exception();
    }

    for ( int i = 0; i < thread_number; ++i )   // 创建所有线程,并且detach他们
    {
        printf( "create the %dth thread\n", i );
        if( pthread_create( m_threads + i, NULL, worker, this ) != 0 )
        {
            delete [] m_threads;
            throw std::exception();
        }
        if( pthread_detach( m_threads[i] ) )
        {
            delete [] m_threads;
            throw std::exception();
        }
    }
}

template< typename T >
threadpool< T >::~threadpool()
{
    delete [] m_threads;
    m_stop = true;
}

template< typename T >
bool threadpool< T >::append( T* request )      // 添加新请求到工作队列
{
    m_queuelocker.lock();                       // 工作队列需要加锁操作
    if ( m_workqueue.size() > m_max_requests )
    {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back( request );
    m_queuelocker.unlock();
    m_queuestat.post();
    return true;
}

template< typename T >
void* threadpool< T >::worker( void* arg )      // 创建线程时,这个参数被传递为线程池实例
{
    threadpool* pool = ( threadpool* )arg;
    pool->run();
    return pool;
}

template< typename T >
void threadpool< T >::run()                     // 一个线程将要运行的代码
{
    while ( ! m_stop )
    {
        m_queuestat.wait();                     // 等待锁
        m_queuelocker.lock();                   // 得到锁
        if ( m_workqueue.empty() )
        {
            m_queuelocker.unlock();
            continue;
        }
        T* request = m_workqueue.front();       // 从工作队列中获取任务
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        if ( ! request )
        {
            continue;
        }
        request->process();                     // 处理这个任务
    }
}

#endif
