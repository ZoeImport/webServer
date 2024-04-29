#ifndef _TOOL_H_
#define _TOOL_H_

#include <functional>
#include <string>
#include <utility>


template <typename F, typename... Args>
auto wrapFunc(F &&f, Args &&...args) {
    return std::bind(std::forward<F>(f), std::forward<Args>(args)...);
}

std::string readFileToString(std::string path);


#endif