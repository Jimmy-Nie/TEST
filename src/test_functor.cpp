#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

template <class T>
class Less {
public:
    bool operator()(T a, T b) {
        return a < b;
    }
};

template <class T>
class Greater {
public:
    bool operator()(T a, T b) {
        return a > b;
    }
};

int main() {
    std::vector<int> vec {5, 2, 1, 11, 7, 8, 4};

    auto prt = [&]() {
        for(auto& it : vec)
            std::cout << it << ", ";
        std::cout << "\n";
    };
    prt();


    std::sort(vec.begin(), vec.end(), Greater<int>());
    prt();

    std::sort(vec.begin(), vec.end(), Less<int>());
    prt();

    std::function<int(int, int)> myPlus = std::plus<int>();
    std::cout << myPlus(11, 22) << std::endl;

    return 0;
}