#include <string>
#include <chrono>
#include <thread>
#include <iostream>

#include <zmq.hpp>
#include "simple_timer.h"

using namespace std::chrono_literals;

#define USE_IPC

#ifdef USE_TCP
    void zmq_server() {
    // initialize the zmq context with a single IO thread
    zmq::context_t context{1};

    // construct a REP (reply) socket and bind to interface
    zmq::socket_t socket{context, zmq::socket_type::rep};
    socket.bind("tcp://*:5555");

    // prepare some static data for responses
    const std::string data{"World"};

    while(true) {
        zmq::message_t request;

        // receive a request from client
        socket.recv(request, zmq::recv_flags::none);
        std::cout << "Received " << request.to_string() << std::endl;

        // simulate work
        std::this_thread::sleep_for(1s);

        // send the reply to the client
        socket.send(zmq::buffer(data), zmq::send_flags::none);
    }
}

#endif

#ifdef USE_IPC
void zmq_server() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP); // 服务器使用 ZMQ_REP (响应端)
    
    socket.bind("ipc:///tmp/zmq_ipc"); // IPC 绑定到本地路径
    
    while (true) {
        zmq::message_t request;
        socket.recv(request, zmq::recv_flags::none); // 接收消息
        
        std::string received_msg(static_cast<char*>(request.data()), request.size());
        std::cout << "Server received: " << received_msg << std::endl;

        // 处理请求（这里简单地返回 "OK"）
        // std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模拟处理时间
        // std::string reply = "OK";
        // zmq::message_t response(reply.begin(), reply.end());
        // socket.send(response, zmq::send_flags::none);
    }
}
#endif

void zmq_sub() {
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);  // 使用 ZMQ_SUB 模式

    subscriber.connect("ipc:///tmp/zmq_pubsub");  // 连接到发布者的 IPC 地址

    // 设置订阅的主题，这里设置为空字符串，表示接收所有消息
    //std::string fliter = "Test2";
    std::string fliter = "";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, fliter.c_str(), fliter.size());
    std::cout << "Subscriber is subscribed to topic: " << fliter << std::endl;
    
    while (true) {
        zmq::message_t topic_msg;
        zmq::message_t message;
        subscriber.recv(topic_msg, zmq::recv_flags::none);  // 接收消息
        subscriber.recv(message, zmq::recv_flags::none);  // 接收消息

        std::string topic(static_cast<char*>(topic_msg.data()), topic_msg.size());
        std::string received_msg(static_cast<char*>(message.data()), message.size());

        uint64_t now_us = bv::SimpleTimer::get_sys_boot_usec();
        std::string rcv_time_str = received_msg.substr(received_msg.length()-11, std::string::npos);
        uint64_t rcv_time = 0;
        try {
            rcv_time = std::stoul(rcv_time_str);
        } catch(const std::exception& e) {
            std::cout << "The num: " << rcv_time_str << std::endl;
            rcv_time = 0;
            std::cout << e.what();
        }

        std::cout << "Subscriber received: [" << topic << "]: " << "\t" << received_msg << " (" << now_us - rcv_time << ")" << std::endl;
    }
}

int main() 
{
    zmq_sub();
    return 0;
}

