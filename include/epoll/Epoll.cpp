#include "Epoll.h"
#include "../tools/tool.cpp"
#include "spdlog/spdlog.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <mutex>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <utility>

int Epoll::start(const std::function<char *(char *)> &func) {
  spdlog::info("start begin");
  while (1) {
    int num = epoll_wait(this->epfd, this->evs, this->epoll_events_size, -1);
    for (auto index = 0; index < num; ++index) {
      int curfd = this->evs[index].data.fd;
      if (curfd == this->fd) {
        int cfd = accept(curfd, NULL, NULL);
        spdlog::info("accept new connect");
        this->ev.events = EPOLLIN;
        this->ev.data.fd = cfd;
        int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
        if (ret == -1) {
          spdlog::error("epoll ctl add error");
          exit(0);
        }
      } else {
        memset(this->buf, 0, this->buffersize);
        int len = recv(curfd, this->buf, this->buffersize, 0);
        if (len == 0) {
          spdlog::info("client close");
          epoll_ctl(this->epfd, EPOLL_CTL_DEL, curfd, NULL);
          close(curfd);
        } else if (len > 0) {
          spdlog::info("client say: {}", this->buf);
          send(curfd, this->buf, len, 0);
          ConnectCallback(this->buf, curfd, func);
        } else {
          spdlog::error("recv error");
          exit(0);
        }
      }
    }
  }
}
#ifdef THREAD_POOL_ACTIVE

void Epoll::startWithThreads(const std::function<char *(char *)> &func) {
  this->wait(func);
}

int Epoll::wait(const std::function<char *(char *)> &func) {
  int readyCount = 0;
  while (1) {
    // spdlog::info("epoll waiting for events ...");
    readyCount = epoll_wait(this->epfd, this->evs, this->epoll_events_size, -1);
    spdlog::info("readyCount {} ", readyCount);
    if (readyCount == -1) {
      spdlog::error("epoll wait error");
      return -1;
    }
    this->epoll_deal(readyCount, func);
    memset(this->evs, 0, this->epoll_events_size);
    // spdlog::info("evs arr clear");
  }
}

void Epoll::epoll_deal(int readCount,
                       const std::function<char *(char *)> &func) {
  {
    for (int index = 0; index < readCount; ++index) {
      int currfd = (this->evs[index].data.fd);
      if (currfd == (this->fd)) {
        // 建立新连接到监听文件描述符
        this->pool_ptr.get()->enQueue(
            [this, currfd] { return this->epoll_accpet(currfd); });
        spdlog::info("accpet task add to thread");
      } else {
        // std::thread recv(
        //     [this, currfd, &func]() { this->epoll_recv(currfd, func); });
        // recv.join();
        auto lambda = std::bind(&Epoll::epoll_recv, this, currfd, func);
        this->pool_ptr.get()->enQueue(lambda);
        spdlog::info("recv task add to thread");
      }
    }
  }
}

int Epoll::epoll_accpet(int currfd) {
  int cfd = accept(currfd, NULL, NULL);
  spdlog::info("accept new connect");
  this->ev.events = EPOLLIN;
  this->ev.data.fd = cfd;
  int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
  if (ret == -1) {
    spdlog::error("epoll ctl add error");
    exit(-1);
  }
  return 0;
}

int Epoll::epoll_recv(int currfd, const std::function<char *(char *)> &func) {
  spdlog::info("recv data");
  memset(this->buf, 0, this->buffersize);
  int len = recv(currfd, this->buf, this->buffersize, 0);
  if (len == 0) {
    spdlog::info("client close");
    epoll_ctl(this->epfd, EPOLL_CTL_DEL, currfd, NULL);
    close(currfd);
  } else if (len > 0) {
    spdlog::info("client say: {}", this->buf);
    // send(currfd, this->buf, len, 0);
    ConnectCallback(this->buf, currfd, func);
  } else {
    spdlog::error("recv error");
    // exit(0);
    close(currfd);
  }
  return 0;
}
#endif
Epoll::~Epoll() { spdlog::info("epoll destruct "); }