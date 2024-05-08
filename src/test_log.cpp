#include <cstdio>
#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>

std::string time_ms() {
    // 使用high_resolution_clock获取当前时间
    auto now = std::chrono::high_resolution_clock::now();

    // 将时间转换为time_t以便使用ctime()函数
    std::time_t now_c = std::chrono::high_resolution_clock::to_time_t(now);

    // 转换为tm结构
    std::tm* now_tm = std::localtime(&now_c);

    // 获取自纪元以来的毫秒数
    auto duration_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    ///按照格式输出时间
    std::stringstream ss;
    ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << "." << duration_in_ms.count();
    return ss.str();
}

#define Error(fmt, ...) printf("[%s] [%s:%s:%d] [ERROR]: " fmt "\n",    time_ms().c_str(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define Warn(fmt, ...) printf("[%s] [%s:%s:%d] [WARN]: " fmt "\n",      time_ms().c_str(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define Info(fmt, ...) printf("[%s] [%s:%s:%d] [INFO]: " fmt "\n",      time_ms().c_str(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define Debug(fmt, ...) printf("[%s] [%s:%s:%d] [DEBUG]: " fmt "\n",    time_ms().c_str(), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

int main() {
    Error("Hello");
    Warn("World");
    Info("Web");
    Debug("Wide");

    return 0;
}