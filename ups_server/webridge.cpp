#include "webridge.h"

WeBridge::WeBridge(const char *port) : Hermes(port) {}

void WeBridge::accptNewConn() { sockfd = Hermes.acceptNewConn(); }

std::vector<char> WeBridge::recv() { return Hermes.basicRecv(sockfd); }
int WeBridge::getTruckId(const std::vector<char> &msg) {
  std::string msg_str = msg.data();
  return stoi(msg_str);
}
