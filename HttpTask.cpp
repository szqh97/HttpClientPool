#include "HttpTask.h"
#include "HttpClient.h"


HttpTask::HttpTask(HttpRequest& req, HttpResponse& resp, handler_t h)
{
    m_http_req = req;
    m_http_resp = resp;
    m_handler =  h;
}

HttpTask::~HttpTask()
{
}

void HttpTask::run()
{
    m_handler(m_http_req, m_http_resp);
}
