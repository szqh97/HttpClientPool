#ifndef HttpConnPool_h_
#define HttpConnPool_h_ 1
#include "HttpClient.h"
#include "Thread.h"
#include <list>
#include <iostream>


class HttpConnPool;

struct Request {
    std::string method;
    std::string strUrl;
    std::string body;
};

//static void Worker(Request& req, std::string &response)
static void _Worker()
{
    Request req;
    req.strUrl = "http://google.com/";
    req.body ="u=18814842159&p=111111&sign=42557FBC90E10CAD27FAC0F9D8BA94E9"; 
    std::cout << "In Worker ..." << std::endl;
    CHttpClient *pcli = new CHttpClient();
    std::string response;
    long resp = pcli->Post(req.strUrl, req.body, response);
    std::cout << resp << std::endl;
    delete pcli;
}

class HttpConn
{
public:
    HttpConn (HttpConnPool *pPool);
    virtual ~HttpConn ();
    int Init();
    void ProcRun(Request &req);
    //void DoExecution(HttpRequest &req, std::string &strResponse);

private:
    CHttpClient *m_phttpclient;
    HttpConnPool *m_phttpconnpool;
    std::string m_method;

    /* data */
};

class HttpConnPool
{
public:
    HttpConnPool (int max_con_cnt = 16);
    virtual ~HttpConnPool ();
    int Init();
    HttpConn* GetHttpConn();
    void RelHttpConn(HttpConn *pHttpConn);

private:
    int m_max_conn_cnt;
    int m_cur_conn_cnt;
    std::list<HttpConn*> m_free_list;
    CThreadNotify m_free_notify;
    /* data */
};
#endif /* ifndef HttpConnPool_h_ */
