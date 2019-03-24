#ifndef HTTPC_CORE_HTTPC_HTTP_RESPONSE_
#include "core/httpc_http_response.h"
#endif

#ifndef HTTPC_CORE_HTTPC_HTTP_
#include "core/httpc_http.h"
#endif

#ifndef HTTPC_UTILS_HTTPC_STRINGUTIL_
#include "utils/httpc_stringutil.h"
#endif

HttpResponse::HttpResponse() {
    response_ = NULL;
    response_len_ = 0;
}

HttpResponse::HttpResponse(char *response, int response_len) {
    response_ = response;
    response_len_ = response_len;
}

std::string HttpResponse::GetStatusCode() {
    if(status_code_.length() != 0)
        return status_code_;

    int start = 0;
    int cnt = 0;
    while(response_[start] != httpc::http::kSpace)
        start++;
    start++;
    while(response_[start+cnt] != httpc::http::kSpace) 
        cnt++;
    status_code_ = std::string(response_+start, cnt);
    return status_code_;
}

void HttpResponse::SetResponseAndResponseLen(char *response, int response_len) {
    response_ = response;
    response_len_ = response_len;
}



void HttpResponse::Replace(char *response, int response_len, std::string src, std::string des) {
    for(int i=0; i+src.length() < response_len; i++) {
        if(httpc::utils::stringutil::strcmpn(response+i, src.c_str(), src.length())==true) {
            for(int j=0; j<src.length(); j++) {
                response[i+j] = des.c_str()[j];
            }
            i += src.length();
        }
    }
}