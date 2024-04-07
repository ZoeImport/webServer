#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <spdlog/pattern_formatter-inl.h>
#include <spdlog/spdlog.h>
#include <thread>
#include <vector>
#include <future>

class ThreadPool {
protected:
  // 互斥锁
  std::mutex mtx;
  // 任务队列
  std::queue<std::function<void()>> tasks;
  // 状态变量
  std::condition_variable cv;
  // 线程池数量
  std::vector<std::thread> threads;
  // 线程池大小
  int maxSize;
  // 停止信号
  bool stop;

public:
  ThreadPool(int size = 20);
  // ThreadPool()=default;
  // ThreadPool(const ThreadPool&)=default;
  // ThreadPool(ThreadPool&& pool)=default;
  ~ThreadPool();
  template <class F, class... Args>
  auto enQueue(F &&f, Args &&...args)
      -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();
    {
      std::unique_lock<std::mutex> lock(mtx);

      // don't allow enqueueing after stopping the pool
      if (stop)
        throw std::runtime_error("enqueue on stopped ThreadPool");

      tasks.emplace([task]() { (*task)(); });
    }
    cv.notify_one();
    return res;
  }
};