#include "Thread.h"
#include <functional>
#include <mutex>
#include <queue>

ThreadPool::ThreadPool(int size) : maxSize(size), stop(false) {
  for (auto index = 0; index < maxSize; ++index) {
    threads.emplace_back([this] {
      while (true) {
        std::unique_lock<std::mutex> constructLock(mtx);
        cv.wait(constructLock, [this] { return stop || !this->tasks.empty(); });
        if (stop && tasks.empty()) {
          // spdlog::error("thread pool is not active ...");
          return ;
        }
        auto task = std::function<void()>(std::move(tasks.front()));

        tasks.pop();
        constructLock.unlock();
        task();
      }
    });
    // spdlog::info("thread create");
  }
  // spdlog::info("thread pool init");
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> destructLock;
    stop = true;
  }
  cv.notify_all();
  for (auto &thread : threads) {
    thread.join();
  }
  // spdlog::info("thread pool destruct");
}


