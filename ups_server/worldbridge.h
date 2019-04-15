#ifndef __WORLDBRIDGE_H__
#define __WORLDBRIDGE_H__
#include "client.h"
#include "dbinterface.h"
#include "world_ups.pb.h"
#include <iostream>
#include <string>
#define TRUCK_NUM 200
class WorldBridge {
private:
  std::string errmsg;
  Client Hermes;
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

public:
  WorldBridge(const char *hostname, const char *port);
  ~WorldBridge();
  int RequireANewWorld();
  int ConnectToAWorld(int64_t world_id, bool initTruck);
  int CreateTrucks(int truckNum, UPS::UConnect &msg, const int &world_id);
  int GoPickUp();
  int GoDeliver();
};
#endif
