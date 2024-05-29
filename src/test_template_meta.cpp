#include <iostream>
#include <type_traits>
//

class A{};
enum E: int {};

// 改写：如何反推出模板参数的类型名字 ???
template<class  T>
void f(T i){
    if(!std::is_integral<T>::value){
        printf("%f Integral required.\n", i);
    }
}


int main()
{
    std::cout << std::boolalpha;
    std::cout << std::is_integral<A>::value << "\n";
    std::cout << std::is_integral<E>::value << "\n";
    std::cout << std::is_integral<float>::value << '\n';
    std::cout << std::is_integral<int>::value << '\n';
    std::cout << std::is_integral<bool>::value << '\n';

    f(123);
    f(1.23);
    f('a');
}
