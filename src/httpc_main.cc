
#ifndef HTTPC_CORE_HTTPC_PROXY_
#include "core/httpc_proxy.h"
#endif

#include <iostream>
#include <fstream>
#include <exception>

#ifndef HTTPC_LOGGING_HTTPC_LOGGING_
#include "logging/httpc_logging.h"
#endif

#ifndef HTTPC_UTILS_ARGS_HTTPC_ARGS_H_
#include "utils/args/httpc_args.h"
#endif

int main(int argc,char *argv[])
{
    try
    {   
        if (args.ParseArgs(argc, argv) == false )
            return -1;
        if( args.HasKey(Options::PROXY_SERVER_IP) == false || 
            args.Get(Options::PROXY_SERVER_IP) == "" ) 
        {
            LOG.Error("must set proxy server ip");
            return -1;
        }
        if( args.HasKey(Options::PROXY_SERVER_PORT) == false || 
            args.Get(Options::PROXY_SERVER_PORT) == "" ) 
        {
            LOG.Error("must set proxy server port");
            return -1;
        }

        LOG.Info("start httpconnect");
        Proxy proxy;
        proxy.RunProxyService();
        return 0;
    }
    catch(std::exception& e)
    {
        LOG.Error(e.what());
        return -1;
    }
}