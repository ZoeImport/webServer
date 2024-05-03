#include "router.h"
void Router::Get(const std::string &url, RequestHandler handler) {
  routes[url] = handler;
}

void Router::Route(const std::string &url, int clientSocket) {
  if (routes.count(url) > 0) {
    auto handler = routes[url];
    handler(clientSocket);
  } else {
    std::string response =
        "HTTP/1.1 404 Not Found\r\nContent-Length: 13\r\n\r\n404 Not Found";
    send(clientSocket, response.c_str(), response.size(), 0);
  }
}


