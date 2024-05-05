#include "webserver.h"
#include <iostream>
WebServer::WebServer(int port) {
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(port);
  auto status =
      bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  if (status == -1) {
    std::cerr << "bind err" << std::endl;
    return;
  }
  int opt = 1;
  setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  listen(serverSocket, 128);
  std::cout << "Server running on port " << port << std::endl;
  clientAddrLen = sizeof(clientAddr);
}
void WebServer::Start(Router &router) {
  int clientSocket;
    clientSocket =
        accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
  while (true) {
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::string request(buffer);

    size_t pos1 = request.find(" ");
    size_t pos2 = request.find(" ", pos1 + 1);
    if (pos1 != std::string::npos && pos2 != std::string::npos) {
      std::string url = request.substr(pos1 + 1, pos2 - pos1 - 1);
      router.Route(url, clientSocket);
    } else {
      std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Length: "
                             "15\r\n\r\n400 Bad Request";
      send(clientSocket, response.c_str(), response.size(), 0);
    }

    close(clientSocket);
  }
}
