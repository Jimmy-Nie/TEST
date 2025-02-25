#include <mutex>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <shared_mutex>

std::mutex mtx;
uint32_t number = 0;

void testMutex() {
    auto inc_attempt = []() {
        for(int i=0; i<1e5; i++) {
            mtx.lock();
            number++;
            mtx.unlock();
        }
    };

    std::thread threads[5];
    for(auto & th : threads) {
        th = std::thread(inc_attempt);
    }

    for(auto &th : threads)
        th.join();

    std::cout << __FUNCTION__ << ": The result: " << number << std::endl;
}

std::timed_mutex timed_mtx;
void testTimedMutex() {
    auto attempt_lock = [] (int id) {
        if(timed_mtx.try_lock_for(std::chrono::seconds(1))) {
            std::cout << "ID: " << id << " get the lock\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } else {
            std::cout << "ID: " << id << " NOT get the lock\n";
        }
    };

    std::thread threads[3];
    for(int i=0; i<3; i++) {
        threads[i] = std::thread(attempt_lock, i);
    }

    for(auto &th : threads)
        th.join();
}

void testSharedLock() {
    //std::shared_mutex shared_mtx;
    int data = 0;

    auto reader = [&](int id) {
        int i = 0;
        while(++i < 20) {
            //shared_mtx.lock_shared();
            std::cout << "Reader id: " << id << ", data: " << data << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            //shared_mtx.unlock_shared();
        }

    };

    auto writer = [&](int id = 0) {
        int i = 0;
        while(++i < 5) {
            //shared_mtx.lock();
            ++data;
            std::cout << "Writer id: " << id << ", data: " << data << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            //shared_mtx.unlock();
        }
    };

    std::thread writer_th(writer);

    std::thread readers[3];
    for(int i=0; i<3; i++) {
        readers[i] = std::thread(reader, i);
    }


    writer_th.join();
    for(auto &th : readers)
        th.join();
}

void testUniqueLock() {

}

int main() {
/*    testMutex();
    testTimedMutex();*/
    testSharedLock();
    testUniqueLock();

    std::this_thread::sleep_for(std::chrono::seconds(60));
}

