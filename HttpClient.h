#ifndef __HTTP_CURL_H__
#define __HTTP_CURL_H__

#include <string>
class HttpRequest
{
public:
    HttpRequest(){}
    HttpRequest (const std::string&, const std::string&, const std::string&);
    virtual ~HttpRequest (){};
    const std::string& GetMethod() const {return m_method;}
    const std::string& GetURL() const {return  m_url;}
    const std::string& GetBody() const {return m_body;}
private:
    std::string m_method;
    std::string m_url;
    std::string m_body;
};

class HttpResponse
{
public:
    HttpResponse (){};
    virtual ~HttpResponse (){};
    void SetSatusCode(const long code){ m_statusCode = code; }
    void SetContext(const std::string& context) { m_context = context; }
    long GetStatusCode() const {return m_statusCode;}
    const std::string& GetContext()const {return m_context;}

private:
    long m_statusCode;
    std::string m_context;
};

class CHttpClient
{
public:
	CHttpClient(void);
	~CHttpClient(void);

public:

	long Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse);
	long Get(const std::string & strUrl, std::string & strResponse);
	long Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath = NULL);
	long Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath = NULL);

public:
	void SetDebug(bool bDebug);

private:
	bool m_bDebug;
};

#endif

