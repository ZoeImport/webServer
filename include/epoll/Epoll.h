#pragma once
#include "../TcpSocket/TcpSocket.h"
#include "../threadPool/Thread.h"
#include <arpa/inet.h>
#include <functional>
#include <memory>
#include <spdlog/spdlog.h>
#include <sys/epoll.h>
#define THREAD_POOL_ACTIVE  

class Epoll : protected TcpSocket {
public:
  Epoll(int port, bool re_use_addr, int bufsize = 1024,
        int epoll_events_size = 1024, bool threadPoolAvtive = false)
      : TcpSocket(port, re_use_addr, bufsize) {
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
    this->epoll_events_size = epoll_events_size;
  }

#ifdef THREAD_POOL_ACTIVE

  // 新增epoll类构造函数，增加epoll的线程池设计
  // template <typename ThreadPoolTemplateName>
  Epoll(int port, bool re_use_addr, bool threadPoolAvtive, int bufsize = 1024,
        int epoll_events_size = 1024, int threadPool_size = 20)
      : TcpSocket(port, re_use_addr, bufsize) {
    this->pool_ptr = std::make_shared<ThreadPool>(threadPool_size);
    this->threadPoolAvtive = true;
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
    this->epoll_events_size = epoll_events_size;
  }
  void startWithThreads(const std::function<char *(char *)> &func);
#endif
  ~Epoll();
  int start(const std::function<char *(char *)> &func);

private:
#ifdef THREAD_POOL_ACTIVE
  int wait(const std::function<char *(char *)> &func);
  void epoll_deal(int readCount, const std::function<char *(char *)> &func);
  int epoll_accpet(int currfd);
  int epoll_recv(int currfd, const std::function<char *(char *)> &func);
#endif
  int epfd;
  epoll_event ev;
  epoll_event *evs;
  int epoll_events_size;
#ifdef THREAD_POOL_ACTIVE
  bool threadPoolAvtive;
  std::shared_ptr<ThreadPool> pool_ptr;
#endif
};