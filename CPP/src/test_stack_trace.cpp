#include "stack/stack_trace.h"
#include <csignal>
#include <iostream>
#include <map>
#include <sstream>
#include <thread>
#include <cstdio>
#include <unistd.h>

using namespace bv;

void sigroutine(int signo, siginfo_t *info, void *secret) {
    auto buff = StackTrace::get_stack_trace(0, secret);
    for (const auto &s : buff) {
        std::cout << " " << s << std::endl;
    }
    if (SIGSEGV == signo) {
        printf("SIGSEGV happened!");
    } else if (SIGINT == signo) {
        printf("ctrl+c kill!");
    } else if (SIGABRT == signo) {
        printf("SIGABRT happened!");
    }
#ifndef WIN32
    else if (SIGBUS == signo) {
        printf("Bus error !");
    }
#endif
    else {
        printf("Got signal [%d]. Exiting...", signo);
    }

    exit(0);
}
// TODO: install to other thread
void installSig()
{
#ifdef WIN32
    signal(SIGINT, sigroutine);
    signal(SIGTERM, sigroutine);
    signal(SIGABRT, sigroutine);
    signal(SIGSEGV, sigroutine);
#else

    struct sigaction act {
    };

    // 1. 安装SIGINT & SIGTERM信号
    sigemptyset(&act.sa_mask);
    act.sa_flags     = SA_SIGINFO | SA_ONSTACK;
    act.sa_sigaction = sigroutine;

    stack_t ss;
    ss.ss_flags = 0;
    ss.ss_size  = 2* SIGSTKSZ;
    ss.ss_sp    = malloc(ss.ss_size);
    sigaltstack(&ss, NULL);

    /*中断进程,Ctrl-C*/
    if (sigaction(SIGINT, &act, NULL) < 0) {
        printf("install sigal SIGINT error\n");
    }
    /// 2). kill pid in terminal
    if (sigaction(SIGTERM, &act, NULL) < 0) {
        printf("install SIGTERM error");
    }

    /// 3). segment fault
    if (sigaction(SIGSEGV, &act, NULL) < 0) {
        printf("install SIGSEGV error");
    }

    /// 4). bus error
    if (sigaction(SIGBUS, &act, NULL) < 0) {
        printf("install SIGBUS error");
    }
    if (sigaction(SIGABRT, &act, NULL) < 0) {
        printf("install SIGBUS error");
    }
#endif
}

void test2()
{
    /* auto buff = StackTrace::get_stack_trace();
     for (auto s : buff) {
         std::cout << " " << s << std::endl;
     }*/

    std::vector<int> x;

    x[10000] = 100;
}

void test1()
{
    test2();
}
void test5()
{
    throw 1;
}
void test4()
{
    test1();
}

void test3()
{
    test4();
}

int main()
{

    installSig();
    /*    std::set_terminate([](){
            auto buff = StackTrace::get_stack_trace();
            for (auto s : buff) {
                std::cout <<" " << s << std::endl;
            }
        });*/

    test3();
    // test1();

    auto p = std::thread([=]() {
        // std::vector<int> x;

        // x[10000] = 100;
        // System::sleep(100);
        test3();
    });

    /*auto buff =StackTrace::get_stack_trace();
    for (auto s : buff) {
        std::cout << s << std::endl;
    }*/
    sleep(100);

    if (p.joinable())
        p.join();
    return 0;
}