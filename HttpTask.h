#ifndef _HTTPTASK_H_
#define _HTTPTASK_H_ 1
#include <iostream>
#include <string>
#include "Task.h"
struct Request {
    std::string method;
    std::string strUrl;
    std::string body ;
};

struct Response {
    long statusCode;
    std::string& context;
};

typedef void (*handler_t)(Request* req, Response* resp);


class HttpTask: public CTask
{
public:
    HttpTask (Request*, Response*, handler_t );
    virtual ~HttpTask ();
    virtual void run();

private:
    Request *m_http_req;
    Response *m_http_resp;
    handler_t m_handler;
};



#endif
