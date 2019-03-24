#ifndef HTTPC_CORE_HTTPC_PROXY_
#include "core/httpc_proxy.h"
#endif

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <thread>

#ifndef HTTPC_CORE_HTTPC_CONST_
#include "core/httpc_const.h"
#endif

#ifndef HTTPC_LOGGING_HTTPC_LOGGING_
#include "logging/httpc_logging.h"
#endif

#ifndef HTTPC_UTILS_ARGS_HTTPC_ARGS_H_
#include "utils/args/httpc_args.h"
#endif

#ifndef HTTPC_UTILS_ARGS_HTTPC_ARGS_H_
#include "utils/args/httpc_options.h"
#endif

typedef struct sockaddr SA; 

int Proxy::current_connection_num_ = 0;

Proxy::Proxy():kMaxConnections_(httpc::proxyclient::kMaxConnections)
{
    Init();
}

Proxy::Proxy(int max_connections):kMaxConnections_(max_connections)
{
    Init();
}

bool Proxy::Init()
{
    return true;
}

bool Proxy::RunProxyService()
{
    std::thread http_th(ProxyServiceThread);
    http_th.join();
    return true;
}

void Proxy::ProxyServiceThread()
{
    int listen_fd, conn_fd;
    socklen_t client_socket_len;
    struct sockaddr_in client_addr, server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(httpc::proxyclient::kDefaultHttpPort);
    
    //when protocol is 0, if the type is stream, which means tcp; if the type is datagram, means udp  
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(listen_fd, (SA *)&server_addr, sizeof(server_addr)) == -1)
    {
        LOG.Error("bind error, errno: " + std::to_string(errno));
        return;
    }
    if(listen(listen_fd, httpc::proxy::kListenQ) == -1)
    {
        LOG.Error("listen error, errno: " + std::to_string(errno));
        return;
    }
    for( ; ; )
    {
        client_socket_len = sizeof(client_addr);
        if( (conn_fd = accept(listen_fd, (SA *)&client_addr, &client_socket_len)) < 0)
        {
            if (errno == EINTR)
                continue;
            else
                LOG.Error("accept error");
        }
        else
        {
            std::thread th(ServiceThread, conn_fd);
            th.detach();
            current_connection_num_++;
            LOG.Info("accept conn, current connection num:" + std::to_string(current_connection_num_));
        }
        
    }
    return;
}

void Proxy::ServiceThread(int conn_fd)
{
    Handler handler(conn_fd);
    handler.RunHandlerService();
}
