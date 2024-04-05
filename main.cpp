#include <chrono>
#include <iostream>
#include <thread>

#include "threadPool/Thread.h"

int main() {
  ThreadPool threads(10);
  for (auto index = 0; index < 100000; ++index) {

    threads.enQueue([index] {
      std::cout  << index << std::endl;
      // std::this_thread::sleep_for(std::chrono::milliseconds(500));
    });
  }
}