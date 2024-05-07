#include "httpRequest.h"
#include <boost/test/unit_test_suite.hpp>
#include <cstddef>
#include <fstream>
#include <iostream>
#include "../tools/tool.h"
#include "httpResponse.h"

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

// std::string httpResponse = "HTTP/1.1 200 OK\r\n"
//                            "Content-Type: text/html; charset=UTF-8\r\n"
//                            "\r\n"
//                            "<!DOCTYPE html>\n"
//                            "<html>\n"
//                            "<head>\n"
//                            "<title>HTML Response</title>\n"
//                            "</head>\n"
//                            "<body>\n"
//                            "<h1>Hello, this is a simple HTML response!</h1>\n"
//                            "</body>\n"
//                            "</html>\n";
// std::string  httpHandle(HttpRequest &req) {
//   std::string url;
//   if (req.getMethod() == "GET") {
    
//     url = HttpRequest::getUrlPrefix() + req.getPath();
//     //test
//     url += "index.html";
//     auto pagestream=readFileToString(url);
//     HttpResponse reponse(pagestream);
//     reponse.setVersion("HTTP/1.1");
//     reponse.setStatusCode(200);
//     reponse.setMsg("ok");
//     auto res = reponse.toString();
//     return res;
//   }
//   return NULL;
// }
