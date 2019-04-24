#include "webridge.h"

WeBridge::WeBridge(const char *port) : Hermes(port) {}

void WeBridge::accptNewConn() { sockfd = Hermes.acceptNewConn(); }

int WeBridge::SendTruckStatus(const truck_t truck) {
  WEB::TruckStatus msg;
  msg.set_truckid(truck.truck_id);
  msg.set_x(truck.x);
  msg.set_y(truck.y);
  msg.set_status(truck.status);
  Homer.LogSendMsg("Web", "truck " + std::to_string(truck.truck_id) +
                              " is at (" + std::to_string(truck.x) + "," +
                              std::to_string(truck.y) + ")");
  return Hermes.sendMsg<WEB::TruckStatus>(sockfd, msg);
}

int WeBridge::ParseRequest(WEB::QueryTruck &msg) { return msg.truckid(); }
