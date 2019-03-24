#ifndef HTTPC_CORE_HTTPC_HANDLER_
#include "core/httpc_handler.h"
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
#include <netdb.h>
#include <sys/select.h>

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

#ifndef HTTPC_CORE_HTTPC_HTTP_REQUEST_
#include "core/httpc_http_request.h"
#endif

#ifndef HTTPC_CORE_HTTPC_HTTP_RESPONSE_
#include "core/httpc_http_response.h"
#endif

#ifndef HTTPC_CORE_HTTPC_HTTP_
#include "core/httpc_http.h"
#endif

typedef struct sockaddr SA; 

Handler::Handler():client_fd_(-1)
{
    proxy_server_fd_ = -1;
}

Handler::Handler(int client_fd): client_fd_(client_fd)
{
    proxy_server_fd_ = -1;
}

void Handler::SetClientFd(int client_fd) {
    client_fd_ = client_fd;
}

bool Handler::RunHandlerService()
{
    return HandlerService();
}

bool Handler::HandlerService()
{
    //select
    fd_set rset, allset;
    FD_ZERO(&allset);
    FD_SET(client_fd_, &allset);
    int nready, maxfd;
    maxfd = client_fd_;

    int n;
    char buff[httpc::Tcp::kMaxDataLength + 100];
    int keep_alive = 1;
    setsockopt(client_fd_, SOL_SOCKET, SO_KEEPALIVE, &keep_alive, sizeof(keep_alive));

    for( ; ; )
    {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(FD_ISSET(client_fd_, &rset))
        {
            if( (n = read(client_fd_, buff, httpc::Tcp::kMaxDataLength)) == 0)
                break;
            else if(n == -1)
            {
                if(errno != EINTR)
                {
                    LOG.Error("errno: " + std::to_string(errno));
                    break;
                }
            }
            else
            {
                LOG.Debug("1, " + std::to_string(n));
                //to connect proxy server
                if(proxy_server_fd_ == -1)
                {
                    if (ConnectProxyServer(args.Get(Options::PROXY_SERVER_IP), \
                        args.Get(Options::PROXY_SERVER_PORT)) == true)
                    {
                        FD_SET(proxy_server_fd_, &allset);
                        maxfd = maxfd > proxy_server_fd_ ? maxfd : proxy_server_fd_;
                        setsockopt(proxy_server_fd_, SOL_SOCKET, SO_KEEPALIVE, &keep_alive, sizeof(keep_alive));
                    }
                    else
                        break;
                }   
                if(HttpRequest::IsHttpRequest(buff, n) == true) {
                    HttpRequest::AddPrefixToUrl(buff, n, "http://" + httpc::server::kDefaultServerIp);
                    n += ("http://" + httpc::server::kDefaultServerIp).length();
                }
                n = write(proxy_server_fd_, buff, n);   
                LOG.Debug("2, " + std::to_string(n));
            }
        }
        if(proxy_server_fd_ != -1 && FD_ISSET(proxy_server_fd_, &rset))
        {
            if( (n = read(proxy_server_fd_, buff, httpc::Tcp::kMaxDataLength)) == 0)
                break;
            else if(n == -1)
            {
                if(errno != EINTR)
                {
                    LOG.Error("errno: " + std::to_string(errno));
                    break;
                }
            }
            else
            {
                LOG.Debug("3, " + std::to_string(n));
                HttpResponse::Replace(buff, n, httpc::http::kDefaultReplaceSrc, httpc::http::kDefaultReplaceDes);
                n = write(client_fd_, buff, n);   
                LOG.Debug("4, " + std::to_string(n));
            }
        }
    }
    close(client_fd_);
    if(proxy_server_fd_ != -1)
        close(proxy_server_fd_);
    LOG.Info("closed the conn to " + args.Get(Options::PROXY_SERVER_IP));
    return true;
}

bool Handler::ConnectProxyServer(std::string proxy_server_ip, std::string proxy_server_port)
{
    struct sockaddr_in server_addr;
    proxy_server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(proxy_server_port.c_str()));
    inet_pton(AF_INET, proxy_server_ip.c_str(), &server_addr.sin_addr);
    if (connect(proxy_server_fd_, (SA *)&server_addr, sizeof(server_addr)) < 0)
    {
        LOG.Error("conn to " + proxy_server_ip + " failed, errno: " + std::to_string(errno));
        return false;
    }
    LOG.Info("conn to " + proxy_server_ip + " successfully");
    return true;
    //return SendHttpConnect();
}

// bool Handler::SendHttpConnect() {
//     HttpRequest http_request;
//     char buff[httpc::Tcp::kMaxDataLength];
//     int n;
//     http_request.SetMethod(httpc::http::HttpMethod::CONNECT);
//     http_request.SetUrl(std::string(client_ip_) + ":" + std::to_string(client_port_));
//     http_request.SetHttpVersison(httpc::http::kDefaultHttpVersion);
//     http_request.PutHeader(httpc::http::header::kHost, \
//         std::string(client_ip_) + ":" + std::to_string(client_port_));
    
//     n = write(server_fd_, http_request.ToString().c_str(), \
//         http_request.ToString().length());
//     if(n != http_request.ToString().length()) {
//         LOG.Error("send http connect to proxy server failed");
//         return false;
//     }
//     LOG.Info("send http connect to proxy server success");

// reread:    
//     if( (n = read(server_fd_, buff, httpc::Tcp::kMaxDataLength) == 0))
//         return false;
//     else if(n == -1)
//     {
//         if(errno != EINTR)
//         {
//             LOG.Error("errno: " + std::to_string(errno));
//             return false;
//         }
//         goto reread; 
//     }
//     else
//     {
//         HttpResponse http_response(buff, n);
//         if(atoi(http_response.GetStatusCode().c_str()) == 200){
//             LOG.Info("connect proxy server success");
//             return true;
//         }else {
//             LOG.Info("connect proxy server failed");
//             return false;
//         }
//     }
//     return false;
// }

