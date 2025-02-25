#include <iostream>
#include <string>
#include <unistd.h>

void exitFunc() {
    sleep(1);
    std::cout << "Bye Bye" << std::endl;
}

int main() {
    atexit(exitFunc);
    std::cout << "End main()" << std::endl;
    return 0;
}