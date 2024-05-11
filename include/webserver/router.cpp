#include "router.h"
#include <sys/socket.h>

void Router::Get(std::string url, Request_Handle handleFunc) {
  _route_table[url] = handleFunc;
}

void Router::Post(std::string url, Request_Handle handleFunc) {
  _route_table[url] = handleFunc;
}



void Router::Route(std::string url) {
  if (_route_table.count(url)) {

    auto handleFunc = _route_table[url];

    auto response = handleFunc();

    response.set_status_code(200);

    auto debug_temp = response.to_string();

    send(this->_cfd, debug_temp.c_str(), debug_temp.size(), 0);
  } else {

    HttpResponse page_404("text_html", "404.html");

    page_404.set_status_code(404);

    auto temp = page_404.to_string();

    // std::string response =
    //     "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";

    send(this->_cfd, temp.c_str(), temp.size(), 0);
  }
}