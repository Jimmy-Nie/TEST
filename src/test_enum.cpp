#include <iostream>
#include "enum.h"
#include <unistd.h>

BETTER_ENUM(ColorType, uint8_t,
    Red,
    Blue,
    Yellow
);

struct T1 {
    int age1;
    int num1;
};

struct T2 {
    int age2;
    int num2;
};

template <class KeyType, class ValueType>
ValueType getValue(KeyType key) {
    T1 t1 {10,10};
    T2 t2 {20, 20};

    if(key == 1)
        return t1;
    // else
    //     return t2;
}

void testTemplate() {
    auto t = getValue<int, T1>(1);
    std::cout << t.age1 << std::endl;

    // t = getValue<int, T2>(2);
    // std::cout << t.age2 << std::endl;
}

int main() {
    ColorType c = ColorType::Red;
    std::cout << "The color: " << c._to_string() << std::endl; //<< Red._to_string() << std::endl;
    std::cout << "The color: " << ColorType::_name() << std::endl;

    testTemplate();
    return 0;
}
