#include "worldbridge.h"
WorldBridge::WorldBridge(const char *hostname, const char *port)
    : world_id(-1), Hermes(hostname, port) {}

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
int WorldBridge::ConnectToAWorld(const int64_t &wid, bool initTruck) {
  world_id = wid;
  UPS::UConnect msg;
  msg.set_worldid(world_id);
  msg.set_isamazon(false);
  if (initTruck) {
    if (CreateTrucks(TRUCK_NUM, msg) == -1)
      return -1;
  }
  return SendMsg<UPS::UConnect>(msg);
}

/*
 * CreateTrucks
 *
 * send message to world let it randomly create trucks, save into db
 * if failed to save, return -1, succeed,return 0
 */
int WorldBridge::CreateTrucks(int truckNum, UPS::UConnect &msg) {
  UPS::UInitTruck *truck;

  for (int i = 0; i < truckNum; i++) {
    truck = msg.add_trucks();
    truck->set_id(i);
    int x = rand() % 100 - 50;
    int y = rand() % 100 - 50;
    truck->set_x(x);
    truck->set_y(y);
    if (Zeus.createTruck(std::to_string(i), std::to_string(x),
                         std::to_string(y), std::to_string(world_id)) == -1)
      return -1;
  }
  return 0;
}

/*
 * GOPickUp
 *
 * Sent message to world let truck to the wharehouse
 * return 0 if succeed, else -1
 *
 */
int WorldBridge::GoPickUp(const int &wh_id, std::vector<truck_t> &trucks,
                          const int64_t &seqnum) {
  UPS::UCommands command;
  UPS::UGoPickup *pickup;
  for (auto truck : trucks) {
    pickup = command.add_pickups();
    pickup->set_whid(wh_id);
    pickup->set_truckid(truck.truck_id);
    pickup->set_seqnum(seqnum);
    if (Zeus.updateTruckStatus(std::to_string(truck.truck_id),
                               std::to_string(truck.x), std::to_string(truck.y),
                               "EN ROUTE TO A WAREHOUSE",
                               std::to_string(world_id)) == -1) {
      return -1;
    }
  }
  return SendMsg<UPS::UCommands>(command);
}

/*
 * SetPackageInfo
 *
 * set up google protocol buffer to load package info
 * return 0 if succeed, else -1
 */
int WorldBridge::SetPackageInfo(truck_t &truck,
                                std::vector<package_t> &packages,
                                UPS::UGoDeliver *goDeliver) {
  UPS::UDeliveryLocation *location;
  for (auto package : packages) {
    location = goDeliver->add_packages();
    location->set_packageid(package.package_id);
    location->set_x(package.x);
    location->set_y(package.y);
    if (Zeus.createPackage(
            std::to_string(package.package_id), std::to_string(truck.truck_id),
            std::to_string(truck.x), std::to_string(truck.y),
            "OUT FOR DELIVERY", std::to_string(world_id)) == -1) {
      return -1;
    }
  }
  return 0;
}

/*
 * GODeliver
 *
 * Sent message to world let truck to deliver package
 * return 0 if succeed, else -1
 *
 */
int WorldBridge::GoDeliver(truck_t &truck, std::vector<package_t> &packages,
                           const int64_t &seqnum) {
  UPS::UCommands command;
  UPS::UGoDeliver *goDeliver;
  goDeliver = command.add_deliveries();
  goDeliver->set_truckid(truck.truck_id);
  if (SetPackageInfo(truck, packages, goDeliver) == -1)
    return -1;
  goDeliver->set_seqnum(seqnum);
  if (Zeus.updateTruckStatus(std::to_string(truck.truck_id),
                             std::to_string(truck.x), std::to_string(truck.y),
                             "DELIVERING", std::to_string(world_id)))
    return -1;
  return SendMsg<UPS::UCommands>(command);
}
int main() {
  WorldBridge wb("localhost", "12345");
  wb.ConnectToAWorld(1, true);
}
