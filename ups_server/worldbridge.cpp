#include "worldbridge.h"

WorldBridge::WorldBridge(const char *hostname, const char *port)
    : Hermes(hostname, port) {}

WorldBridge::~WorldBridge() {}

/*
 * RequireANewWorld
 *
 * Send msg to require a new world id
 * if success return 0, else, return -1
 */
int WorldBridge::RequireANewWorld() {
  UPS::UConnect msg;
  msg.set_worldid(5);
  msg.set_isamazon(false);
  return SendMsg<UPS::UConnect>(msg);
}
/*
 * ConnectToAWorld
 *
 * Connect to a simulate world.
 * if it is a new world, set initruck as true
 * send success return 0, else return -1
 *
 */
int WorldBridge::ConnectToAWorld(int64_t world_id, bool initTruck) {
  UPS::UConnect msg;
  msg.set_worldid(world_id);
  msg.set_isamazon(false);
  if (initTruck) {
    if (CreateTrucks(TRUCK_NUM, msg, world_id) == -1)
      return -1;
  }
  return SendMsg<UPS::UConnect>(msg);
}
/*
 * CreateTrucks
 *
 * randomly create trucks, save into db
 * if failed to save, return -1, succeed,return 0
 */
int WorldBridge::CreateTrucks(int truckNum, UPS::UConnect &msg,
                              const int &world_id) {
  UPS::UInitTruck *truck;
  DBInterface db;
  for (int i = 0; i < truckNum; i++) {
    truck = msg.add_trucks();
    truck->set_id(i);
    int x = rand() % 100 - 50;
    int y = rand() % 100 - 50;
    truck->set_x(x);
    truck->set_y(y);
    if (db.createTruck(std::to_string(i), std::to_string(x), std::to_string(y),
                       std::to_string(world_id)) == -1)
      return -1;
  }
  return 0;
}
int main() {
  WorldBridge wb("localhost", "12345");
  wb.ConnectToAWorld(1, true);
}
