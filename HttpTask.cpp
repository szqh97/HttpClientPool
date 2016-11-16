#include "HttpTask.h"

HttpTask::HttpTask(Request* req, Response* resp, handler_t h)
{
    m_http_req = req;
    m_http_resp = resp;
    m_handler =  h;
}

HttpTask::~HttpTask()
{
    delete m_http_req;
    delete m_http_resp;
}

void HttpTask::run()
{
    if (!m_http_req and !m_http_resp) {
        return ;
    }
    m_handler(m_http_req, m_http_resp);
}
