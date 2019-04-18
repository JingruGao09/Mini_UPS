#ifndef __UPSERVER_H__
#define __UPSERVER_H__
#include "worldbridge.h"
class UPServer {
private:
  DBInterface Zeus;
  WorldBridge wb;
  int64_t wid;
  void ConnectWorld();

public:
  UPServer(const char *h, const char *p);
};
#endif
