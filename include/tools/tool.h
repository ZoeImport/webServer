#ifndef _TOOL_H_
#define _TOOL_H_

#include <functional>
#include <string>
#include <type_traits>
#include <utility>

// func wrap
template <typename F, typename... Args> auto wrapFunc(F &&f, Args &&...args) {
  return std::bind(std::forward<F>(f), std::forward<Args>(args)...);
}

// read file(at path) to string
std::string readFileToString(std::string path);

// remove blur messgae from  content-type of Requestbody to make it correct
std::string eraseBlur(const std::string &content_type, const std::string &body);

namespace tool {

template <typename T> std::string to_string(const T &t) {
  if constexpr (std::is_convertible_v<T, std::string>) {
    return t;
  } else {
    return std::to_string(t);
  }
}
template <typename... Args>
std::string addString(char sepeerator, Args... args) {
  // if ((std::is_same_v<string, Args> && ...)) {
  std::string res;
  std::vector<std::string> arr{args...};
  for (auto &x : arr) {
    res += (x + sepeerator);
  }
  if (res.back() == sepeerator) {
    res.pop_back();
    return res;
  } else {
    throw std::exception{};
  }
  // }
}
} // namespace tool

#endif