#ifndef HTTPC_UTILS_HTTPC_OPTION_ERROR_H_
#define HTTPC_UTILS_HTTPC_OPTION_ERROR_H_

#include <iostream>
class OptionError
{
public:
    static void NotHaveThisOption(std::string option);
    static void NotWithValue(std::string option);
    static void NotHaveSourceFile();
};

#endif