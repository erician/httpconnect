#ifndef HTTPC_UTILS_ARGS_HTTPC_OPTIONS_H_
#include "utils/args/httpc_options.h"
#endif

const std::string Options::PROXY_SERVER_IP = "i"; 
const std::string Options::PROXY_SERVER_PORT = "p"; 

Options::Options()
{
    options_dict_[PROXY_SERVER_IP] = true;
    options_dict_[PROXY_SERVER_PORT] = true;
}

bool Options::DoesHaveKey(std::string key)
{
    if (options_dict_.find(key) != options_dict_.end())
        return true;
    else
        return false;
}

bool Options::DoesHaveValue(std::string key)
{
    if (DoesHaveKey(key) == true)
        return options_dict_[key];
    else
        return false;
}

