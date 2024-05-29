#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <thread>

double getCpuFrequencies() {
    std::ifstream cpuinfo_file("/proc/cpuinfo");
    std::string line;
    std::string frequency_str;
    double frequency = 0.0;

    while (std::getline(cpuinfo_file, line)) {
        if(line.find("cpu MHz") != std::string::npos) {
            frequency_str = line.substr(line.find(':')+1);
            std::cout << "The line: " << line << std::endl;
            std::cout << "The frequency str:" << frequency_str << "###########\n";
            break;
        }
    }

    try {
        frequency = std::stod(frequency_str);
    } catch (...) {
        std::cout << "frequency_str=" << frequency_str << " invalid!\n";
    }
    return frequency;
}

std::string getCpuModelName() {
    std::ifstream cpuinfo_file("/proc/cpuinfo");
    std::string line;
    std::string model_name;

    while (std::getline(cpuinfo_file, line)) {
        if(line.find("model name") != std::string::npos) {
            model_name = line.substr(line.find(':') + 2);
            break;
        }
    }

    return model_name;
}


struct CpuParam {
    unsigned long long user = 0;
    unsigned long long nice = 0;
    unsigned long long system = 0;
    unsigned long long idle = 0.0;
};

CpuParam pre_cpu_param_;

double getCpuUsage() {
    double percent = 0.0;
    uint64_t total = 0.0;
    CpuParam cur_cpu_param;
    char str1[1024] {0};
    char str2[1024] {0};

    FILE* file = fopen("/proc/stat", "r");
    int ret = fscanf(file, "cpu %llu %llu %llu %llu",
           &cur_cpu_param.user, &cur_cpu_param.nice, &cur_cpu_param.system, &cur_cpu_param.idle);
    fclose(file);
    {
        total = cur_cpu_param.user + cur_cpu_param.nice + cur_cpu_param.system + cur_cpu_param.idle;
        percent = cur_cpu_param.user + cur_cpu_param.nice + cur_cpu_param.system;
        percent = percent/total * 100;
    }
    std::cout << "The percent1: " << percent << std::endl;
/*    printf("f1 = %lld\n", cur_cpu_param.user);
    printf("f2 = %lld\n", cur_cpu_param.nice);
    printf("f3 = %lld\n", cur_cpu_param.system);
    printf("f4 = %lld\n", cur_cpu_param.idle);
    printf("rt = %d\n", ret);*/

    if (cur_cpu_param.user < pre_cpu_param_.user || cur_cpu_param.nice < pre_cpu_param_.nice
        || cur_cpu_param.system < pre_cpu_param_.system || cur_cpu_param.idle < pre_cpu_param_.idle) {
        std::cout << "ERROR @@@@@@@@@@@@@@@@@@\n";
    } else {
        total = (cur_cpu_param.user - pre_cpu_param_.user)
                + (cur_cpu_param.nice - pre_cpu_param_.nice) + (cur_cpu_param.system - pre_cpu_param_.system);
        percent = total;
        total += (cur_cpu_param.idle - pre_cpu_param_.idle);
        percent /= total;
        percent *= 100;
    }
    pre_cpu_param_ = cur_cpu_param;
    std::cout << "The percent2: " << percent << std::endl << std::endl;

    return percent;
}

double getCpuFrequency() {
    std::string cmd = R"(df -P | awk '{if(NR!=1 && NF==6) print $2" "$3" "$6 }')";
    std::ifstream cpuinfo_file(cmd);
    std::string line;
    std::string frequency_str;
    double frequency = 0.0;
    std::cout << cmd << std::endl;

    int i = 0;
    while (std::getline(cpuinfo_file, line)) {
/*        if(line.find("cpu MHz") != std::string::npos) {
            frequency_str = line.substr(line.find(':')+1);
            break;
        }*/
        std::cout << "line" << i << "##" << line << std::endl;
    }

    return frequency;
}

/*
int main() {
    double frequency = getCpuFrequencies();
    std::cout << "CPU frequency: " << frequency << " MHz" << std::endl;

    std::string str = "        1234";
    std::cout << "The str " << std::stod(str) << std::endl;

    std::cout <<"The CPU model name: " << getCpuModelName() << std::endl;

    std::cout << "The cpu ocupy percent: " << getCpuUsage() << std::endl;
    return 0;
}*/

#define ONE_MB (1024 * 1024)
void testSysconf() {
    long num_procs;
    long page_size;
    long num_pages;
    long free_pages;
    long long  mem;
    long long  free_mem;

    num_procs = sysconf (_SC_NPROCESSORS_CONF);
    printf ("CPU 个数为: %ld 个\n", num_procs);

    page_size = sysconf (_SC_PAGESIZE);
    printf ("系统页面的大小为: %ld K\n", page_size / 1024 );

    num_pages = sysconf (_SC_PHYS_PAGES);
    printf ("系统中物理页数个数: %ld 个\n", num_pages);

    free_pages = sysconf (_SC_AVPHYS_PAGES);
    printf ("系统中可用的页面个数为: %ld 个\n", free_pages);

    mem = (long long) ((long long)num_pages * (long long)page_size);
    mem /= ONE_MB;

    free_mem = (long long)free_pages * (long long)page_size;
    free_mem /= ONE_MB;

    printf ("总共有 %lld MB 的物理内存, 空闲的物理内存有: %lld MB\n", mem, free_mem);
}

int testProcessCPUFrequency() {
    FILE *fp;
    long utime, stime, cutime, cstime;
    long dummy;
    fp = fopen("/proc/self/stat", "r");
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }
    if (fscanf(fp, "%*d %*s %*c %ld %ld %ld %ld %*d %*d %*d %*d %*d %ld %*d %*d %*d", &utime, &stime, &cutime, &cstime, &dummy) != 5) {
        fclose(fp);
        return -1;
    }
    fclose(fp);

    // 总的CPU时间 = 用户时间 + 系统时间 + 子进程用户时间 + 子进程系统时间
    long total_time = utime + stime + cutime + cstime;
    printf("total: %ld; utime=%ld, &stime=%ld, &cutime=%ld, &cstime=%ld\n", total_time, utime, stime, cutime, cstime);

    // 读取系统CPU信息
    fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }
    if (fscanf(fp, "cpu %*d %*d %*d %ld", &dummy) != 1) {
        fclose(fp);
        return -1;
    }
    fclose(fp);
    printf("Dummy: %ld\n", dummy);

    // CPU占用率 = 1 - （总的CPU时间 / 系统CPU时间）
    double cpu_usage = ((double)(total_time * 100)) / dummy;
    printf("CPU Usage: %.2f%%\n", cpu_usage);
    return 0;
}

void consumeCPU() {
    int i = 0;
    while(i++ < 1e6) {
        for(int j=0; j<5e3; j++)
            for(int k=0; k<1e6; k++)
                ;
        sleep(2);
    }
};

int main() {
    std::thread th(&consumeCPU);
    th.detach();

    int i = 0;
    while(++i < 1e6) {
        testProcessCPUFrequency();
        sleep(1);
    }
    return 0;
}