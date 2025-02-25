#include <string>
#include <iostream>

#include "zmq.hpp"
#include "simple_timer.h"
using namespace bv;

void zmq_pub() {
    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);  // 使用 ZMQ_PUB 模式
    publisher.bind("ipc:///tmp/zmq_pubsub");  // 绑定到 IPC 地址

    std::this_thread::sleep_for(std::chrono::seconds(1));  // 等待订阅者连接

    int msg_count = 0;
    while (true) {
        if(msg_count % 3 == 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(20));  // 每秒发送一条消息

        uint64_t now_us = SimpleTimer::get_sys_boot_usec();
        std::string topic = "Test" + std::to_string(msg_count % 3);
        std::string date = bv::SimpleTimer::get_date_string();
        std::string msg = " Now Time: [ " + date.substr(0, date.length() - 1) + " ] ";

        msg += std::to_string(msg_count) + ":\t" + std::to_string(now_us);

        zmq::message_t topic_msg(topic.begin(), topic.end());
        zmq::message_t message(msg.begin(), msg.end());

        publisher.send(topic_msg, zmq::send_flags::sndmore);  // 发送消息        
        publisher.send(message, zmq::send_flags::none);  // 发送消息

        msg_count++;
        std::cout << "Publisher sent: " << msg << std::endl;
    }
}

int main() {
    zmq_pub();
    return 0;
}

