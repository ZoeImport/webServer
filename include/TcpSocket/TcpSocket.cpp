#include "TcpSocket.h"
#include "spdlog/spdlog.h"
#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <cstring>
#include <functional>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

void ConnectCallback(char *buf, int connectfd,
                     const std::function<char *(char *)> &func) {
  // auto func_ptr = std::make_unique(
  // std::bind(std::forward<F>(f), std::forward<Args>(args)...));

  // char *response;
  // strcpy(response, httpResponse.c_str());
  auto date = func(buf);
  auto ret = send(connectfd, date, sizeof(date), 0);
}

TcpSocket::TcpSocket(int port, bool re_use_addr, int bufsize) {
  this->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    spdlog::error("socket error ");
    // throw std::exception();
    return;
  }
  this->addr.sin_family = AF_INET;
  this->addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
  addrlen = sizeof(addr);
  if (re_use_addr) {
    int opt = 1;
    setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    spdlog::info("REUSEADDR active ...");
  }
  auto ret = bind(fd, (sockaddr *)&addr, addrlen);
  if (ret == -1) {
    spdlog::error("bind error ");
    return;
  }
  listen(fd, 128); // mark the max connect size
  this->buf = new char[bufsize];
  this->buffersize = bufsize;
}

int TcpSocket::accept_connect(const std::function<char *(char *)> &func) {
  spdlog::info("waiting connection");
  sockaddr_in caddr;
  this->cfd = accept(fd, (struct sockaddr *)&caddr, &addrlen);
  if (cfd == -1) {
    spdlog::error("accpet error ");
    return -1;
  }
  spdlog::info("connect successfully !!!");
  char ip[32];
  spdlog::info("client address : {}:{}",
               inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip, sizeof(ip)),
               ntohs(caddr.sin_port));
  // std::cout << "client ip: "
  //           << inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip, sizeof(ip)) <<
  //           ","
  //           << "port: " << ntohs(caddr.sin_port) << std::endl;
  while (true) {
    char buffer[1024];
    auto len = recv(cfd, buffer, sizeof(buffer), 0);
    if (len > 0) {
      ConnectCallback(buffer, cfd, func);
    } else if (len == 0) {
      spdlog::info("client close ");
      break;
    } else {
      spdlog::error("recv error ");
      break;
    }
  }
  close(fd);
  close(cfd);
  return 0;
}

std::string httpResponse = "HTTP/1.1 200 OK\r\n"
                           "Content-Type: text/html; charset=UTF-8\r\n"
                           "\r\n"
                           "<!DOCTYPE html>\n"
                           "<html>\n"
                           "<head>\n"
                           "<title>HTML Response</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "<h1>Hello, this is a simple HTML response!</h1>\n"
                           "</body>\n"
                           "</html>\n";

// int TcpSocket::httpHandle() {
//   spdlog::info("waiting connection");
//   sockaddr_in caddr;
//   this->cfd = accept(fd, (struct sockaddr *)&caddr, &addrlen);
//   if (cfd == -1) {
//     spdlog::error("accpet error ");
//     return -1;
//   }
//   spdlog::info("connect successfully !!!");
//   char ip[32];
//   spdlog::info("client address : {}:{}",
//                inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip, sizeof(ip)),
//                ntohs(caddr.sin_port));
//   // std::cout << "client ip: "
//   //           << inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip, sizeof(ip)) <<
//   //           ","
//   //           << "port: " << ntohs(caddr.sin_port) << std::endl;
//   spdlog::info("ready into loop ");
//   while (true) {
//     char buffer[1024];
//     spdlog::info("recv buffer ");
//     auto len = recv(cfd, buffer, sizeof(buffer), 0);
//     std::cout << buffer << std::endl;
    
//     spdlog::info("recv request ,len :{}", len);
//     if (len > 0) {
//       std::string req_str(buffer);
//       HttpRequest req(req_str);
//       auto msg= ::httpHandle(req);
//       spdlog::info("ready to send response");
//       std::cout<<msg<<std::endl;
//       send(cfd, msg.c_str(), msg.size(), 0);
//     } else if (len == 0) {
//       spdlog::info("client close ");
//       break;
//     } else {
//       spdlog::error("recv error ");
//       break;
//     }
//   }
//   close(fd);
//   close(cfd);
//   return 0;
// }

// int TcpSocket::httpHandleTest() {
//   // spdlog::set_level(spdlog::level::err);
//   sockaddr_in caddr;
//   this->cfd = accept(fd, (struct sockaddr *)&caddr, &addrlen);
//   if (cfd == -1) {
//     spdlog::error("accpet error ");
//     return -1;
//   }
//   spdlog::info("connect successfully !!!");
//   char ip[32];
//   spdlog::info("client address : {}:{}",
//                inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip, sizeof(ip)),
//                ntohs(caddr.sin_port));
//   spdlog::info("ready into loop ");
//   while (true) {
//     char buffer[1024];
//     spdlog::info("recv buffer ");
//     auto len = recv(cfd, buffer, sizeof(buffer), 0);
//     std::string recv_buf(buffer); 
//     std::cout << recv_buf << std::endl;
    
//     spdlog::info("recv request ,len :{}", len);
//     if (len > 0) {
//       spdlog::info("ready to send response");
//       HttpRequest request(recv_buf);
//       std::cout<<request.getMsg()<<std::endl;
//       send(cfd, httpResponse.c_str(), httpResponse.size(), 0);
//     } else if (len == 0) {
//       spdlog::info("client close ");
//       break;
//     } else {
//       spdlog::error("recv error ");
//       break;
//     }
//   }
//   close(fd);
//   close(cfd);
//   return 0;
// }

