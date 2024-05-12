#pragma once
#include <arpa/inet.h>
#include <functional>
#include <netinet/in.h>
#include <sys/socket.h>


void ConnectCallback(char *buf, int connectfd,
                     const std::function<char *(char *)> &func);

class TcpSocket {
public:
  TcpSocket(int port, bool re_use_addr, int bufsize = 1024);
  TcpSocket(const TcpSocket &server) = delete;
  TcpSocket(TcpSocket &&server) = delete;
  int accept_connect(const std::function<char *(char *)> &func);
  // int httpHandle();
  // int httpHandleTest();

protected:
  sockaddr_in addr;
  socklen_t addrlen;
  int fd;
  int cfd;
  char *buf;
  int buffersize;
};
