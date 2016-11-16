#ifndef HttpClientPool_h_
#define HttpClientPool_h_ 1
#include "ThreadPool.h"
#include "Task.h"

class HttpClientPool
{
public:
    HttpClientPool ();
    int Init(int thread_num);
    void AddTask(CTask *task);

    virtual ~HttpClientPool ();

private:
    CThreadPool *m_thread_pool; 
    int m_thread_num;
};
#endif
