#pragma once

class Timer {
public:
    Timer() { start(); }

    uint64_t elapsed_usec() {
        return static_cast<uint64_t>( std::chrono::duration_cast<std::chrono::microseconds>
                (std::chrono::steady_clock::now() - start_).count() );
    }

    void start() { start_ = std::chrono::steady_clock::now(); }

private:
    std::chrono::steady_clock::time_point start_;
};