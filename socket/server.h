#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
void server_func(char *buf, int connectfd);

class Server {
public:
  Server(int port);
  Server(const Server &server) = delete;
  Server(Server &&server) = delete;
  int accept_connect();

private:
  sockaddr_in addr;
  socklen_t addrlen;
  int fd;
  int cfd;
};
