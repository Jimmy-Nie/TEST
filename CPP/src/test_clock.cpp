//
// Created by Jimmy on 2024/5/23.
//

#include<sys/times.h>
#include<stdio.h>
#include<unistd.h>
#include <unistd.h>

int main() {
    struct tms start;
    struct tms end;
    clock_t t_start = 0;
    clock_t t_end = 0;
    long tck = 0;
    int i = 0, j = 0;

    tck = sysconf(_SC_CLK_TCK);        //调用sysconf函数获取系统的节拍率,需包含<unistd.h>头文件
    t_start = times(&start);
    if (-1 == t_start) {
        perror("times error");
        return (-1);
    }

    for (i = 0; i < 10000; i++) {
        for (j = 0; j < 20000; j++);
    }

    sleep(2);

    t_end = times(&end);
    if (-1 == t_end) {
        perror("times error");
        return  -1;
    }

    printf("TCK: %ld\n", tck);
    printf("t_end=%ld, end.tms_utime=%ld, end.tms_stime=%ld\n\n", t_end, end.tms_utime, end.tms_stime);

    printf("时间总和 = %f秒\n", (t_end - t_start) / (double) tck);
    printf("用户CPU时间 = %f秒\n", (end.tms_utime - start.tms_utime) / (double) tck);
    printf("系统CPU时间 = %f秒\n", (end.tms_stime - start.tms_stime) / (double) tck);

    return 0;
}