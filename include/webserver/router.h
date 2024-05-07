#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include "../httpParse/httpResponse.h"

using Request_Handle = std::function<HttpResponse()>;
class Router {
private:
  int _cfd;
  std::unordered_map<std::string, Request_Handle> _route_table;

public:
  Router() = default;
  inline void set_cfd(int connect_fd) { _cfd = connect_fd; }
  void Get(std::string url, Request_Handle handFunc);
  void Route(std::string url);
};