#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

typedef void (*RequestHandler)(int clientSocket);

class Router {
private:
    std::map<std::string, std::function<void(int)>> routes;

public:
    void Get(const std::string& url, RequestHandler handler) ;

    void Route(const std::string& url, int clientSocket) ;
};
