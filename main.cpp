#include <chrono>
#include <iostream>
#include <thread>
#include "spdlog/spdlog.h"
#include "threadPool/Thread.h"
#include "TcpSocket/TcpSocket.h"
#include "TcpSocket/epoll/Epoll.h"

int main() {
  // ThreadPool threads(5);
  // for (auto index = 0; index < 100; ++index) {

  //   threads.enQueue([index](int a) {
  //     std::cout  <<"第"<< index <<"次"<< std::endl;
  //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
  //   },index);
  // }
  Epoll server(9002, true); // 设置端口复用
  
  spdlog::info("service begin in port 9002");
  server.start([](char *buf) -> char * { return buf; });
}