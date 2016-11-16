#ifndef _HTTPTASK_H_
#define _HTTPTASK_H_ 1
#include <iostream>
#include <string>
#include "Task.h"
#include "HttpClient.h"

typedef void (*handler_t)(HttpRequest& req, HttpResponse& resp);


class HttpTask: public CTask
{
public:
    HttpTask (HttpRequest& req, HttpResponse& resp, handler_t h);
    virtual ~HttpTask ();
    virtual void run();

private:
    HttpRequest m_http_req;
    HttpResponse m_http_resp;
    handler_t m_handler;
};

#endif
