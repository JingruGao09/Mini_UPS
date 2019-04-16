#ifndef __WORLDBRIDGE_H__
#define __WORLDBRIDGE_H__
#include "client.h"
#include "dbinterface.h"
#include "world_ups.pb.h"
#include <iostream>
#include <string>
#define TRUCK_NUM 200
struct _truck_t {
  int truck_id;
  int x;
  int y;
};
struct _package_t {
  int package_id;
  int x;
  int y;
};
typedef struct _package_t package_t;
typedef struct _truck_t truck_t;
class WorldBridge {
private:
  int world_id;
  std::string errmsg;
  Client Hermes;
  DBInterface Zeus;
  /* SendMsg
   * easy way to send google protocol message, return 0 if success
   * else return -1, check errmsg to find some idea
   */
  template <typename T> int SendMsg(T &msg) {
    std::vector<char> buf;
    if (msgToCharArray<T>(msg, buf) == -1)
      return -1;
    if (Hermes.sendData(buf) == -1) {
      errmsg = Hermes.getError();
      return -1;
    }
    return 0;
  }
  int CreateTrucks(int truckNum, UPS::UConnect &msg);
  int SetPackageInfo(truck_t &truck, std::vector<package_t> &packages,
                     UPS::UGoDeliver *goDeliver);

public:
  WorldBridge(const char *hostname, const char *port);
  ~WorldBridge();
  int RequireANewWorld();
  int ConnectToAWorld(const int64_t &wid, bool initTruck);

  int GoPickUp(const int &wh_id, std::vector<truck_t> &trucks,
               const int64_t &seqnum);
  int GoDeliver(truck_t &truck, std::vector<package_t> &packages,
                const int64_t &seqnum);
};
#endif
