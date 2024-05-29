#include <iostream>

using namespace std;


#include <ctime>
#include <iostream>
#include <chrono>
#include <ctime>

void date_time() {
    time_t now = time(0);
    char* currentTime = ctime(&now);
    std::cout << "当前时间为: " << currentTime;
}

void date_time_ms() {
    // 使用high_resolution_clock获取当前时间
    auto now = std::chrono::high_resolution_clock::now();

    // 将时间转换为time_t以便使用ctime()函数
    std::time_t now_c = std::chrono::high_resolution_clock::to_time_t(now);

    // 使用ctime()获取当前时间的字符串表示
    std::cout << "Current time: " << std::ctime(&now_c);

    // 获取自纪元以来的毫秒数
    auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    // 打印毫秒数
    std::cout << "Milliseconds: " << duration_in_ms.count() << std::endl;
}

uint64_t clocktime_us() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000ULL + ts.tv_nsec / 1000;
}

int main() {
    //date_time_ms();
    std::cout << "System uptime: " << clocktime_us() << " us\n";
    std::cout << "System uptime: " << clocktime_us()/(1e6*60) << " min\n";
    return 0;
}