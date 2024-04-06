#include "spdlog/spdlog.h"
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
  ClassName(int) : stop(false) {
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
  // ThreadPool pool(4);

  // std::function<void()> func;

  // auto result = pool.enqueue([](int answer) { return answer; }, 42);

  // std::cout << result.get() << std::endl;

  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);

  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical(
      "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:<30}", "left aligned");

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  spdlog::debug("This message should be displayed..");

  // change log pattern
  spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

  // Compile time log levels
  // Note that this does not change the current log level, it will only
  // remove (depending on SPDLOG_ACTIVE_LEVEL) the call on the release code.
  SPDLOG_TRACE("Some trace message with param {}", 42);
  SPDLOG_DEBUG("Some debug message");
}
