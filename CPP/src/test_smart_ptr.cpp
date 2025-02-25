/**
 * @brief: 测试智能指针
 */
#include <iostream>
#include <string>
#include <memory>

class CountBase {
public:
    void inc() {++count_;}
    void dec() {--count_;}
    int get() {return count_;}

private:
    int count_ = 0;
};

template<class T>
class SmartPointer {
public:
    SmartPointer() {
        std::cout << "construct null!\n";
        p_count_ = new CountBase();
        ptr_ = new T();
    }

    explicit SmartPointer(T* ptr) : ptr_(ptr) {
        std::cout << "Copy construct!\n";
        if(ptr_) {
            p_count_ = new CountBase();
            p_count_->inc();
        }
    }

    SmartPointer(const SmartPointer<T>& rhs) {
        std::cout << "Copy construct!\n";
        if (&rhs != this) {
            ptr_ = rhs.ptr_;
            p_count_ = rhs.p_count_;
            p_count_->inc();
        }
    }

    ~SmartPointer() {
        std::cout << "smart pointer deleted!\n";
        if(ptr_) {
            p_count_->dec();
            if(p_count_->get() <= 0) {
                delete ptr_;
                ptr_ = nullptr;

                delete p_count_;
                p_count_ = nullptr;
            }
        }
    }

    SmartPointer<T>& operator=(const SmartPointer<T>& rhs) {
        std::cout << "Assign construct!\n";
        if(&rhs != this) {
            if(p_count_->get() != 0 && ptr_) {
                delete ptr_;
                p_count_->dec();
                delete p_count_;
            }
            ptr_ = rhs.ptr_;
            p_count_ = rhs.p_count_;
            p_count_->inc();
        }
        return *this;
    }

    T& operator*() {
        if(!ptr_) {
            std::cout << "The pointer=nullptr\n";
        }
        return *ptr_;
    }

    T* get() { return ptr_ ? ptr_ : nullptr; }

    int use_count() {
        if(p_count_)
            return p_count_->get();
        else
            return 0;
    }

public:
    T* ptr_ = nullptr;
    CountBase* p_count_ = nullptr;
};


int main() {
    SmartPointer<int> ip1(new int(10));
    SmartPointer<int> ip2 = ip1;
    SmartPointer<int> ip3;
    ip3 = ip2;
    SmartPointer<int> ip4(ip1);

    std::cout << "*ip1=" << *ip1 << ", ip1.get()=" << *(ip1.get()) << ", ip1.use_count() = " << ip1.use_count() << std::endl;
    std::cout << "*ip2=" << *ip2 << ", ip2.get()=" << *(ip2.get()) << ", ip2.use_count() = " << ip2.use_count() << std::endl;
    std::cout << "*ip3=" << *ip3 << ", ip3.get()=" << *(ip3.get()) << ", ip3.use_count() = " << ip3.use_count() << std::endl;
    std::cout << std::endl;

    std::shared_ptr<int> p1 = std::make_shared<int>(111);
    std::shared_ptr<int> p2 = p1;
    std::shared_ptr<int> p3;
    p3 = p1;

    std::cout << "*p1=" << *p1 << ", p1.get()=" << *(p1.get()) << ", p1.use_count() = " << p1.use_count() << std::endl;
    std::cout << "*p2=" << *p2 << ", p2.get()=" << *(p2.get()) << ", p2.use_count() = " << p2.use_count() << std::endl;
    std::cout << "*p3=" << *p3 << ", p3.get()=" << *(p3.get()) << ", p3.use_count() = " << p3.use_count() << std::endl;

    std::weak_ptr<int> p4(p3);
    std::cout << "p3.use_count() = " << p3.use_count() << std::endl;
    std::cout << "p4.use_count() = " << p4.use_count() << std::endl;

    return 0;
}