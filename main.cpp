#include <iostream>
#include <string>
#include "HttpClientPool.h"
#include "HttpTask.h"
#include "HttpClient.h"
using namespace std;

void httpAsyncRequest(Request *req, Response *resp)
{
    std::cout << "POST URL IS " << req->strUrl << std::endl;
    CHttpClient *pcli = new CHttpClient();
    resp->statusCode = pcli->Post(req->strUrl, req->body, resp->context);
    std::cout << "ret: " << resp->statusCode << " context: " << resp->context << endl;

}

int main()
{
    string post_data = "u=18814842159&p=111111&sign=42557FBC90E10CAD27FAC0F9D8BA94E9";
    string strUrl = "http://app-test.kaipao.cc/v1/user/loginx";

    Request req ;
    req.method = "POST";
    req.strUrl = strUrl;
    req.body = post_data;

    Response resp{};
    
 
    HttpClientPool *pool =  new HttpClientPool();
    pool->Init(8);
   
    for (int i = 0; i < 22; i++) {
        CTask *task = new HttpTask(&req, &resp,  httpAsyncRequest);
        pool->AddTask(task);
    }

    return 0;
}
