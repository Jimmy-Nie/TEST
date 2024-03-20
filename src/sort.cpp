#include <iostream>
#include <random>
#include <vector>
#include <functional>   // std::greater
#include <algorithm>    // std::sort
#include <cstdlib>
#include <chrono>

#include "sort.h"

using namespace std;

const bool debug = false;    ///是否打印排序号的数据

#define arr_size 1024 * 16
uint32_t g_array[arr_size] = {0};

template<class T>
void swap(T* arr, uint32_t i, uint32_t j) {
    T tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
};

template<class T>
void print_arr(T* arr, uint32_t size) {
    if(size > MAX_SIZE) {
        std::cout << "The size=" << size << " > MAX_SIZE=" << MAX_SIZE << std::endl;
        return;
    }

    ///打印信息
    for(int i = 0; i < size; i++) {
        if(i%20 == 0)
            std::cout << std::endl;
        std::cout << arr[i] << "  ";
    }

    std::cout << "\n==================================================== \n";
}

int generate_arr(uint32_t* arr, uint32_t size) {
    if(size > MAX_SIZE) {
        std::cout << "The size=" << size << " > MAX_SIZE=" << MAX_SIZE << std::endl;
        return false;
    }

    for(int i = 0; i < size; i++) {
        arr[i] = random() % size;
    }

    if(debug) {
        std::cout << "\nThe generated data (size = " << size << ")";
        print_arr(arr, size);
    }

    return true;
}


int main() {
    Timer timer;
    uint64_t elapsed_us = 0;
    generate_arr(g_array, arr_size);

    ///冒牌排序法耗时
    timer.start();
    BubbleSort<uint32_t>::sort(g_array, arr_size, true);
    elapsed_us = timer.elapsed_usec();

    if(debug) {
        std::cout << "\nThe Bubble sort array data:";
        print_arr<uint32_t>(g_array, arr_size);
    }
    std::cout << "The BubbleSort data size=" << arr_size << " cost " << elapsed_us << " us\n";

    ///快速排序耗时
    generate_arr(g_array, arr_size);

    timer.start();
    QuickSort<uint32_t>::sort(g_array, arr_size, true);
    elapsed_us = timer.elapsed_usec();

    if(debug) {
        std::cout << "\nThe QuickSort array data:";
        print_arr<uint32_t>(g_array, arr_size);
    }
    std::cout << "The QuickSort data size=" << arr_size << " cost " << elapsed_us << " us\n";

    ///选择排序法耗时
    generate_arr(g_array, arr_size);

    timer.start();
    SelectionSort<uint32_t>::sort(g_array, arr_size, false);
    elapsed_us = timer.elapsed_usec();

    if(debug) {
        std::cout << "\nThe Selection sort array data:";
        print_arr<uint32_t>(g_array, arr_size);
    }
    std::cout << "The SelectionSort data size=" << arr_size << " cost " << elapsed_us << " us\n";

    ///堆排序
    generate_arr(g_array, arr_size);

    timer.start();
    HeapSort<uint32_t>::sort(g_array, arr_size, true);
    elapsed_us = timer.elapsed_usec();

    if(debug) {
        std::cout << "\nThe HeapSort array data:";
        print_arr<uint32_t>(g_array, arr_size);
    }
    std::cout << "The HeapSort data size=" << arr_size << " cost " << elapsed_us << " us\n";

    ///插入排序
    generate_arr(g_array, arr_size);

    timer.start();
    InsertionSort<uint32_t>::sort(g_array, arr_size, true);
    elapsed_us = timer.elapsed_usec();

    if(debug) {
        std::cout << "\nThe Insertion sort array data:";
        print_arr<uint32_t>(g_array, arr_size);
    }
    std::cout << "The InsertionSort data size=" << arr_size << " cost " << elapsed_us << " us\n";

    ///希尔排序
    generate_arr(g_array, arr_size);
    timer.start();
    ShellSort<uint32_t>::sort(g_array, arr_size, true);
    elapsed_us = timer.elapsed_usec();

    if(debug) {
        std::cout << "\nThe ShellSort array data:";
        print_arr<uint32_t>(g_array, arr_size);
    }
    std::cout << "The ShellSort data size=" << arr_size << " cost " << elapsed_us << " us\n";

    ///计算排序
    generate_arr(g_array, arr_size);
    timer.start();
    CountSort<uint32_t>::sort(g_array, arr_size, true);
    elapsed_us = timer.elapsed_usec();

    if(debug) {
        std::cout << "\nThe CountSort array data:";
        print_arr<uint32_t>(g_array, arr_size);
    }
    std::cout << "The CountSort data size=" << arr_size << " cost " << elapsed_us << " us\n";
    ///桶排序耗时

    return 0;
}