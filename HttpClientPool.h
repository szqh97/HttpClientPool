#ifndef HttpClientPool_h_
#define HttpClientPool_h_ 1
#include "ThreadPool.h"
#include "Task.h"

static int g_thread_num = 8;
class HttpClientPool
{
public:
    ~HttpClientPool();
    int Init(int thread_num);
    void AddTask(CTask *task);
    static HttpClientPool* GetHttpClientPool();
    static void Destory();


private:
    HttpClientPool ();
    static HttpClientPool* pHttpClintPool;
    CThreadPool *m_thread_pool; 
    int m_thread_num;
};
#endif
