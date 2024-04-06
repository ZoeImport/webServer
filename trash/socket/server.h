#include <arpa/inet.h>
#include <functional>
#include <netinet/in.h>
#include <sys/socket.h>

void server_func(char *buf, int connectfd,const std::function<char*(char*)> &func);

class Server {
public:
  Server(int port,bool re_use_addr) ;
  Server(const Server &server) = delete;
  Server(Server &&server) = delete;
  int accept_connect(const std::function<char*(char*)> &func);

private:
  sockaddr_in addr;
  socklen_t addrlen;
  int fd;
  int cfd;
};
