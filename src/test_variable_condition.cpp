#include <condition_variable>
#include <mutex>
#include <thread>
#include <atomic>
#include <iostream>
#include <chrono>
#include <thread>

std::mutex lock;
std::condition_variable condVar;

std::atomic<bool> dataReady{false};

void waitingForWork() {
    std::cout << "Waiting ..." << std::endl;
    std::unique_lock<std::mutex> l(lock);
    while(!condVar.wait_for(l, std::chrono::milliseconds(std::numeric_limits<int32_t>::max()), []{return dataReady.load();})) {
        std::cout << "x ";
        std::cout.flush();
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Running ..." << std::endl;
}

void setDataReady(bool ready) {
    dataReady = ready;
    std::cout << "Data prepared, notify one" << std::endl;
    condVar.notify_one();
}

int main() {
    std::cout << "==========Begin==========" << std::endl;

    std::thread t1(waitingForWork);

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "\nset true" << std::endl;
    setDataReady(true);

    t1.join();

    std::cout << "===========End===========" << std::endl;
}