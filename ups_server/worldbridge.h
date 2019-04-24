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
  int delivery_handler(UPS::UResponses &msg, std::vector<int64_t> &seqnums,
                       std::vector<int64_t> &packageids);
  int ack_handler(UPS::UResponses &msg);
  int truck_handler(UPS::UResponses &msg, std::vector<int64_t> &seqnums,
                    std::vector<truck_t> &truckstatus);
  int err_handler(UPS::UResponses &msg, std::vector<int64_t> &seqnums);
  int selectATruck(const int &wh_x, const int &wh_y);
  int resendQuery(const int &truck_id, const int &seqnum);
  int resendGoDeliver(const int &truck_id, const int &package_id,
                      const int &package_x, const int &package_y,
                      const int &seqnum);
  int resendGoPickUp(const int &wh_id, const int &truck_id, const int &seqnum);
  int ReSendMsg();

public:
  WorldBridge(const char *hostname, const char *port);

  ~WorldBridge();
  int reconnect();
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
  int ParseResponses(UPS::UResponses &msg, std::vector<truck_t> &trucks,
                     std::vector<int64_t> &packageids,
                     std::vector<truck_t> &truckstatus);
  int SetWorldOptions(int speed);
  template <typename T> int RecvMsg(T &msg) { return Hermes.recvMsg<T>(msg); }
};
#endif
