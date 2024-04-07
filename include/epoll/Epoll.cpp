#include "Epoll.h"
#include "spdlog/spdlog.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

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
          ConnectCallback(this->buf, curfd,func);
        } else {
          spdlog::error("recv error");
          exit(0);
        }
      }
    }
  }
}