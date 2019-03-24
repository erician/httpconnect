#ifndef HTTPC_CORE_HTTPC_HTTP_REQUEST_
#include "core/httpc_http_request.h"
#endif

HttpRequest::HttpRequest() {
    ;
}

void HttpRequest::SetMethod(httpc::http::HttpMethod method) {
    method_ = std::string(httpc::http::HttpMethodName[method]);
}

void HttpRequest::SetUrl(std::string url) {
    url_ = url;
}

void HttpRequest::SetHttpVersison(std::string http_version) {
    http_version_ = http_version;
}

void HttpRequest::PutHeader(std::string key, std::string value) {
    headers_[key] = value;
}

std::string HttpRequest::ToString() {
    std::string message;
    message += method_ + httpc::http::kSpace + url_ + httpc::http::kSpace + \
                http_version_ + httpc::http::kCRLF;
    for(std::map<std::string, std::string>::iterator it=headers_.begin(); it != headers_.end(); it++) {
        message+= (it->first + httpc::http::header::kDelimiter + it->second + httpc::http::kCRLF); 
    }
    message += httpc::http::kCRLF;
    message += body_;
    return message;
}

/* this function is right for most case, but not all */
bool HttpRequest::IsHttpRequest(const char *cont, int len) {
    char method[httpc::http::kMaxHttpMethodLen+1];
    int i = 0;
    while(cont[i] != httpc::http::kSpace) {
        method[i] = cont[i];
        i++;
        if(i>httpc::http::kMaxHttpMethodLen)
            return false;
    }
    method[i] = '\0';
    for(int i=0; i<httpc::http::HttpMethodNum; i++) {
        if(strcmp(method, httpc::http::HttpMethodName[i]) == 0) {
            return true;
        }
    }
    return false;
}

void HttpRequest::AddPrefixToUrl(char *cont, int len, std::string prefix) {
    int url_start_pos = 0;
    while(cont[url_start_pos] != httpc::http::kSpace) {
        url_start_pos++;
    }
    url_start_pos++;
    for(int i=len-1; i>=url_start_pos; i--) {
        cont[i+prefix.length()] = cont[i];
    }
    for(int i=0; i<prefix.length(); i++) {
        cont[i+url_start_pos] = prefix[i];
    }
}