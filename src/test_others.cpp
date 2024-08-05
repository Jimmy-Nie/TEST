#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>  // for std::tolower and std::isspace

void testTransform() {
    std::string level = "Iam A Little BOY!!!";

    // 使用 lambda 函数转换为小写并处理空格
    std::transform(level.begin(), level.end(), level.begin(),
                   [](unsigned char c) -> char {
                       if (std::isspace(c)) {
                           return ' ';  // 将空格替换为其他字符或者去掉这行以去除空格
                       } else {
                           return static_cast<char>(std::tolower(c));
                       }
                   });

    // 输出转换后的字符串
    std::cout << level << std::endl;
}

int main() {
    testTransform();
    return 0;
}
