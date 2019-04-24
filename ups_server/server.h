#ifndef __SERVER_H__
#define __SERVER_H__
#include "helper.h"
#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include <signal.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#define MAXDATASIZE 65536
typedef struct addrinfo addrinfo;
typedef struct sockaddr_storage sockaddr_storage;
typedef struct sockaddr sockaddr;
class Server {
private:
  const char *port;
  addrinfo host_info;
  int listener;
  std::vector<char> recvall(int fd);
  std::vector<char> recvall2(int fd);
  int sendall(int fd, const char *buf, size_t *len);

public:
  Server();
  Server(const char *p);
  ~Server();
  int acceptNewConn();
  std::vector<char> receiveData(int fd);
  void sendData(int fd, const std::vector<char> &msg);
  std::vector<char> basicRecv(int fd);
  template <typename T> int sendMsg(int sockfd, T &msg) {
    google::protobuf::io::FileOutputStream out(sockfd);
    if (!sendMesgTo(msg, &out))
      return -1;
    return 0;
  }

  template <typename T> int recvMsg(int sockfd, T &msg) {
    google::protobuf::io::FileInputStream in(sockfd);
    if (!recvMesgFrom(msg, &in))
      return -1;
    return 0;
  }
};
#endif
