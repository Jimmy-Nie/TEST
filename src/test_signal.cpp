#include <iostream>
#include <vector>
#include <functional>

using namespace std;
#define Debug(fmt, ...) printf("[%s:%s:%d]: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

/**
 * 先实现槽基类,包含两个虚函数对象, 主要为后续调用提供接口
 * @tparam TParm
 */
template<class TParm>
class SlotBase {
public:
    virtual void exec(TParm) = 0;
    virtual ~SlotBase() = default;
};

/**
 * Slot子类，负责实现exec方法，通过exec调用 receiver.func,
 * 同时Slot构造函数负责初始化两个内部变量，将需要关联的 receiver 和 receiver.func 插入槽
 * @tparam TReceiver
 * @tparam TParm
 */
template<class TReceiver, class TParm>
class Slot : public SlotBase<TParm> {
public:
    Slot(TReceiver* receiver, void (TReceiver::*func) (TParm))
        : receiver_(receiver), func_(func) {
        std::cout << "Add Slot\n";
    }

    void exec(TParm parm) override {
        (receiver_->*func_)(parm);
    }

private:
    TReceiver* receiver_ = nullptr;
    void (TReceiver::*func_)(TParm);
};

/**
 * 信号类
 * 私有成员m_pSlotSet，存储槽指针的vector
 * 重载(): 在括号调用参数时，循环调用 slot_vec_ 中存储的槽指针，将参数传递给槽的 exec 方法
 * bind(): 将一个 槽Slot 与 信号Signal 实例关联起来
 * @tparam TParm 
 */
template<class TParm>
class Signal {
public:
    ~Signal() {
        for(auto& it : slot_vec_) {
            delete it;
        }
    }

    template<class TReceiver>
    void bind(TReceiver* p_obj, void(TReceiver::*func)(TParm)) {
        slot_vec_.emplace_back(new Slot<TReceiver, TParm>(p_obj, func));
    }

    void operator()(TParm parm) {
        for(auto& it : slot_vec_)
            it->exec(parm);
    }

private:
    std::vector<SlotBase<TParm>*> slot_vec_;
};

///Connect函数
///为了更方便地将sender中的signal与 槽 和 receiver 关联，可以定义一个宏
#define Connect(sender, signal, receiver, method) ((sender)->signal.bind(receiver, method))

class Receiver1 {
public:
    void self_inc(int a) {
        Debug("Receiver1 self inc num: ++%d=%d", a++, a);
    }
};

class Receiver2 {
public:
    void self_inc(int a) {
        Debug("Receiver2 self inc num: ++%d=%d", a++, a);
    }
};

class Sender {
public:
    void testSignal(int value) {
        value_charged_(value);
    }

public:
    Signal<int> value_charged_;
};

int main() {
    auto *r1 = new Receiver1();
    auto *r2 = new Receiver2();
    auto *sd = new Sender();

    Connect(sd, value_charged_, r1, &Receiver1::self_inc);
    Connect(sd, value_charged_, r2, &Receiver2::self_inc);

    sd->testSignal(10);
    sd->testSignal(20);
}