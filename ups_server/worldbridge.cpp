#include "worldbridge.h"
#include <iostream>
WorldBridge ::WorldBridge(const char *hostname, const char *port)
    : world_id(-1), Hermes(hostname, port) {}
WorldBridge::~WorldBridge() {}

/*
 * RecvMsg
 *
 * return msg in vector<char>
 */
// std::vector<char> WorldBridge::RecvMsg() { return Hermes.; }

/*
 * RequireANewWorld
 *
 * Send msg to require a new world id
 * if success return 0, else, return -1
 * pass test
 */
int WorldBridge::RequireANewWorld() {
  UPS::UConnect msg;
  msg.set_isamazon(false);
  Homer.LogSendMsg("World", "Requesting a new world");
  return Hermes.sendMsg<UPS::UConnect>(msg);
}

/* ConnectToAWorld
 *
 * Connect to a simulate world.
 * if it is a new world, set initruck as true
 * send success return 0, else return -1
 * pass test
 */
int WorldBridge::ConnectToAWorld(const int64_t &wid, bool initTruck) {
  world_id = wid;
  UPS::UConnect msg;
  msg.set_worldid(world_id);
  msg.set_isamazon(false);
  if (initTruck) {
    if (CreateTrucks(TRUCK_NUM, &msg) == -1)
      return -1;
  }
  Homer.LogSendMsg("World", "Connecting to world " + std::to_string(wid));
  return Hermes.sendMsg<UPS::UConnect>(msg);
}

/*
 * ParseConnectWorldInfo
 *
 * parse the message to check whether succeed to connect world
 *
 * return 0 if succeed, return -1 if fail
 * pass test
 */
int WorldBridge::ParseConnectWorldInfo(UPS::UConnected &msg) {
  Homer.LogRecvMsg("World", msg.result());
  if (msg.result() == "connected!")
    return 0;
  return -1;
}
/*
 * CreateTrucks
 *
 * send message to world let it randomly create trucks, save into db
 * if failed to save, return -1, succeed,return 0
 * pass test
 */
