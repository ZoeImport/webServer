#include "Thread.h"
#include "spdlog/spdlog.h"
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
          spdlog::error("thread pool is not active ...");
          return ;
        }
        auto task = std::function<void()>(std::move(tasks.front()));

        tasks.pop();
        constructLock.unlock();
        task();
      }
    });
  }
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
}


// template <typename F, typename... Args>
// auto ThreadPool::enQueue(F &&f, Args &&...args) -> decltype(f(args...)){
//   auto func = std::bind(f, args...);
//   {
//     std::unique_lock<std::mutex> lock(mtx);
//     tasks.emplace(func);
//   }
// }
