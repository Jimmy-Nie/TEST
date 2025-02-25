
#include <iostream>
#include <ctime>
#include <cmath>
 
void test_abs() {
    std::cout << "The abs(1.11) = " << std::abs(-1.11) << std::endl;
    std::cout << "The fabs(1.11) = " << std::fabs(-1.11) << std::endl;
}
int main() {
    std::time_t now = std::time(nullptr);  // 获取当前时间
    std::tm *ptm = std::localtime(&now);   // 转换为本地时间
 
    // 打印时区信息
    // 注意：std::put_time在C++11及以后的版本中可用
    //std::cout << "Local Time: " << std::put_time(ptm, "%Y-%m-%d %H:%M:%S %Z") << std::endl;
 
    // 如果std::put_time不可用，可以手动构造时区信息
    // 注意：此方法依赖于环境变量TZ，可能不在所有系统中设置
    char tz[10];
    std::strftime(tz, sizeof(tz), "%Z", ptm);
    std::cout << "Time Zone: " << (tz[0] ? tz : "Unknown") << std::endl;
 
    test_abs();
    return 0;
}