#ifndef HTTPC_CORE_HTTPC_CONST_
#define HTTPC_CORE_HTTPC_CONST_

#include <string>

namespace httpc
{
    namespace proxyclient
    {
        const int kMaxConnections = 10000;
        const short kDefaultHttpPort = 80;
    };// proxyclient

    namespace proxyserver
    {
        const std::string kProxyType = "http 1.1";
    };// proxyserver

    namespace server
    {
        const std::string kDefaultServerIp = "192.168.3.22";
        const short kDefaultServerPort = 80;
    };// namespace server

    namespace proxy
    {
        const int kMaxConnections = 50;   
        const int kListenQ = 10;
    };//proxy

    namespace Tcp
    {
        const int kMss = 1460;
        const int kMaxDataLength = 65535;
    };//Tcp

};//httpc
#endif
