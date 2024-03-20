/**
 * 排序算法：
 * 排序：所谓排序，就是使一串记录，按照其中的某个或某些关键字的大小，递增或递减的排列起来的操作。
 * 稳定性：假定在待排序的记录序列中，存在多个具有相同的关键字的记录，若经过排序，这些记录的相对次序保持不变，即在原序列中，r[i]=r[j]，且r[i]在r[j]之前，而在排序后的序列中，r[i]仍在r[j]之前，则称这种排序算法是稳定的；否则称为不稳定的。
 * 内部排序：数据元素全部放在内存中的排序。
 * 外部排序：数据元素太多不能同时放在内存中，根据排序过程的要求不能在内外存之间移动数据的排序。
 * 详见：https://blog.csdn.net/vpurple_/article/details/126568614
 * https://mp.weixin.qq.com/s?__biz=MzUwOTA4MDM2OQ==&mid=2247490722&idx=1&sn=def1a6f829d83b25e328748b2ee9577a&chksm=f916fafcce6173ead188a3e7ab8d5257cd652754f4d542547450923f59be7a48aa1d7c91e64a&scene=27
 */

#pragma once
#include "timer.h"
#include <map>

#define MAX_SIZE (1024*1024*4)

template<class T>
void print_arr(T* arr, uint32_t size);

template<class T>
void swap(T* arr, uint32_t i, uint32_t j);

///======================================= 选择排序 =======================================================================
/**
 * @brief: 选择排序
 * 时间复杂度：O(n^2)
 * 基本思想： 每一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始位置，直到全部待排序的数据元素排完
 * @tparam T
 */
template<class T>
class SelectionSort {
public:
    static int sort(T *arr, uint32_t size, bool upward = true) {
        if (size > MAX_SIZE) {
            std::cout << "The size=" << size << " > MAX_SIZE=" << MAX_SIZE << std::endl;
            return false;
        } else if (!arr) {
            std::cout << "The array is nullptr!! \n";
            return false;
        }

        for(int i=0; i<size-1; i++) {
            int tmp = i;
            for(int j=i+1; j<size; j++) {
                if( (upward && (arr[tmp] > arr[j]))
                    || (!upward && (arr[tmp] < arr[j])) ) {
                        tmp = j;
                }
            }
            swap(arr, tmp, i);
        }
        return true;
    };
};

/**
 * @brief: 堆排序
 * 基本思想：初始时把要排序的数的序列看作是一棵顺序存储的二叉树，调整它们的存储序，使之成为一个堆，
 * 这时堆的根节点的数最大。然后将根节点与堆的最后一个节点交换。然后对前面(n-1)个数重新调整使之成为堆。依此类推，直到只有两个节点的堆，并对它们作交换，最后得到有n个节点的有序序列。
 * 从算法描述来看，堆排序需要两个过程，一是建立堆，二是堆顶与堆的最后一个元素交换位置。所以堆排序有两个函数组成。一是建堆的渗透函数，二是反复调用渗透函数实现排序的函数。
 * 思路：
 * - 1：建立大根堆–将n个元素组成的无序序列构建一个大根堆，
 * - 2：交换堆元素–交换堆尾元素和堆首元素，使堆尾元素为最大元素；
 * - 3：重建大根堆–将前n-1个元素组成的无序序列调整为大根堆
 * -4: 重复执行步骤二和步骤三，直到整个序列有序。
 * 参考：https://blog.csdn.net/qq_43801020/article/details/108136124
 */
