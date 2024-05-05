#include "webserver.h"
#include <asm-generic/socket.h>
#include <iostream>
#include <iterator>
#include <netinet/in.h>
#include <ostream>
#include <sys/socket.h>
#include <unistd.h>

Webserver::Webserver(int port) {
  _socket.fd = socket(AF_INET, SOCK_STREAM, 0);
  if (_socket.fd == -1) {
    std::cerr << "socket error" << std::endl;
    return;
  }
  _socket.addr.sin_family = AF_INET;
  _socket.addr.sin_port = htons(port);
  _socket.addr.sin_addr.s_addr = INADDR_ANY;
  int port_reuse = 1;
  setsockopt(_socket.fd, SOL_SOCKET, SO_REUSEADDR, &port_reuse,
             sizeof(port_reuse));
  auto ret = bind(_socket.fd, (sockaddr *)&_socket.addr, sizeof(_socket.addr));
  if (ret == -1) {
    std::cerr << "bind error" << std::endl;
    return;
  }
  socklen_t caddr_len = sizeof(_socket);
  listen(_socket.fd, 128);
  _socket.cfd = accept(_socket.fd, (sockaddr *)&_socket, &caddr_len);
  if (_socket.cfd == -1) {
    std::cerr << "accept error" << std::endl;
    return;
  }
  while (true) {
    char buffer[1024];
    auto len = recv(_socket.cfd, buffer, sizeof(buffer), 0);
    if (len > 0) {
      std::cout << "buffer:" << buffer << std::endl;
      send(_socket.cfd, buffer, sizeof(buffer), 0);
    } else if (len == 0) {
      std::cerr << "len == 0" << std::endl;
      break;
    } else {
      std::cerr << "recv error" << std::endl;
      break;
    }
  }
  close(_socket.cfd);
  close(_socket.fd);
}
