#ifndef __WORLDBRIDGE_H__
#define __WORLDBRIDGE_H__
#include "client.h"
#include "dbinterface.h"
#include "helper.h"
#include "log.h"
#include "world_ups.pb.h"
#include <iostream>
#include <string>
#define TRUCK_NUM 200
struct _truck_t {
  int truck_id;
  int x;
  int y;
};

typedef struct _truck_t truck_t;
class WorldBridge {
private:
  int world_id;
  std::string errmsg;
  Client Hermes;
  DBInterface Zeus;
  Log Homer;
  int CreateTrucks(int truckNum, UPS::UConnect *msg,
                   std::vector<truck_t> &trucks);
  int SetPackageInfo(const int &truck_id, package_t &packages,
                     UPS::UGoDeliver *goDeliver);
  int finished_handler(UPS::UResponses &msg, std::vector<truck_t> &trucks,
                       std::vector<int64_t> &seqnums);
  int delivery_handler(UPS::UResponses &msg, std::vector<int64_t> &seqnums);
  int ack_handler(UPS::UResponses &msg);
  int truck_handler(UPS::UResponses &msg, std::vector<int64_t> &seqnums);
  int err_handler(UPS::UResponses &msg, std::vector<int64_t> &seqnums);
  int selectATruck(const int &wh_x, const int &wh_y);

public:
  WorldBridge(const char *hostname, const char *port);

  ~WorldBridge();
  void setWid(const int64_t &wid);
  int RequireANewWorld(std::vector<truck_t> &trucks);
  int ConnectToAWorld(const int64_t &wid);
  int DisconnectAWorld();
  int ParseConnectWorldInfo(UPS::UConnected &msg);
  int GoPickUp(const int &wh_id, const int &wh_x, const int &wh_y,
               const std::vector<int> &package_ids);
  int GoDeliver(const int &truck_id, const int &package_id);
  int Query(const int &truck_id);
  int ack(const std::vector<int64_t> &seqnums);
  int ParseResponses(UPS::UResponses &msg, std::vector<truck_t> &trucks);
  int SetWorldOptions(int speed);
  template <typename T> int RecvMsg(T &msg) { return Hermes.recvMsg<T>(msg); }
};
#endif
