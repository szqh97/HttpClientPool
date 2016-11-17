#include "HttpClientPool.h"

HttpClientPool* HttpClientPool::pHttpClintPool = NULL;

HttpClientPool::HttpClientPool()
{
    m_thread_num = 0;
    m_thread_pool = NULL;
}

int HttpClientPool::Init(int thread_num) 
{
    m_thread_num = thread_num;
    m_thread_pool = new CThreadPool();
    if (m_thread_pool) {
        m_thread_pool->Init(m_thread_num);
    } else {
        return 1;
    }
    return 0;
}

HttpClientPool::~HttpClientPool()
{
    if (m_thread_pool) {
        m_thread_pool->Destory();
        delete m_thread_pool;
        m_thread_pool = NULL;
    }
}

void HttpClientPool::AddTask(CTask *task)
{
    m_thread_pool->AddTask(task);
}

HttpClientPool* HttpClientPool::GetHttpClientPool()
{
    if (pHttpClintPool == NULL) {
        pHttpClintPool = new HttpClientPool();
        pHttpClintPool->Init(g_thread_num);
    }
    return pHttpClintPool;
}

void HttpClientPool::Destory()
{
    if (pHttpClintPool)
    {
        delete pHttpClintPool;
        pHttpClintPool =  NULL;
    }
}
