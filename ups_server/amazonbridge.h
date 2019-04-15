#ifndef __AMAZONBRIDGE_H__
#define __AMAZONBRIDGE_H__
#include "client.h"

// client will do connection and garbage collection
class AmazonBridge {
private:
  Client Hermes;

public:
  AmazonBridge(const char *hostname, const char *port);
  ~AmazonBridge();
  int SendWorldId(const int &world_id);
  int SendTruckId();
  int SendPackageId();
};
#endif
