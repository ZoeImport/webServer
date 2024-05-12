#pragma once

#include "../httpParse/httpResponse.h"
#include "../httpParse/httpRequest.h"
#include <functional>
#include <string>
#include <unordered_map>

using Request_Handle = std::function<HttpResponse(const HttpRequest &request)>;
class Router {
private:
  int _cfd;
  std::unordered_map<std::string, Request_Handle> _route_table;
  std::unordered_map<std::string, std::unordered_map<std::string,Request_Handle>> _table; 

public:
  Router() = default;
  inline void set_cfd(int connect_fd) { _cfd = connect_fd; }
  void Get(std::string url, Request_Handle handFunc);
  void Post(std::string url, Request_Handle handFunc);
  // void Route(std::string url);
  void Route(std::string method,std::string url);
  void Route(const HttpRequest &request);
};