#ifndef HTTPC_CORE_HTTPC_HTTP_RESPONSE_
#define HTTPC_CORE_HTTPC_HTTP_RESPONSE_

#include <string>
#include <iostream>
#include <map>

class HttpResponse {
public:
    HttpResponse();
    HttpResponse(char *response, int response_len);
    void SetResponseAndResponseLen(char *response, int response_len);
    static void Replace(char *response, int response_len, std::string src, std::string des);
    std::string GetStatusCode();

private:
    char *response_;
    int response_len_;
    std::string http_version_;
    std::string status_code_;
    std::string reason_phrase_;
    std::map<std::string, std::string> headers_;
    std::string body_;

};

#endif