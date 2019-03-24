#ifndef HTTPC_UTILS_HTTPC_STRINGUTIL_
#define HTTPC_UTILS_HTTPC_STRINGUTIL_

#include <iostream>
#include <vector>

namespace httpc
{
    namespace utils
    {
        namespace stringutil
        {
            std::vector<std::string> split(std::string src, std::string str_to_find);
            std::string strip(std::string src,char c); 
            bool strcmpn(const char *src, const char *des, int n);

        };//stringutil
    };//utils

};//httpc
#endif