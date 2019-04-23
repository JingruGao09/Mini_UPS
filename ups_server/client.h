#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "helper.h"
#include "world_ups.pb.h"
#include <algorithm>
#include <arpa/inet.h>
#include <cstring>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <netdb.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#define MAXDATASIZE 65536
typedef struct addrinfo addrinfo;
typedef struct timeval timeval;
class Client {
private:
  std::string errmsg;
  int sockfd;
  const char *hostname;
  const char *port;
  const char *getHost(const char *hostname);
  std::vector<char> recvall(int fd);
  int sendall(int fd, const char *buf, size_t *len);

public:
  Client(const char *h, const char *p);

  ~Client();
  int reconnect();
  std::vector<char> receiveData();
  std::vector<char> basicRecv();
  int sendData(const std::vector<char> &msg);
  int getFD();
  std::string getError();
  template <typename T> int sendMsg(T &msg) {
    google::protobuf::io::FileOutputStream out(sockfd);
    if (!sendMesgTo(msg, &out))
      return -1;
    return 0;
  }

  template <typename T> int recvMsg(T &msg) {
    google::protobuf::io::FileInputStream in(sockfd);
    if (!recvMesgFrom(msg, &in))
      return -1;
    return 0;
  }
};
#endif
