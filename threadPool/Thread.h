#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
private:
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
  ThreadPool(int size);
  ~ThreadPool();
  template <typename F, typename... Args>
  auto enQueue(F &&f, Args &&...args) -> decltype(f(args...)) {
    auto func = std::bind(f, args...);
    {
      std::unique_lock<std::mutex> lock(mtx);
      tasks.emplace(func);
    }
  }
};