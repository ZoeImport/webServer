#include <iostream>
#include <map>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "router.h"

class WebServer {
private:
    int serverSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;

public:
    WebServer(int port=8080) ;

    void Start(Router& router);

    ~WebServer() {
        close(serverSocket);
    }
};

