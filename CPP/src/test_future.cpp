#include <iostream>
#include <future>
#include <string>
#include <chrono>
#include <thread>

uint32_t add(uint32_t x) {
    uint32_t result = 0;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "The thread id: 0x" << std::hex << std::this_thread::get_id() << std::dec << std::endl;
    for(uint32_t i = 0; i <= x; ++i) {
        result += i;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return result;
}

void test_future_wait() {
    uint32_t ret = 0;
    std::future<uint32_t> result = std::async(add,100);
    std::cout << "waiting ..." << std::endl;
    std::cout << "future valid: "<< result.valid() << std::endl; // second get
    std::cout << "+++++ future state: "<< static_cast<int>(result.wait_for(std::chrono::milliseconds(10))) << std::endl; // second get

    int i = 0;
    while(result.wait_for(std::chrono::milliseconds(10)) != std::future_status::ready) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        std::cout << ++i << std::endl;
    }

/*    while(++i < 20) {
        std::cout << "++++ The future state: " << static_cast<int>(result.wait_for(std::chrono::milliseconds(0))) << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
*//*        try {
            std::cout << "-------- result get: " << result.get() << std::endl; // second get
        } catch (const std::future_error& e) {
            std::cout << "future_error : " << e.what() << std::endl;
            break;
        }*//*
    }*/
    std::cout << "\nfuture state: " << result.valid() << std::endl; // second get
    std::cout << "ready ..." << std::endl;
    std::cout << "result get: " << result.get() << std::endl; // second get
}

int main() {
    test_future_wait();
    return 0;
}