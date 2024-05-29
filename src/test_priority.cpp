#include <pthread.h>
#include <sched.h>

#include <cstdio>
#include <cstring>
#include <thread>
#include <chrono>
#include <iostream>

#include "simple_timer.h"

using namespace std::chrono_literals;

void func() {
    bv::SimpleTimer tm;

    int policy;
    sched_param sch;
    pthread_getschedparam(pthread_self(), &policy, &sch);
    printf("%#x: sched policy %d, thread priority %d\n", pthread_self(), policy, sch.sched_priority);
    //printf("Sched Policy: [SCHED_FIFO:%d] [SCHED_RR:%d] [SCHED_OTHER:%d]\n", SCHED_FIFO, SCHED_RR, SCHED_OTHER);
    for(int i=0; i<1e5; i++)
        for(int j=0; j<2e4; j++)
            ;
        printf("TID: [%#x] cost %lf seconds\n", pthread_self(), tm.elapsed_ms() / 1000.0F);
}

int main() {
    sched_param sch;

    std::thread t1(func);
    sch.sched_priority = 1;
    if (pthread_setschedparam(t1.native_handle(), SCHED_FIFO, &sch)) {
        printf("%d: set sched param failed - %s\n", __LINE__, strerror(errno));
    }

    std::thread t2(func);
    sch.sched_priority = 20;
    if (pthread_setschedparam(t2.native_handle(), SCHED_FIFO, &sch)) {
        printf("%d: set sched param failed - %s\n", __LINE__, strerror(errno));
    }

    std::thread t3(func);
    sch.sched_priority = 40;
    if (pthread_setschedparam(t3.native_handle(), SCHED_FIFO, &sch)) {
        printf("%d: set sched param failed - %s\n", __LINE__, strerror(errno));
    }

    std::thread t4(func);
    sch.sched_priority = 1;
    if (pthread_setschedparam(t4.native_handle(), SCHED_RR, &sch)) {
        printf("%d: set sched param failed - %s\n", __LINE__, strerror(errno));
    }

    std::thread t5(func);
    sch.sched_priority = 20;
    if (pthread_setschedparam(t5.native_handle(), SCHED_RR, &sch)) {
        printf("%d: set sched param failed - %s\n", __LINE__, strerror(errno));
    }

    std::thread t6(func);
    sch.sched_priority = 40;
    if (pthread_setschedparam(t6.native_handle(), SCHED_RR, &sch)) {
        printf("%d: set sched param failed - %s\n", __LINE__, strerror(errno));
    }

    std::thread t7(func);
    std::thread t8(func);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    return 0;
}
