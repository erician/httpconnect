#include <iostream>
#include <string>
#include <cstring>

int main() {
    char str[] = "aaa\r\nbbb\r\n";
    std::cout << str[50] << std::endl;
    std::string s(str);
    std::cout << str << std::endl;
    std::cout << strlen(str) << std::endl;
    return 0;
}