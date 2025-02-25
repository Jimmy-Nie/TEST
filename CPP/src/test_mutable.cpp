#include <iostream>
#include <string>

class Student {
public:
    Student(const std::string &name) : name_(name) { }

    std::string getName() const {
        access_num_++;
        std::cout << "Access Times: " << access_num_ << std::endl;
        return name_;
    }

    void setAge(uint32_t age) { age_ = age; }
    static uint32_t getAge() { return age_; }
private:
    std::string name_;
    mutable uint32_t access_num_ = 0;   ///Notice mutable
    static uint32_t age_;
};
uint32_t Student::age_ = 18;

int main() {
    Student S1("S1");
    S1.getName();
    S1.getName();
    S1.setAge(30);
    std::cout << "Student::getAge()=" << Student::getAge() << std::endl;

    Student S2("S2");
    std::cout << "S2.getAge()=" << S2.getAge() << std::endl;

    return 0;
}
