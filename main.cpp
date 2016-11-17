#include <iostream>
#include <string>
#include "HttpClientPool.h"
#include "HttpTask.h"
#include "HttpClient.h"
#include <thread>
#include <curl/curl.h>
using namespace std;

void httpAsyncRequest(HttpRequest& req, HttpResponse& resp)
{
    std::cout << "POST URL IS " << req.GetURL()<< std::endl;
    CHttpClient *pcli = new CHttpClient();
    std::string strResponse;
    long code = 1111;
    code = pcli->Post(req.GetURL(), req.GetBody(), strResponse);
    resp.SetContext(strResponse);
    resp.SetSatusCode(code);
    std::cout << "ret: " << resp.GetStatusCode()<< " context: " << resp.GetContext()<< std::endl;


}

int main()
{ 
 
    g_thread_num = 4;
    HttpClientPool *pool =  HttpClientPool::GetHttpClientPool();
   
    curl_global_init(CURL_GLOBAL_ALL);
    for (int i = 0; i < 22; i++) {
        string post_data = "u=18814842159&p=111111&sign=42557FBC90E10CAD27FAC0F9D8BA94E9";
        string strUrl = "http://192.168.1.111:8080/v1/user/login";

        HttpRequest req("POST", strUrl, post_data);

        HttpResponse resp;
    
        CTask *task = new HttpTask(req, resp,  httpAsyncRequest);
        pool->AddTask(task);
    }


    std::this_thread::sleep_for(std::chrono::minutes(10));
    return 0;
}