int WorldBridge::CreateTrucks(int truckNum, UPS::UConnect *msg) {
  UPS::UInitTruck *truck;

  for (int i = 0; i < truckNum; i++) {
    truck = msg->add_trucks();
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
 * after use this function, query to get truck info
 * return 0 if succeed, else -1
 *
 */
int WorldBridge::GoPickUp(const int &wh_id, std::vector<truck_t> &trucks) {
  UPS::UCommands command;
  UPS::UGoPickup *pickup;
  int64_t seqnum;
  for (auto truck : trucks) {
    pickup = command.add_pickups();
    pickup->set_whid(wh_id);
    pickup->set_truckid(truck.truck_id);
    if ((seqnum = Zeus.fetchSeqNum(std::to_string(world_id))) == -1)
      return -1;
    pickup->set_seqnum(seqnum);
    Homer.LogSendMsg("World",
                     "sending truck " + std::to_string(truck.truck_id) +
                         " to warehouse " + std::to_string(wh_id),
                     std::to_string(seqnum));
    // save msg to db
  }
  return Hermes.sendMsg<UPS::UCommands>(command);
}

int WorldBridge::SetWorldOptions(int speed) {
  UPS::UCommands command;
  command.set_simspeed(speed);
  Homer.LogSendMsg("World", "setting world speed to " + std::to_string(speed));
  return Hermes.sendMsg<UPS::UCommands>(command);
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
    Homer.LogSendMsg("World",
                     "loading package " + std::to_string(package.package_id) +
                         " onto truck " + std::to_string(truck.truck_id));
  }
  return 0;
}

/*
 * GODeliver
 *
 * Sent message to world let truck to deliver package
 * after using this function, please query
 * return 0 if succeed, else -1
 *
 */
int WorldBridge::GoDeliver(truck_t &truck, std::vector<package_t> &packages) {
  UPS::UCommands command;
  UPS::UGoDeliver *goDeliver;
  int64_t seqnum;
  goDeliver = command.add_deliveries();
  goDeliver->set_truckid(truck.truck_id);
  if (SetPackageInfo(truck, packages, goDeliver) == -1)
    return -1;
  if ((seqnum = Zeus.fetchSeqNum(std::to_string(world_id))) == -1)
    return -1;
  goDeliver->set_seqnum(seqnum);
  // save msg to db
  Homer.LogSendMsg("World",
                   "sending truck " + std::to_string(truck.truck_id) +
                       " to deliver",
                   std::to_string(seqnum));
  return Hermes.sendMsg<UPS::UCommands>(command);
}

int WorldBridge::Query(const int &truck_id) {
  UPS::UCommands command;
  UPS::UQuery *query;
  int64_t seqnum;
  query = command.add_queries();
  query->set_truckid(truck_id);
  if ((seqnum = Zeus.fetchSeqNum(std::to_string(world_id))) == -1)
    return -1;
  query->set_seqnum(seqnum);
  // save msg to db
  Homer.LogSendMsg("World",
                   "querying status of truck " + std::to_string(truck_id),
                   std::to_string(seqnum));
  return Hermes.sendMsg<UPS::UCommands>(command);
}
/*
 * ack
 * send ack info to server
 *
 * return 0 if succeed, else -1
 */
int WorldBridge::ack(const std::vector<int64_t> &seqnums) {
  UPS::UCommands command;
  for (unsigned long i = 0; i < seqnums.size(); i++) {
    command.add_acks(seqnums[i]);
    Homer.LogSendMsg("World", "acking " + std::to_string(seqnums[i]));
  }
  return Hermes.sendMsg<UPS::UCommands>(command);
}

/*
 * ParseResponse
 *
 * handle all message from world simulator
 *
 * return -1,if fail to pass message or db error
 * return 1, if world closed successfully
 * return 2, if exist any error
 * return 0, if succeed
 * if truck arrive wh, trucks will be updated.
 */
int WorldBridge::ParseResponses(UPS::UResponses &msg,
                                std::vector<truck_t> &trucks) {
  std::vector<int64_t> seqnums;
  if (msg.has_finished() && msg.finished())
    return 1;
  if (finished_handler(msg, trucks, seqnums) == -1)
    return -1;
  if (delivery_handler(msg, seqnums) == -1)
    return -1;
  ack_handler(msg);
  if (truck_handler(msg, seqnums) == -1)
    return -1;
  if (err_handler(msg, seqnums) == -1)
    return -1;
  if (ack(seqnums) == -1)
    return -1;
  return 0;
}
/*
 * finished_handler
 *
 * when truck arrive warehouse or complete all delivery,
 * we will handle Ufinished message
 *
 * return 0 if succeed, else -1
 * if the status is arrive warehouse, trucks will be updated
 *
 */
int WorldBridge::finished_handler(UPS::UResponses &msg,
                                  std::vector<truck_t> &trucks,
                                  std::vector<int64_t> &seqnums) {
  for (int i = 0; i < msg.completions_size(); i++) {
    UPS::UFinished finished = msg.completions(i);
    seqnums.push_back(finished.seqnum());
    if (Zeus.docInSeqNum(std::to_string(finished.seqnum()),
                         std::to_string(world_id)) == -1)
      continue;
    if (Zeus.updateTruckStatus(std::to_string(finished.truckid()),
                               std::to_string(finished.x()),
                               std::to_string(finished.y()), finished.status(),
                               std::to_string(world_id)))
      return -1;

    if (finished.status() == "arrive warehouse") {
      Homer.LogRecvMsg("World",
                       "truck " + std::to_string(finished.truckid()) +
                           " arrived at warehouse, located at (" +
                           std::to_string(finished.x()) + "," +
                           std::to_string(finished.y()) + ")",
                       std::to_string(finished.seqnum()));
      trucks.push_back({finished.truckid(), finished.x(), finished.y()});
    } else {
      Homer.LogRecvMsg("World",
                       "truck " + std::to_string(finished.truckid()) +
                           " delivered all packages, located at (" +
                           std::to_string(finished.x()) + "," +
                           std::to_string(finished.y()) + ")",
                       std::to_string(finished.seqnum()));
    }
  }
  return 0;
}
/*
 * delivery_handler
 *
 * when truck makes one delivery,
 * we will handle UDeliveryMade message
 * update the db
 *
 * return 0 if succeed, else -1
 */
int WorldBridge::delivery_handler(UPS::UResponses &msg,
                                  std::vector<int64_t> &seqnums) {
  for (int i = 0; i < msg.delivered_size(); i++) {
    UPS::UDeliveryMade delivery = msg.delivered(i);
    seqnums.push_back(delivery.seqnum());
    if (Zeus.docInSeqNum(std::to_string(delivery.seqnum()),
                         std::to_string(world_id)) == -1)
      continue;
    if (Zeus.updatePackageStatus(std::to_string(delivery.packageid()),
                                 "Delivered", std::to_string(world_id)) == -1)
      return -1;
    Homer.LogRecvMsg("World",
                     "truck" + std::to_string(delivery.truckid()) +
                         " delivered package " +
                         std::to_string(delivery.packageid()),
                     std::to_string(delivery.seqnum()));
  }
  return 0;
}

/*
 * ack_handler
 *
 * update request status in db
 * always return 0
 */
int WorldBridge::ack_handler(UPS::UResponses &msg) {
  for (int i = 0; i < msg.acks_size(); i++) {
    if (Zeus.rmOutSeqNum(std::to_string(msg.acks(i)),
                         std::to_string(world_id)) == -1)
      return -1;
    Homer.LogRecvMsg("World", "acking " + std::to_string(msg.acks(i)));
  }
  return 0;
}

/*
 * truck_handler
 *
 * update truck info inside db
 * fail to save info will return -1, succeed return 0
 */
int WorldBridge::truck_handler(UPS::UResponses &msg,
                               std::vector<int64_t> &seqnums) {
  for (int i = 0; i < msg.truckstatus_size(); i++) {
    UPS::UTruck truck = msg.truckstatus(i);
    std::cout << truck.truckid() << std::endl;
    seqnums.push_back(truck.seqnum());
    if (Zeus.docInSeqNum(std::to_string(truck.seqnum()),
                         std::to_string(world_id)) == -1)
      continue;
    if (Zeus.updateTruckStatus(std::to_string(truck.truckid()),
                               std::to_string(truck.x()),
                               std::to_string(truck.y()), truck.status(),
                               std::to_string(world_id)) == -1)
      return -1;
    Homer.LogRecvMsg("World",
                     "truck " + std::to_string(truck.truckid()) + " is " +
                         truck.status() + " ,located at(" +
                         std::to_string(truck.x()) + "," +
                         std::to_string(truck.y()) + ")",
                     std::to_string(truck.seqnum()));
  }
  return 0;
}

/*
 * error_handler
 *
 * log errmsg
 * return number of errors
 */
int WorldBridge::err_handler(UPS::UResponses &msg,
                             std::vector<int64_t> &seqnums) {
  int count = 0;
  for (int i = 0; i < msg.error_size(); i++) {
    ++count;
    UPS::UErr err = msg.error(i);
    seqnums.push_back(err.seqnum());
    if (Zeus.docInSeqNum(std::to_string(err.seqnum()),
                         std::to_string(world_id)) == -1)
      continue;
    Homer.LogRecvMsg("World",
                     "responding original seqnum " +
                         std::to_string(err.originseqnum()) + " " + err.err(),
                     std::to_string(err.seqnum()));
  }
  return count;
}

/*
int main() {
  WorldBridge wb("localhost", "12345");
  wb.ConnectToAWorld(1, true);
}
*/
