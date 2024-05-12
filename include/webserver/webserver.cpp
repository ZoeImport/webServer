#include "webserver.h"
#include "../httpParse/httpRequest.h"
#include "router.h"
#include <asm-generic/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <ostream>
#include <sys/socket.h>
#include <unistd.h>

int Webserver::_connect_count = 0;

Webserver::Webserver(int port, Router router) {

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

  while (true) {
    _socket.cfd = accept(_socket.fd, (sockaddr *)&_socket, &caddr_len);
    if (_socket.cfd == -1) {
      std::cerr << "accept error" << std::endl;
      return;
    }

    // std::cout << "begin to handle" << std::endl;
    char buffer[1024];
    auto len = recv(_socket.cfd, buffer, sizeof(buffer), 0);

    HttpRequest request((std::string(buffer)));

    if (len > 0) {
      router.set_cfd(_socket.cfd);

      std::cout << "==========" << " the " << (++_connect_count) << "th message "
                << "===========" << std::endl;
      std::cout << "buffer:" << std::endl << buffer << std::endl;

      router.Route(request.getPath());
      close(_socket.cfd);
    } else if (len == 0) {
      std::cerr << "len == 0" << std::endl;
      continue;

    } else {
      std::cerr << "recv error" << std::endl;
      break;
    }
  }

  close(_socket.fd);
}
