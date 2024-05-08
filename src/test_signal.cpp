#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <mutex>

#define Debug(fmt, ...) printf("[%s:%s:%d]: " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

/**
 * 先实现槽基类,包含两个虚函数对象, 主要为后续调用提供接口
 * @tparam TParm
 */
class SlotBase {
public:
    SlotBase() = default;
    SlotBase(const SlotBase&) = delete;
    SlotBase& operator=(const SlotBase&) = delete;

    virtual ~SlotBase() = default;
};

template<class SlotType>
class SignalBase {
public:
    SignalBase() = default;
    virtual ~SignalBase() = default;

public:
    std::mutex mutex_;
    std::vector<std::weak_ptr<SlotType>> slots_;
};

/**
 * Slot子类，负责实现exec方法，通过exec调用 receiver.func,
 * 同时Slot构造函数负责初始化两个内部变量，将需要关联的 receiver 和 receiver.func 插入槽
 * @tparam TReceiver 目标接受者
 * @tparam Function 目标接受者需要执行的程序
 */
template<class Function>
class Slot : public SlotBase {
public:
    Slot(const std::weak_ptr<SignalBase<SlotBase>>& signal, std::function<Function> func)
        : signal_(signal), func_(func) {
        std::cout << "Add Slot\n";
    }

    ~Slot() {
        std::shared_ptr<SignalBase<SlotBase>> sig = signal_.lock();
        if(sig)
            return;
        {
            std::unique_lock<std::mutex> lck(sig->mutex_);
            for(auto it=sig->slots_.begin(); it!=sig->slots_.end(); ++it) {
                if(it->expired() || it->lock().get() == this)
                    sig->slots_.erase(std::move(sig->slots_.begin(), sig->slots_.end(), it), sig->slots_.end());
            }
        }
    }

private:
    std::function<Function> func_;
    std::weak_ptr<SignalBase<SlotBase>> signal_;
};

/**
 * 信号类
 * 私有成员m_pSlotSet，存储槽指针的vector
 * 重载(): 在括号调用参数时，循环调用 slot_vec_ 中存储的槽指针，将参数传递给槽的 exec 方法
 * bind(): 将一个 槽Slot 与 信号Signal 实例关联起来
 * @tparam TParm 
 */
template<class Function>
class Signal {
public:
    Signal() : signal_(std::make_shared<SignalBase<Slot<Function>>>()) {}



    template<class TReceiver, class Function>
    void connect(std::function<Function> func) {
        slot_vec_.emplace_back( std::make_shared<Slot<TReceiver, Function>(receiver, func) );
    }

    template <class... Args>
    void operator()(Args && ...args) {
        for(auto& it : slot_vec_)
            it->exec(parm);
    }

private:
    std::shared_ptr<SignalBase<Slot<Function>>> signal_;
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