template<class T>
class HeapSort {
public:
    static int sort(T *arr, uint32_t size, bool upward = true) {
        if (size > MAX_SIZE) {
            std::cout << "The size=" << size << " > MAX_SIZE=" << MAX_SIZE << std::endl;
            return false;
        } else if (!arr) {
            std::cout << "The array is nullptr!! \n";
            return false;
        }

        /// 构建大根堆（从最后一个非叶子节点向上）
        for (int i = size / 2 - 1; i >= 0; i--) {
            adjust(arr, size, i);
        }

        /// 调整大根堆
        for (int i = size - 1; i >= 1; i--) {
            swap(arr, 0, i);           /// 将当前最大的放置到数组末尾
            adjust(arr, i, 0);   /// 将未完成排序的部分继续进行堆排序
        }

        return true;
    }
private:
    /// 递归方式构建大根堆(len是arr的长度，index是第一个非叶子节点的下标)
    static void adjust(T *arr, int len, int index) {
        int left = 2 * index + 1;     /// index的左子节点
        int right = 2 * index + 2;    /// index的右子节点

        int max_index = index;
        if (left<len && arr[left] > arr[max_index])
            max_index = left;
        if (right<len && arr[right] > arr[max_index])
            max_index = right;

        if (max_index != index) {
            swap(arr, max_index, index);
            adjust(arr, len, max_index);
        }
    }
};

///======================================= 插入排序 =======================================================================
/**
 * @brief: 插入排序
 * 时间复杂度：O(n^2)
 * 基本思想：基把待排序的数据记录，按其关键码值的大小逐个插入到一个已经排好序的有序序列中，直到所有的数据插入完为止，得到一个新的有序序列 。
 * 当插入第 i(i>=1) 个元素时，前面的 array[0]，array[1]……array[i-1] 已经排好序，此时用 array[i] 的排序码与 array[i-1]，array[i-2] …… 的排序码顺序进行比较，找到插入位置即将 array[i] 插入，原来位置上的元素顺序后
 * @tparam T
 */
template<class T>
class InsertionSort {
public:
    static int sort(T *arr, uint32_t size, bool upward = true) {
        if (size > MAX_SIZE) {
            std::cout << "The size=" << size << " > MAX_SIZE=" << MAX_SIZE << std::endl;
            return false;
        } else if (!arr) {
            std::cout << "The array is nullptr!! \n";
            return false;
        }

        T tmp;
        for(int i=0; i<size-1; i++) {
            for(int j=i+1; j>0; j--) {
                ///如果升序排列，则后面数字小于前面数字时，需要交换一下
                if( (upward && (arr[j] < arr[j-1]))
                    || (!upward && (arr[j] > arr[j-1])) )
                    swap(arr, j, j-1);
                else
                    break;
            }
        }
        return true;
    }
};

/**
 * @brief: 希尔排序
 * 时间复杂度：O(n^1.3)
 * 基本思想： 先选定一个整数，把待排序文件中所有记录分成个组，所有距离为gap的值分在同一组内，并对每一组内的数据进行排序。
 * 然后改变 gap ，重复上述分组和排序的工作。当 gap 到达 1 时，所有记录在统一组内排好序。
 * @tparam T
 */
template<class T>
class ShellSort {
public:
    static int sort(T *arr, uint32_t size, bool upward = true) {
        if (size > MAX_SIZE) {
            std::cout << "The size=" << size << " > MAX_SIZE=" << MAX_SIZE << std::endl;
            return false;
        } else if (!arr) {
            std::cout << "The array is nullptr!! \n";
            return false;
        }

        ///也是采用了 “分而治之” 的思想
        for(uint32_t gap = size/2; gap >= 1; gap/=2) {
            for(uint32_t i=gap; i<size; i++) {
                for(int j=i; j>=gap; j-=gap) {
                    if( (upward && (arr[j] < arr[j-1]))
                        || (!upward && (arr[j] > arr[j-1])) )
                        swap(arr, j, j-1);
                }
            }
        }
        return true;
    }
};

///======================================= 交换排序 =======================================================================
/**
 * @brief: 冒泡排序
 * 时间复杂度为 O(n^2)
 * @tparam T
 */
template<class T>
class BubbleSort {
public:
    static int sort(T* arr, uint32_t size, bool upward = true) {
        if(size > MAX_SIZE) {
            std::cout << "The size=" << size << " > MAX_SIZE=" << MAX_SIZE << std::endl;
            return false;
        } else if (!arr) {
            std::cout << "The array is nullptr!! \n";
            return false;
        }

        int i = 0;
        bool swap_flag = true;  ///主要适用于检测本次排序有没有数据交换，如果没有，则表示已经排序完成了，后面的步骤没必要进行下去了
        while(swap_flag && (i < size - 1)) {
            swap_flag = false;
            for(int j = 1; j < size - i; j++) {
                if((upward && (arr[j-1] > arr[j]))
                   || !upward && (arr[j-1] < arr[j])) {
                    swap(arr, j-1, j);
                    swap_flag = true;
                }
            }
            i++;
        }
        return true;
    }
};

