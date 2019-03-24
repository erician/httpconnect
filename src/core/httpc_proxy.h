#ifndef HTTPC_CORE_HTTPC_PROXY_
#define HTTPC_CORE_HTTPC_PROXY_ 

#ifndef HTTPC_CORE_HTTPC_HANDLER_
#include "core/httpc_handler.h"
#endif

#include <iostream>
#include <vector>

class Proxy
{
public:
    Proxy();
    Proxy(int max_connections);
    bool RunProxyService();

private:
    const int kMaxConnections_;         // not use
    static int current_connection_num_;

    bool Init();
    static void ProxyServiceThread();
    static void ServiceThread(int conn_fd);

};

#endif
