#include "HttpConnPool.h"
#include <curl/curl.h>
#include <thread>
const int MIN_HTTP_CONN_CNT = 2;


////////////// HttpConn //////////
HttpConn::HttpConn (HttpConnPool *pPool)
{
    m_phttpconnpool = pPool;
    m_phttpclient = NULL;
}

HttpConn::~HttpConn()
{
    delete m_phttpclient;
    m_phttpclient = NULL;
}

int HttpConn::Init()
{
    m_phttpclient = new CHttpClient();
    if (m_phttpclient)
        return 0;
    return 0;
}

void HttpConn::ProcRun(Request &req )
{
    
    std::string resp;
    std::thread t(::_Worker);
    t.join();
}

/*
void HttpConn::DoExecution(Request &req, std::string &strResponse)
{
    std::string strUrl = req.strUrl;
    std::string method = req.method;
    std::string body = req.body;
    std::cout << "starting exec: " << strUrl << std::endl;
    long response_code =-1;
    if (method == "GET")
    {
        response_code = m_phttpclient->Get(strUrl, strResponse);
    }
    else if (method == "POST")
    {
        response_code = m_phttpclient->Post(strUrl, body, strResponse);
    }
    //TODO send msg to push_server
    std::cout << "DoExecution finished, response_code: " << response_code << std::endl;
    std::cout << "response is : " << strResponse << std::endl;
}
*/

///////////////HttpConnPool ///////////

HttpConnPool::HttpConnPool(int max_con_cnt)
{
    m_max_conn_cnt = max_con_cnt;
    m_cur_conn_cnt = MIN_HTTP_CONN_CNT;
}

HttpConnPool::~HttpConnPool()
{
    for(std::list<HttpConn*>::const_iterator it = m_free_list.begin(); it != m_free_list.end(); it++)
    {
        delete *it;
    }
    m_free_list.clear();
}

int HttpConnPool::Init()
{
    for (int i=0; i < m_max_conn_cnt; ++i)
    {
        HttpConn* pHttpConn = new HttpConn(this);
        int ret = pHttpConn->Init();
        if(ret) {
            delete pHttpConn;
            pHttpConn = NULL;
            return ret;
        }
        m_free_list.push_back(pHttpConn);
    }
    return 0;
}

HttpConn* HttpConnPool::GetHttpConn()
{
    m_free_notify.Lock();
    while (m_free_list.empty()) {
        if (m_cur_conn_cnt >= m_max_conn_cnt) {
            m_free_notify.Wait();
        } else {
            HttpConn* pHttpConn = new HttpConn(this);
            int ret = pHttpConn->Init();
            if (ret) {
                m_free_notify.Unlock();
                delete pHttpConn;
                return NULL;
            } else {
                m_free_list.push_back(pHttpConn);
                m_cur_conn_cnt++;
            }
        }
    }

    HttpConn* pHttpConn = m_free_list.front();
    m_free_list.pop_front();
    m_free_notify.Unlock();
    return pHttpConn;
}

void HttpConnPool::RelHttpConn(HttpConn *pHttpConn) 
{
    m_free_notify.Lock();
    std::list<HttpConn*>::iterator it = m_free_list.begin();
    for(it = m_free_list.begin(); it != m_free_list.end(); it++){
        if(*it == pHttpConn){
            break;
        }
    }

    if (it == m_free_list.end()) {
        m_free_list.push_back(pHttpConn);
    }

    m_free_notify.Signal();
    m_free_notify.Unlock();
}

