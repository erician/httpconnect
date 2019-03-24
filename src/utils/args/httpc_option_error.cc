#ifndef HTTPC_UTILS_ARGS_HTTPC_OPTION_ERROR_H_
#include "utils/args/httpc_option_error.h"
#endif

void OptionError::NotHaveThisOption(std::string option)
{
    std::cout<<"we don\'t have the option:"+option<<std::endl;
}
void OptionError::NotWithValue(std::string option)
{
    std::cout<<"the option of "+option+" must with a value"<<std::endl;
}
void OptionError::NotHaveSourceFile()
{
    std::cout<<"we don\'t have source file to compile"<<std::endl;
}