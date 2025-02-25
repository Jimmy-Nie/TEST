#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <thread>
#include <iostream>
#include <chrono>

void *func1(void *arg){
    int i=0;
    for(i=0;i<10;i++){
        printf("func1 %d\n",i);
        sleep(1);
    }

    pthread_exit(NULL);


}


int main() {

    int ret = -1;
    pthread_t tid = -1;

    pthread_create(&tid, NULL, func1, NULL);

    sleep(3);
    printf("sleep 3s cancel\n");
    pthread_cancel(tid);

    int i = 0;
    while (++i < 10) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}