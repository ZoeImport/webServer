#include <chrono>
#include <iostream>
#include <thread>
#include "spdlog/spdlog.h"
#include "include/threadPool/Thread.h"
#include "include/TcpSocket/TcpSocket.h"
#include "include/epoll/Epoll.h"

#define THREAD_POOL_ACTIVE 1

int main() {
  // ThreadPool threads(5);
  // for (auto index = 0; index < 100; ++index) {

  //   threads.enQueue([index](int a) {
  //     std::cout  <<"第"<< index <<"次"<< std::endl;
  //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
  //   },index);
  // }
  ThreadPool thread;
  // Epoll server(9002, true,ThreadPool()); // 设置端口复用
  Epoll server(9002, true,true); // 设置端口复用
  
  spdlog::info("service begin in port 9002");
  server.startWithThreads([](char *buf) -> char * { return buf; });
}