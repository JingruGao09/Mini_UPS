#ifndef __WEBRIDGE_H__
#define __WEBRIDGE_H__
#include "helper.h"
#include "log.h"
#include "server.h"
#include "web_ups.pb.h"
class WeBridge {
private:
  Server Hermes;
  int sockfd;
  Log Homer;

public:
  WeBridge(const char *port);
  void accptNewConn();
  int SendTruckStatus(const truck_t truck);
  int ParseRequest(WEB::QueryTruck &msg);
};
#endif
