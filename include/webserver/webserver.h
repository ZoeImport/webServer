#include <netinet/in.h>
#include <sys/socket.h>

struct Socket {
  sockaddr_in addr;
  int fd;
  int cfd;
};

class Webserver {
private:
  Socket _socket;
  
public:
  Webserver(int port);
};