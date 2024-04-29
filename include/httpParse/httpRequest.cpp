#include "httpRequest.h"
#include <boost/test/unit_test_suite.hpp>
#include <fstream>
#include <iostream>

HttpRequest::HttpRequest(const std::string &requestStr) {
  msg = requestStr;
  std::stringstream ss(requestStr);
  std::string line;

  // 解析请求行
  std::getline(ss, line);
  std::stringstream lineStream(line);
  // 默认按照空格分隔
  lineStream >> method >> path >> version;

  // 解析请求头
  while (std::getline(ss, line) && !line.empty()) {
    std::stringstream headerStream(line);
    std::string headerName, headerValue;
    std::getline(headerStream, headerName, ':');
    std::getline(headerStream, headerValue);
    headers.emplace_back(headerName, headerValue);
  }

  // 解析请求体（如果有的话）
  if (ss.rdbuf()->in_avail() > 0) {
    std::stringstream bodyStream;
    bodyStream << ss.rdbuf();
    body = bodyStream.str();
  }
}
std::string HttpRequest::url_prefix = "../resource";


void httpHandle(HttpRequest &req) {
  std::string url;
  if (req.getMethod() == "GET") {
    url = HttpRequest::getUrlPrefix() + req.getPath();
    std::cout << url << std::endl;
    std::fstream read(url + "index.html");
    
  }
}
