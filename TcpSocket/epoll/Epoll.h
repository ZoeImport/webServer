#pragma once
#include "../TcpSocket.h"
#include <arpa/inet.h>
#include <functional>
#include <memory>
#include <spdlog/spdlog.h>
#include <sys/epoll.h>
#include <vector>

class Epoll : protected TcpSocket {
public:
  Epoll(int port, bool re_use_addr,int bufsize=1024,int epoll_events_size=1024) : TcpSocket(port, re_use_addr,bufsize) {
    this->epfd = epoll_create(100);
    spdlog::info("epoll module creat ");
    if (epfd == -1) {
      spdlog::error("epoll create error");
      return;
    }
    this->ev.events = EPOLLIN; // read event for listen fd
    this->ev.data.fd = fd;
    epoll_ctl(this->epfd, EPOLLIN, this->fd, &this->ev);
    this->evs = new epoll_event[epoll_events_size];
    this->epoll_events_size=epoll_events_size;
  }
  int start(const std::function<char *(char *)> &func);

private:
  int epfd;
  epoll_event ev;
  epoll_event *evs;
  int epoll_events_size;
};