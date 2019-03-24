#ifndef HTTPC_UTILS_ARGS_HTTPC_OPTIONS_H_
#define HTTPC_UTILS_ARGS_HTTPC_OPTIONS_H_

#include <iostream>
#include <map>

class Options
{
private:
    //option name and isHasValue
    std::map<std::string, bool> options_dict_;
public:
    static const std::string PROXY_SERVER_IP;
    static const std::string PROXY_SERVER_PORT;
public:
    Options();
    bool DoesHaveKey(std::string key);
    bool DoesHaveValue(std::string key);
};

#endif