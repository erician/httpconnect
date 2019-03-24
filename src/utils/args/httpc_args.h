#ifndef HTTPC_UTILS_ARGS_HTTPC_ARGS_H_
#define HTTPC_UTILS_ARGS_HTTPC_ARGS_H_

#include <iostream>
#include <map>
#include <vector>
#include <string>

#ifndef HTTPC_UTILS_ARGS_HTTPC_OPTIONS_H_
#include "utils/args/httpc_options.h"
#endif

#ifndef HTTPC_UTILS_ARGS_HTTPC_OPTION_ERROR_H_
#include "utils/args/httpc_option_error.h"
#endif

class Args
{
public:
    Args(){}
    bool ParseArgs(int argc, char *argv[]);
    void Set(std::string, std::string value);
    std::string Get(std::string key);
    bool HasKey(std::string key);
    bool DoesOnlyHaveSrc();

private:
    Options all_options_;
    std::map<std::string, std::string> arg_dict_;
    int ParseArgsStartsWithSingleStrikethrough(char *option, char *value);
    int ParseArgsStartsWithDoubleStrikethrough(char *option);
    std::string CharToString(char ch);

};
extern Args args;
#endif