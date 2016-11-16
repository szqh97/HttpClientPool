#include <iostream>
#include <string>
#include "HttpConnPool.h"
using namespace std;


int main()
{
    HttpConnPool *pool =  new HttpConnPool(8);
    pool->Init();
    string post_data = "u=18814842159&p=111111&sign=42557FBC90E10CAD27FAC0F9D8BA94E9";
    string strUrl = "http://app-test.kaipao.cc/v1/user/loginx";
    strUrl = "http://google.com/";
    Request req ;
    req.method = "POST";
    req.strUrl = strUrl;
    req.body = post_data;
    
    for (auto i = 0; i < 22; i++) {
        HttpConn *conn = pool->GetHttpConn();
        conn->ProcRun(req);
        pool->RelHttpConn(conn);
    }

    return 0;
}
