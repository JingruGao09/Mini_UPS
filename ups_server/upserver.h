#ifndef __UPSERVER_H__
#define __UPSERVER_H__
#include "amazonbridge.h"
#include "log.h"
#include "ups_amazon.pb.h"
#include "world_ups.pb.h"
#include "worldbridge.h"
#include <thread>
#define SIMSPEED 10000
#define FLAKINESS 0
class UPServer {
private:
  DBInterface Zeus;
  Log Homer;
  WorldBridge wb;
  AmazonBridge ab;
  int64_t wid;
  void ConnectWorld();

public:
  UPServer(const char *h, const char *p, const char *a_h, const char *a_p);
  ~UPServer();
  int WorldMsgHandler();
  int AmazonMsgHandler();
  int World_reconnect();
  int Amazon_reconnect();
  void Query();
  int test();
};
#endif
