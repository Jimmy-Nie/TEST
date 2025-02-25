#include <iostream>
#include <functional>
#include <string>
#include <chrono>
#include <thread>

std::function<int(int, int)> func;

int add(int x, int y) {
    std::cout << x << " + " << y << " = " << x + y << std::endl;
    return x+y;
}

int sub(int x, int y) {
    std::cout << x << " - " << y << " = " << x - y << std::endl;
    return x-y;
}

int main() {
    func = add;
    int result = func(123,321);
    std::cout << result << std::endl;

    func = sub;
    result = func(123,321);
    std::cout << result << std::endl;

    auto f1 = std::bind(add, 11, 22);
    f1();

    auto f2 = std::bind(add, std::placeholders::_1, 20);
    f2(10);

    auto f3 = std::bind(sub, std::placeholders::_2, std::placeholders::_1);
    f3(10, 20);

    auto f4 = std::bind([&](int a, int b) {return a*b;}, std::placeholders::_1, std::placeholders::_2);
    std::cout << f4(11, 22) << std::endl;

    return 0;
}
