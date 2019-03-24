#ifndef HTTPC_CORE_HTTPC_HTTP_
#define HTTPC_CORE_HTTPC_HTTP_

#ifndef HTTPC_CORE_HTTPC_CONST_
#include "core/httpc_const.h"
#endif

#include <string>
#include <cstring>

namespace httpc {

namespace http {

enum HttpMethod {
    GET = 0,
    PUT, 
    DELETE, 
    HEAD,
    POST,
    TRACE,
    CONNECT,
    HttpMethodNum,
};

const char * const HttpMethodName[HttpMethodNum] = {
    "GET",
    "PUT",
    "DELETE",
    "HEAD",
    "POST",
    "TRACE",
    "CONNECT",
};

const int kMaxHttpMethodLen = 7;
const std::string kDefaultHttpVersion = "HTTP/1.1";
const char kSpace = ' ';
const std::string kCRLF = "\r\n";
const std::string kDefaultReplaceSrc = httpc::server::kDefaultServerIp;
const std::string kDefaultReplaceDes = "eastlake.git";

namespace header {
    const std::string kHost = "Host";
    const std::string kDelimiter = ": ";
} //namespace header



} //namespace http

} //namespace httpc

#endif