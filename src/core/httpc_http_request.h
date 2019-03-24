#ifndef HTTPC_CORE_HTTPC_HTTP_REQUEST_
#define HTTPC_CORE_HTTPC_HTTP_REQUEST_

#ifndef HTTPC_CORE_HTTPC_HTTP_
#include "core/httpc_http.h"
#endif

#include <string>
#include <map>

class HttpRequest {
public:
    HttpRequest();
    void SetMethod(httpc::http::HttpMethod method);
    void SetUrl(std::string url);
    void SetHttpVersison(std::string http_version);
    void PutHeader(std::string key, std::string value);
    std::string ToString();
    static bool IsHttpRequest(const char *cont, int len);
    static void AddPrefixToUrl(char *cont, int len, std::string prefix);

private: 
    std::string method_;
    std::string url_;
    std::string http_version_;
    std::map<std::string, std::string> headers_;
    std::string body_;
    bool ParseHttpRequest(char *request);
};

#endif