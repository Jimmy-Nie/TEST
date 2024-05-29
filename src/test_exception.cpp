#include <iostream>
#include <cstring>
#include <stdexcept>
#include <errno.h>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <sstream>
#include <vector>

void testOpen() {
    std::string str = "a.txt";
    std::string str_null = "null.txt";
    if (open(str_null.c_str(), O_WRONLY) < 0) {
        sleep(2);
        fprintf(stderr, "[%s:%d]: [%d: %s]\n", __FUNCTION__, __LINE__, errno, strerror(errno));
        //perror("open null.txt");
    }

    int fd = 0;
    if ((fd = (open(str.c_str(), O_WRONLY)) < 0)) {
        sleep(2);
        fprintf(stderr, "[%s:%d]: [%d: %s]\n", __FUNCTION__, __LINE__, errno, strerror(errno));
        //perror("open a.txt");
        return;
    }
    close(fd);
    printf( "[%s:%d]: [%d: %s]\n", __FUNCTION__, __LINE__, errno, strerror(errno));
}

void testStat() {
    std::string str = "/usr/local/";
    struct stat sb;
    if (stat(str.c_str(), &sb) == -1) {
        sleep(1);
        fprintf(stderr, "\n[%s:%d]: [%d: %s]\n", __FUNCTION__, __LINE__, errno, strerror(errno));
        //perror("stat");
    }
}


class Exception : public std::exception {
public:
    template<class... Args>
    Exception(const char* fmt, Args&&... args) {
        char buffer[1024];
        std::stringstream ss;
        ss << "[%s:%s:%d]: ";
        ss << fmt;
        ss << "\n";

        snprintf(buffer, sizeof(buffer), ss.str().c_str(),
                 __FILE__, __FUNCTION__, __LINE__, std::forward<Args&&>(args)...);
        message_ = buffer;
    }

    const char* what() const noexcept  override {
        return message_.c_str();
    }

private:

private:
    std::string message_;
};

void testException() {
    std::string str = "This is my friend!";
    throw Exception("He said: %s", str.c_str());
}

void testHex() {
    std::vector<std::string> ret;
    std::vector<int> stacks {22, 33, 44, 55, 66};
    std::stringstream ss;
    for(int i=0; i<stacks.size(); i++) {
        ss << "[/usr/local]: 0x";
        ss << std::hex << stacks[i];
        ret.push_back(ss.str().c_str());
    }

    for(auto& r : ret)
        std::cout << r << std::endl;
}

int main() {
/*    std::thread t1(testOpen);
    t1.detach();

    std::thread t2(testStat);
    t2.detach();*/

    try {
        testException();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    testHex();

    //sleep(10);
}
