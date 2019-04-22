#ifndef __AMAZONBRIDGE_H__
#define __AMAZONBRIDGE_H__
#include "client.h"
#include "dbinterface.h"
#include "log.h"
#include "server.h"
#include "ups_amazon.pb.h"
#include <iostream>
#include <string>

struct _truck_location {
  int truck_id;
  int wh_x;
  int wh_y;
};
struct _package_info {
  int package_id;
  std::string description;
  int count;
};
struct _warehouse_info {
  int wh_id;
  int wh_x;
  int wh_y;
  std::vector<int> package_ids;
};
struct _truck_dest {
  int truck_id;
  int64_t package_id;
};
typedef struct _truck_location truck_location;
typedef struct _package_info package_info;
typedef struct _warehouse_info warehouse_info;
typedef struct _truck_dest truck_dest;

class AmazonBridge {
private:
  int64_t world_id;
  std::string errmsg;
  Client ConAmazonClient;
  DBInterface Zeus;
  Log Homer;

  int apackageinfo_handler(UA::DetermineWarehouse &warehouseinfo,
                           std::vector<int> &package_ids);
  int determinewarehouse_handler(UA::AUCommands &msg,
                                 std::vector<int64_t> &seqnums,
                                 std::vector<warehouse_info> &warehouse_infos);
  int truckdst_handler(UA::DetermineDst &msg,
                       std::vector<truck_dest> &truck_dsts);
  int determinedst_handler(UA::AUCommands &msg, std::vector<int64_t> &seqnums,
                           std::vector<truck_dest> &truck_dsts);
  int ack_handler(UA::AUCommands &msg);

public:
  AmazonBridge(const char *hostname, const char *port);
  ~AmazonBridge();
  int SendWorldId();
  int SendTruckId(std::vector<truck_location> &trucks);
  int SendPackageId(std::vector<int64_t> &package_ids);
  int FinishShipment(std::vector<int64_t> &package_ids);
  int ack(const std::vector<int64_t> &seqnum);
  int ParseResponses(UA::AUCommands &msg,
                     std::vector<warehouse_info> &warehouse_infos,
                     std::vector<truck_dest> &truck_dsts);
  int setWid(const int64_t &wid);
  template <typename T> int RecvMsg(T &msg) {
    return ConAmazonClient.recvMsg<T>(msg);
  }
};
#endif
