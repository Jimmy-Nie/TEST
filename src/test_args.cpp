#include <iostream>

using namespace std;

void printList() { //递归终止控制函数
    std::cout << std::endl;
}

template<class T, class ...Args>
void printList(const T& val, Args... args) {
    std::cout << "<ListVal, 参数包中参数个数> : " << "<" << val << " , " << sizeof...(args) << ">" << std::endl;
    printList(args...);
}

int main() {
    std::string s = "zhang";
    printList(30, 12.15, s, 'b', 100);

    return 0;
}