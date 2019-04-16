#ifndef __AMAZONBRIDGE_H__
#define __AMAZONBRIDGE_H__
#include "client.h"
#include "server.h"
#include "ups_amazon.pb.h"
#include "dbinterface.h"
#include <iostream>
#include <string>

// client will do connection and garbage collection
class AmazonBridge {
private:
  Client ConAmazonClient;
  Server UpsServer;

  template <typename T> int SendMsg(T &msg) {
    std::vector<char> buf;
    if (msgToCharArray<T>(msg, buf) == -1)
      return -1;
    if (ConAmazonClient.sendData(buf) == -1) {
      errmsg = ConAmazonClient.getError();
      return -1;
    }
    return 0;
  }

 public:
  AmazonBridge(const char *hostname, const char *port);
  ~AmazonBridge();
  int SendWorldId(const int &world_id);
  int SendTruckId();
  int SendPackageId();
};
#endif
