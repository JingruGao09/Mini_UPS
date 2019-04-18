#ifndef __UPSERVER_H__
#define __UPSERVER_H__
#include "world_ups.pb.h"
#include "worldbridge.h"
#define SIMSPEED 100
#define FLAKINESS 0
class UPServer {
private:
  DBInterface Zeus;
  WorldBridge wb;
  int64_t wid;
  void ConnectWorld();

public:
  UPServer(const char *h, const char *p);
  int WorldMsgHandler();
  int test();
};
#endif
