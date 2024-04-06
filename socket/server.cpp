#include "server.h"
#include <arpa/inet.h>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <utility>


void server_func(char *buf, int connectfd,const std::function<char*(char*)> &func) {
  // auto func_ptr = std::make_unique(
      // std::bind(std::forward<F>(f), std::forward<Args>(args)...));
  auto date =func(buf);
  auto ret = send(connectfd, date, sizeof(buf), 0);
}




Server::Server(int port) {
  this->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    std::cerr << "socket error" << std::endl;
    // throw std::exception();
    return;
  }
  this->addr.sin_family = AF_INET;
  this->addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
  addrlen = sizeof(addr);
  auto ret = bind(fd, (sockaddr *)&addr, addrlen);
  if (ret == -1) {
    std::cerr << "bind error" << std::endl;
    return;
  }
  listen(fd, 128); // mark the max connect size
}

int Server::accept_connect(const std::function<char*(char*)> &func) {
  std::cout<<"waiting connection"<<std::endl;
  sockaddr_in caddr;
  this->cfd = accept(fd, (struct sockaddr *)&caddr, &addrlen);
  if (cfd == -1) {
    std::cerr << "accept error" << std::endl;
    return -1;
  }
  char ip[32];
  std::cout << "client ip: "
            << inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip, sizeof(ip)) << ","
            << "port: " << ntohs(caddr.sin_port) << std::endl;
  while (true) {
    char buffer[1024];
    auto len = recv(cfd, buffer, sizeof(buffer), 0);
    if (len > 0) {
      server_func(buffer, cfd,func);

    } else if (len == 0) {
      std::cout << "client close" << std::endl;
      break;
    } else {
      std::cerr << "recv error" << std::endl;
      break;
    }
  }
  close(fd);
  close(cfd);
  return 0;
}
