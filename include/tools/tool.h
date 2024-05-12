#ifndef _TOOL_H_
#define _TOOL_H_

#include <functional>
#include <string>
#include <utility>

// func wrap 
template <typename F, typename... Args>
auto wrapFunc(F &&f, Args &&...args) {
    return std::bind(std::forward<F>(f), std::forward<Args>(args)...);
}

// read file(at path) to string 
std::string readFileToString(std::string path);

// remove blur messgae from  content-type of Requestbody to make it correct
std::string eraseBlur(const std::string &content_type,const std::string &body);


#endif