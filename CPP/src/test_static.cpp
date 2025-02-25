//
// Created by Jimmy on 2024/5/10.
//
#include <iostream>
#include <string>
#include <vector>

class TestStatic {
public:
    TestStatic(const std::string &str) : str_(str) { }

    int getSize() { return str_.length(); }
public:
    static int getSize(const std::string &str) {
        TestStatic ts(str);
        return ts.getSize();
    }

private:
    std::string str_;
};

int main() {
    TestStatic ts("123123123");
    std::cout << "Construct size: " << ts.getSize() << std::endl;
    std::cout << "The static size: " << TestStatic::getSize("hello, world!") << std::endl;

    std::vector<char> vc = {'1', '2', '3', 0, 0, 0, '4', '5', 0, 0, 0, 0};
    std::string str;
    str.assign(vc.begin(), vc.end());
    std::cout << str << ", size: " << str.size() << std::endl;
}