/**
 * @brief: 快速排序
 * 基本思想：
 * - 从数组中选择一个元素，把这个元素称之为中轴元素吧，然后把数组中所有小于中轴元素的元素放在其左边，所有大于或等于中轴元素的元素放在其右边，
 * - 显然，此时中轴元素所处的位置的是有序的。也就是说，我们无需再移动中轴元素的位置。
 * - 从中轴元素那里开始把大的数组切割成两个小的数组(两个数组都不包含中轴元素)，接着通过递归的方式，
 * - 让中轴元素左边的数组和右边的数组也重复同样的操作，直到数组的大小为1，此时每个元素都处于有序的位置。
 *
 * 算法步骤：
 * 1、选取第一个数为基准
 * 2、将比基准小的数交换到前面，比基准大的数交换到后面
 * 3、对左右区间重复第二步，直到各区间只有一个数
 * @tparam T
 */
template<class T>
class QuickSort {
public:
    static int sort(T *arr, uint32_t size, bool upward = true) {
        if (size > MAX_SIZE) {
            std::cout << "The size=" << size << " > MAX_SIZE=" << MAX_SIZE << std::endl;
            return false;
        } else if (!arr) {
            std::cout << "The array is nullptr!! \n";
            return false;
        }

        quick_sort(arr, 0, size-1, upward);
    }

private:
    static void quick_sort(T* arr, int start, int end, bool upward) {
        if(start >= end || !arr)
            return;

        ///反馈分区下标
        int mid = partition(arr, start, end, upward);

        ///递归调用
        quick_sort(arr, start, mid-1, upward);
        quick_sort(arr, mid+1, end, upward);
    }

    static int partition(T* arr, int start, int end, bool upward) {
        /// 选择数组的第一个元素作为枢纽值
        int left = start;
        int right = end;
        int pivot = arr[start]; ///基准元素

        /// 遍历数组，将小于枢纽值的元素放到左边，大于枢纽值的元素放到右边
        while(left < right) {
            ///从右向左开始找一个 小于等于 pivot的数值
            while ((left < right) &&
                    ((upward && arr[right] > pivot) || (!upward && arr[right] < pivot)) ) {
                right--;
            }
            ///交换两个元素的位置
            if(left < right) {
                swap(arr, left, right);
                left++;
            }

            ///从左向右开始找一个 大于 pivot的数值
            while ((left < right) &&
                   ((upward && arr[left] < pivot) || (!upward && arr[left] > pivot)) ) {
                left++;
            }
            ///交换两个元素的位置
            if(left < right) {
                swap(arr, left, right);
                right--;
            }
        }

        return left;
    }
};

///======================================= 计数排序 ===========================================================
/**
 * @brief: 计数排序
 * 将输入的数据值转化为键存储在额外开辟的数组空间中。作为一种线性时间复杂度的排序，计数排序要求输入的数据必须是有确定范围的整数。
 * @tparam T
 */
template<class T>
class CountSort {
public:
    static int sort(T *arr, uint32_t size, bool upward = true) {
        if (size > MAX_SIZE) {
            std::cout << "The size=" << size << " > MAX_SIZE=" << MAX_SIZE << std::endl;
            return false;
        } else if (!arr) {
            std::cout << "The array is nullptr!! \n";
            return false;
        }

        ///创建一个关联容器，将数据存到关联容器中
        std::map<T, uint32_t> tmp_map;
        for(int i=0; i<size; i++) {
            if(tmp_map.count(arr[i]) > 0)
                tmp_map[arr[i]]++;
            else
                tmp_map[arr[i]] = 1;
        }

        ///将容器中的数据重新按序放到原数组中
        int index = 0;
        //for(const auto& [key, value] : tmp_map) {
        for(auto it = tmp_map.begin(); it != tmp_map.end(); it++)
            for(int i=0; i<it->second; i++)
                arr[index++] = it->first;
    }
};