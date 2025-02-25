/**
 * @file: simple_timer.h
 * @brief:
 * @author: Jimmy Nie (nieshihua@126.com)
 * @date: 2024-04-12
 */
#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <sys/time.h>
#include <thread>
namespace bv
{
/**
 * \brief: the simple timer
 */
class SimpleTimer {
public:
    using clock = std::chrono::steady_clock;

public:
    SimpleTimer() { start(); }

    ///\brief: (re)start the timer
    void start() { m_start_ = clock::now(); }

    ///\brief: elapsed (nano/micro/milli/.)seconds since start
    uint32_t elapsed_s() {
        return static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::seconds>(clock::now() - m_start_).count());
    }

    uint32_t elapsed_ms() {
        return static_cast<unsigned int>(
            std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - m_start_).count());
    }

    uint64_t elapsed_us() {
        return static_cast<uint64_t>(
            std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - m_start_).count());
    }

    uint64_t elapsed_ns() {
        return static_cast<uint64_t>(
            std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - m_start_).count());
    }

public:
    ///\brief: sleep for period duration
    static void sleep_sec(uint32_t secs) { std::this_thread::sleep_for(std::chrono::seconds(secs)); }
    static void sleep_msec(uint32_t msecs) { std::this_thread::sleep_for(std::chrono::milliseconds(msecs)); }
    static void sleep_usec(uint32_t usecs) { std::this_thread::sleep_for(std::chrono::microseconds (usecs)); }

    ///\brief: get current time in sec/msec/usec (from epoch)
    static uint64_t get_current_sec() { return (get_current_usec() / 1000000); }
    static uint64_t get_current_msec() { return (get_current_usec()/1000); }
    static uint64_t get_current_usec() {
        auto tp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
        return (tp.time_since_epoch().count());
    }


    ///\brief: get the sec/msec/usec/nsec from system boot
    static uint64_t get_sys_boot_sec() { return get_sys_boot_nsec() / 1e9; }
    static uint64_t get_sys_boot_msec() { return get_sys_boot_nsec() / 1e6; }
    static uint64_t get_sys_boot_usec() { return get_sys_boot_nsec() / 1e3; }
    static uint64_t get_sys_boot_nsec() { return std::chrono::steady_clock::now().time_since_epoch().count(); }

    ///\brief: get the local time zone
    ///\Return: +8(UTC+8), -8(UTC-8)
    static int get_time_zone() {
        int timezone = 0;
        time_t t1, t2;
        struct tm *tm_utc;

        time(&t1);                  ///返回从公元1970年1月1日的UTC时间从0时0分0秒算起到现在所经过的秒数
        tm_utc = gmtime(&t1);       ///返回的时间日期未经时区转换，格林尼治时间
        t2 = mktime(tm_utc);        ///转换为秒
        timezone = (t1 - t2) / 3600;

        return timezone;
    }

    ///\brief: get the date string and time zone
    static std::string get_date_string()  {
        std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
        time_t tt = std::chrono::system_clock::to_time_t(today);
        return ctime(&tt);
    }

private:
    clock::time_point m_start_;
};
} // namespace bv
