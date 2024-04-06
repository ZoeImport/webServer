#include <chrono>
#include <iostream>
#include <thread>

#include "threadPool/Thread.h"

#include "socket/server.h"

int main() {
  // ThreadPool threads(5);
  // for (auto index = 0; index < 100; ++index) {

  //   threads.enQueue([index](int a) {
  //     std::cout  <<"第"<< index <<"次"<< std::endl;
  //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
  //   },index);
  // }
  Server server(9002);
  server.accept_connect([](char *buf) -> char * {
    return buf;
  });
}