//
// Created by Jimmy on 2024/5/11.
//

#include <iostream>
#include <string>
#include <cstring>

void testString () {
    std::string full_str = "Hello, world! my name is Jimmy";
    std::string sub_str1 = "Jimmy1";
    std::string sub_str2 = "Jimmy";

    std::string::size_type pos = full_str.find_first_of(sub_str1);
    if(pos != std::string::npos)
        std::cout << "The pos " << pos << std::endl;

    pos = full_str.find_first_of(sub_str1, 17);
    if(pos != std::string::npos)
        std::cout << "The pos " << pos << std::endl;

    pos = full_str.find(sub_str2);
    if(pos != std::string::npos)
        std::cout << "The pos " << pos << std::endl;

    pos = full_str.find(sub_str2, 10);
    if(pos != std::string::npos)
        std::cout << "The pos " << pos << std::endl;
}

void testStr1() {
    std::string str = "\n\nHello, world!\nThis is my son!\nNo, No, No!\n\n";
    std::string::size_type first = str.find_first_not_of("\n");
    std::string::size_type last = str.find_last_not_of("\n");

    if(first != std::string::npos && last != std::string::npos) {
        std::cout << "First: " << first << ", last: " << last << std::endl;
        std::cout << "The substr: " << str.substr(first, last - first + 1) << std::endl;
    }
}

void testSTLString() {
    std::string str = "        Hello, world!        ";
    std::string str1 (str);

    auto pos = str.find_first_not_of(' ');
    if(pos == std::string::npos)
        str1.clear();
    str1 = str.substr(pos);

    pos = str1.find_last_not_of(' ');
    if(pos != std::string::npos)
        str1 = str1.substr(0, pos+1);

    std::cout << str1 << " ##LEN: " << str1.length() << std::endl;
}

void testStrtok() {
    std::string str = "hello           world 1      2                3";
    std::string delimiter = " ";
    char* token = strtok(const_cast<char*>(str.c_str()), delimiter.c_str());
    while(token) {
        std::cout << token << " ";
        token = std::strtok(nullptr, delimiter.c_str());
    }
    std::cout << std::endl;
}

int main() {
    testStrtok();
    return 0;
}