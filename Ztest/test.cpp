#include "test2.h"
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <ratio>
#include <thread>
#include <vector>

class ClassName {
public:
  ClassName() = default;
  ClassName(int):stop(false) {
    for (auto index = 0; index < 2; ++index) {
      {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return false; });
      }
      if (!stop) {
        return;
      }
      std::cout << "constructor done" << std::endl;
    }
  }
  bool stop;
  std::vector<int> nums;
  std::mutex mtx;
  std::condition_variable cv;
};

int main() {
  //   std::unique_lock<std::mutex> lock(mtx);
  //   cv.wait(lock, [] {
  //     std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  //     return false;
  //   });
  //  std::cout<<"running"<<std::endl;
  // ClassName temp(1);
  // temp.nums.push_back(20);
  // create thread pool with 4 worker threads
  ThreadPool pool(4);

  std::function<void()> func;

  // auto result = pool.enqueue([](int answer) { return answer; }, 42);

  // std::cout << result.get() << std::endl;
}