#include "client.h"

/*
 * getHost
 * This function can get IP from hostname
 *
 */
const char *Client::getHost(const char *hostname) {
  struct hostent *he = gethostbyname(hostname);
  if (he == nullptr)
    throw std::string("no host");
  struct in_addr **addr_list = (struct in_addr **)he->h_addr_list;
  return inet_ntoa(*addr_list[0]);
}

/*
 * Sendall
 * This function try to send all data to the socket
 *
 * Test Status: pass unit test
 */
int Client::sendall(int fd, const char *buf, size_t *len) {
  size_t total = 0;     // how many bytes we've sent
  int bytesleft = *len; // how many we have left to send
  int n;

  while (total < *len) {
    if ((n = send(fd, buf + total, bytesleft, 0)) == -1) {
      break;
    }
    total += n;
    bytesleft -= n;
  }

  *len = total; // return number actually sent here

  return n == -1 ? -1 : 0; // return -1 on failure, 0 on success
}

/*
 * Send
 * This function make sure send all data to the socket
 *
 * Test Status: pass unit test
 */
int Client::sendData(const std::vector<char> &msg) {
  try {
    size_t sent = 0;
    size_t len = msg.size();
    size_t max = msg.size();
    while (sent < len) {
      sent = len - sent;
      len = sent;
      if (sendall(sockfd, &msg.data()[max - len], &sent) == -1) {
        throw std::string("send failed");
      }
    }
    return 0;
  } catch (std::string &e) {
    throw std::string("socket failed");
    return -1;
  }
}

/*
 * recvall
 * This function will receive all data from one socket
 *
 * Test Status: pass unit test, timeout=1, might be too long
 */
std::vector<char> Client::recvall(int fd) {
  std::vector<char> msg;
  size_t index = 0;
  int contentlen = 0;
  if (msg.size() < index + MAXDATASIZE)
    msg.resize(index + MAXDATASIZE);
  int nbytes;
  if ((nbytes = recv(fd, &msg.data()[index], MAXDATASIZE - 1, 0)) <= 0) {
    return std::vector<char>();
  } else {
    index += nbytes;
  }
  std::vector<char> pattern{'\n'};
  auto it = std::search(msg.begin(), msg.end(), pattern.begin(), pattern.end());
  std::string len_str(msg.begin(), it);
  contentlen = stoi(len_str);
  msg.erase(msg.begin(), it + 1);
  index -= (it + 1 - msg.begin());
  msg.resize(index);
  for (it = msg.begin(); it != msg.end(); it++) {
    contentlen--;
  }
  while (contentlen) {
    if (msg.size() < index + MAXDATASIZE)
      msg.resize(index + MAXDATASIZE);
    int nbytes;
    if ((nbytes = recv(fd, &msg.data()[index], MAXDATASIZE - 1, 0)) <= 0) {
      break;
    } else {
      index += nbytes;
      contentlen -= nbytes;
    }
  }
  msg.resize(index);
  return msg;
}
std::vector<char> Client::basicRecv() {
  int index = 0;
  std::vector<char> msg;
  msg.resize(MAXDATASIZE);
  index = recv(sockfd, &msg.data()[index], MAXDATASIZE - 1, 0);
  if (index == -1)
    throw std::string("recv failed");
  msg.resize(index);
  return msg;
}
std::vector<char> Client::receiveData() { return recvall(sockfd); }

int Client::getFD() { return sockfd; }

/*
 * initializer
 * This function initialize the socket and connect to server
 * status: uncomplete, exception
 *
 */
std::string Client::getError() { return errmsg; }

Client::Client(const char *h, const char *p) {
  port = p;
  hostname = getHost(h);
  addrinfo host_info;
  addrinfo *host_info_list;

  memset(&host_info, 0, sizeof(host_info));
  host_info.ai_family = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;
  try {
    if (getaddrinfo(hostname, port, &host_info, &host_info_list) != 0)
      throw std::string("getaddrinfo");

    sockfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                    host_info_list->ai_protocol);
    if (sockfd == -1)
      throw std::string("socket");

    if ((connect(sockfd, host_info_list->ai_addr,
                 host_info_list->ai_addrlen)) == -1)
      throw std::string("connect");
  } catch (std::string &e) {
    errmsg = e;
    throw e;
  }
  freeaddrinfo(host_info_list);
}
int Client::reconnect() {
  close(sockfd);
  addrinfo host_info;
  addrinfo *host_info_list;

  memset(&host_info, 0, sizeof(host_info));
  host_info.ai_family = AF_UNSPEC;
  host_info.ai_socktype = SOCK_STREAM;
  try {
    if (getaddrinfo(hostname, port, &host_info, &host_info_list) != 0)
      throw std::string("getaddrinfo");

    sockfd = socket(host_info_list->ai_family, host_info_list->ai_socktype,
                    host_info_list->ai_protocol);
    if (sockfd == -1)
      throw std::string("socket");

    if ((connect(sockfd, host_info_list->ai_addr,
                 host_info_list->ai_addrlen)) == -1)
      throw std::string("connect");
  } catch (std::string &e) {
    errmsg = e;
    freeaddrinfo(host_info_list);
    return -1;
  }
  freeaddrinfo(host_info_list);
  return 0;
}
Client::~Client() { close(sockfd); }
