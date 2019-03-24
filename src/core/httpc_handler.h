#ifndef HTTPC_CORE_HTTPC_HANDLER_
#define HTTPC_CORE_HTTPC_HANDLER_

#include <iostream>
#include <string>

class Handler
{
public:
    Handler();
    Handler(int conn_fd);
    bool RunHandlerService();
    bool ConnectProxyServer(std::string proxy_server_ip, std::string proxy_server_port);
    bool SendHttpConnect();
    void SetClientFd(int client_fd);
         
private:
    int client_fd_;
    int proxy_server_fd_;
    bool HandlerService();    
};

#endif