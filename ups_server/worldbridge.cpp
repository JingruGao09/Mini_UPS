#include "worldbridge.h"
#include <iostream>
WorldBridge ::WorldBridge(const char *hostname, const char *port)
    : world_id(-1), Hermes(hostname, port) {}
WorldBridge::~WorldBridge() {}

/*
 * RequireANewWorld
 *
 * Send msg to require a new world id
 * if success return 0, else, return -1
 * pass test
 */
int WorldBridge::RequireANewWorld(std::vector<truck_t> &trucks) {
  UPS::UConnect msg;
  if (CreateTrucks(TRUCK_NUM, &msg, trucks) == -1) {
    Homer.LogRecvMsg("System", "failed to create truck");
    return -1;
  }
  msg.set_isamazon(false);
  Homer.LogSendMsg("World", "Requesting a new world");
  return Hermes.sendMsg<UPS::UConnect>(msg);
}

void WorldBridge::setWid(const int64_t &wid) { world_id = wid; }
/* ConnectToAWorld
 *
 * Connect to a simulate world.
 * if it is a new world, set initruck as true
 * send success return 0, else return -1
 * pass test
 */
int WorldBridge::ConnectToAWorld(const int64_t &wid) {
  world_id = wid;
  UPS::UConnect msg;
  msg.set_worldid(world_id);
  msg.set_isamazon(false);
  Homer.LogSendMsg("World", "Connecting to world " + std::to_string(wid));
  return Hermes.sendMsg<UPS::UConnect>(msg);
}

int WorldBridge::DisconnectAWorld() {
  UPS::UCommands command;
  command.set_disconnect(true);
  Homer.LogSendMsg("World", "diconnect from world");
  return Hermes.sendMsg<UPS::UCommands>(command);
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
  Homer.LogRecvMsg("System", "failed to connect world");
  return -1;
}
/*
 * CreateTrucks
 *
 * send message to world let it randomly create trucks, save into db
 * if failed to save, return -1, succeed,return 0
 * pass test
 */
int WorldBridge::CreateTrucks(int truckNum, UPS::UConnect *msg,
                              std::vector<truck_t> &trucks) {
  UPS::UInitTruck *truck;

  for (int i = 0; i < truckNum; i++) {
    truck = msg->add_trucks();
    truck->set_id(i);
    int x = rand() % 100 - 50;
    int y = rand() % 100 - 50;
    truck->set_x(x);
    truck->set_y(y);
    trucks.push_back({i, x, y});
  }
  return 0;
}

/*
 * selectAtruck
 *
 * first check whether there is a truck at this wh
 * then pick the nearest idle truck
 * last pick the nearest delivering truck
 *
 * if success return truck_id, else return -1
 */
int WorldBridge::selectATruck(const int &wh_x, const int &wh_y) {
  int truck_id = -1;
  truck_id = Zeus.getArrivedTruck(wh_x, wh_y, std::to_string(world_id));
  if (truck_id != -1)
    return truck_id;
  truck_id = Zeus.getIdleTruck(wh_x, wh_y, std::to_string(world_id));
  if (truck_id != -1)
    return truck_id;
  return Zeus.getDeliveringTruck(wh_x, wh_y, std::to_string(world_id));
}
int WorldBridge::ReSendMsg() {
  std::vector<resend_msg_t> msgs = Zeus.getDatedOutMsg(world_id);
  for (auto msg : msgs) {
    if (msg.type == GOPICKUP) {
      resendGoPickUp(msg.wh_id, msg.truck_id, msg.seqnum);
    } else if (msg.type == GODELIVER) {
      resendGoDeliver(msg.truck_id, msg.package_id, msg.package_x,
                      msg.package_y, msg.seqnum);
    } else if (msg.type == QUERY) {
      resendQuery(msg.truck_id, msg.seqnum);
    }
  }
  return 0;
}
int WorldBridge::resendGoPickUp(const int &wh_id, const int &truck_id,
                                const int &seqnum) {
  UPS::UCommands command;
  UPS::UGoPickup *pickup;

  pickup = command.add_pickups();
  pickup->set_whid(wh_id);
  pickup->set_truckid(truck_id);
  pickup->set_seqnum(seqnum);
  Homer.LogSendMsg("World",
                   "resending truck " + std::to_string(truck_id) +
                       " to warehouse " + std::to_string(wh_id),
                   std::to_string(seqnum));
  Zeus.updateOutMsgDate(std::to_string(seqnum), std::to_string(world_id));
  return Hermes.sendMsg<UPS::UCommands>(command);
}
/*
 * GOPickUp
 *
 * Sent message to world let truck to the wharehouse
 * after use this function, query to get truck info
 * return 0 if succeed, else -1
 *
 */
int WorldBridge::GoPickUp(const int &wh_id, const int &wh_x, const int &wh_y,
                          const std::vector<int> &package_ids) {
  ReSendMsg();
  UPS::UCommands command;
  UPS::UGoPickup *pickup;
  resend_msg_t msg;
  msg.type = GOPICKUP;
  int64_t seqnum;
  int truck_id = selectATruck(wh_x, wh_y);
  if (truck_id == -1) {
    Homer.LogRecvMsg("system", "no truck can go to warehouse(" +
                                   std::to_string(wh_x) + "," +
                                   std::to_string(wh_y) + ")");
    return -1;
  }
  pickup = command.add_pickups();
  pickup->set_whid(wh_id);
  pickup->set_truckid(truck_id);
  if ((seqnum = Zeus.fetchSeqNum(std::to_string(world_id))) == -1) {
    Homer.LogRecvMsg("System", "failed to fetch seq num");
    return -1;
  }
  pickup->set_seqnum(seqnum);
  Homer.LogSendMsg("World",
                   "sending truck " + std::to_string(truck_id) +
                       " to warehouse (" + std::to_string(wh_x) + "," +
                       std::to_string(wh_y) + ")",
                   std::to_string(seqnum));
  for (auto packageid : package_ids)
    Zeus.updatePackageStatus(
        std::to_string(packageid), std::to_string(truck_id),
        "truck en route to warehouse", std::to_string(world_id));
  // save msg to db
  msg.truck_id = truck_id;
  msg.wh_id = wh_id;
  msg.package_id = 0;
  msg.package_x = 0;
  msg.package_y = 0;
  Zeus.docOutMsg(std::to_string(seqnum), msg, std::to_string(world_id));
  return Hermes.sendMsg<UPS::UCommands>(command);
}

/*
 * SetWorldOptions
 *
 * set the speed of world
 * pass test
 */
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
int WorldBridge::SetPackageInfo(const int &truck_id, package_t &package,
                                UPS::UGoDeliver *goDeliver) {
  UPS::UDeliveryLocation *location;
  location = goDeliver->add_packages();
  location->set_packageid(package.package_id);
  location->set_x(package.x);
  location->set_y(package.y);
  if (Zeus.updatePackageStatus(std::to_string(package.package_id),
                               std::to_string(truck_id), "out for delivery",
                               std::to_string(world_id)) == -1) {
    Homer.LogRecvMsg("System", "failed to SetPackageInfo");
    return -1;
  }
  Homer.LogSendMsg("World", "package " + std::to_string(package.package_id) +
                                " on truck " + std::to_string(truck_id));

  return 0;
}
int WorldBridge::resendGoDeliver(const int &truck_id, const int &package_id,
                                 const int &package_x, const int &package_y,
                                 const int &seqnum) {
  UPS::UCommands command;
  UPS::UGoDeliver *goDeliver;

  goDeliver = command.add_deliveries();
  goDeliver->set_truckid(truck_id);
  package_t package;
  package.package_id = package_id;
  package.x = package_x;
  package.y = package_y;
  if (SetPackageInfo(truck_id, package, goDeliver) == -1)
    return -1;
  goDeliver->set_seqnum(seqnum);
  Homer.LogSendMsg("World",
                   "sending truck " + std::to_string(truck_id) +
                       " to deliver package " + std::to_string(package_id) +
                       ", destination(" + std::to_string(package_x) + "," +
                       std::to_string(package_y) + ")",
                   std::to_string(seqnum));
  Zeus.updateOutMsgDate(std::to_string(seqnum), std::to_string(world_id));
  return Hermes.sendMsg<UPS::UCommands>(command);
}

/*
 * GODeliver
 *
 * Sent message to world let truck to deliver package
 * after using this function, please query
 * return 0 if succeed, else -1
 *
 */
int WorldBridge::GoDeliver(const int &truck_id, const int &package_id) {
  ReSendMsg();
  UPS::UCommands command;
  UPS::UGoDeliver *goDeliver;
  resend_msg_t msg;
  msg.type = GODELIVER;

  int64_t seqnum;
  package_t package = Zeus.getPackageInfo(package_id);

  goDeliver = command.add_deliveries();
  goDeliver->set_truckid(truck_id);
  if (SetPackageInfo(truck_id, package, goDeliver) == -1)
    return -1;
  if ((seqnum = Zeus.fetchSeqNum(std::to_string(world_id))) == -1) {
    Homer.LogRecvMsg("System", "failed to fetch seq num");
    return -1;
  }
  goDeliver->set_seqnum(seqnum);
  // save msg to db
  msg.wh_id = 0;
  msg.truck_id = truck_id;
  msg.package_id = package.package_id;
  msg.package_x = package.x;
  msg.package_y = package.y;
  Zeus.docOutMsg(std::to_string(seqnum), msg, std::to_string(world_id));
  Homer.LogSendMsg(
      "World",
      "sending truck " + std::to_string(truck_id) + " to deliver package " +
          std::to_string(package.package_id) + ", destination(" +
          std::to_string(package.x) + "," + std::to_string(package.y) + ")",
      std::to_string(seqnum));
  return Hermes.sendMsg<UPS::UCommands>(command);
}
int WorldBridge::resendQuery(const int &truck_id, const int &seqnum) {
  UPS::UCommands command;
  UPS::UQuery *query;

  query = command.add_queries();
  query->set_truckid(truck_id);
  query->set_seqnum(seqnum);
  Homer.LogSendMsg("World",
                   "requerying status of truck " + std::to_string(truck_id),
                   std::to_string(seqnum));
  Zeus.updateOutMsgDate(std::to_string(seqnum), std::to_string(world_id));
  return Hermes.sendMsg<UPS::UCommands>(command);
}
int WorldBridge::Query(const int &truck_id) {
  ReSendMsg();
  UPS::UCommands command;
  UPS::UQuery *query;
  int64_t seqnum;
  resend_msg_t msg;
  msg.type = QUERY;
  query = command.add_queries();
  query->set_truckid(truck_id);
  if ((seqnum = Zeus.fetchSeqNum(std::to_string(world_id))) == -1) {
    Homer.LogRecvMsg("System", "failed to fetch seq num");
    return -1;
  }
  query->set_seqnum(seqnum);
  // save msg to db
  msg.truck_id = truck_id;
  msg.wh_id = 0;
  msg.package_id = 0;
  msg.package_x = 0;
  msg.package_y = 0;
  Zeus.docOutMsg(std::to_string(seqnum), msg, std::to_string(world_id));
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
    if (Zeus.docInSeqNum(std::to_string(seqnums[i]),
                         std::to_string(world_id)) == -1)
      continue;
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
                                std::vector<truck_t> &trucks,
                                std::vector<int64_t> &packageids) {
  std::vector<int64_t> seqnums;
  if (msg.has_finished() && msg.finished())
    return 1;
  if (finished_handler(msg, trucks, seqnums) == -1)
    return -1;
  if (delivery_handler(msg, seqnums, packageids) == -1)
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
    if (Zeus.lookupInSeqNum(std::to_string(finished.seqnum()),
                            std::to_string(world_id)) == 0)
      continue;
    if (Zeus.updateTruckStatus(std::to_string(finished.truckid()),
                               std::to_string(finished.x()),
                               std::to_string(finished.y()), finished.status(),
                               std::to_string(world_id))) {
      Homer.LogRecvMsg("System", "failed to update TruckStatus");
      return -1;
    }

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
                                  std::vector<int64_t> &seqnums,
                                  std::vector<int64_t> &packageids) {
  for (int i = 0; i < msg.delivered_size(); i++) {
    UPS::UDeliveryMade delivery = msg.delivered(i);
    seqnums.push_back(delivery.seqnum());
    packageids.push_back(delivery.packageid());
    if (Zeus.lookupInSeqNum(std::to_string(delivery.seqnum()),
                            std::to_string(world_id)) == 0)
      continue;
    if (Zeus.updatePackageStatus(std::to_string(delivery.packageid()),
                                 "Delivered", std::to_string(world_id)) == -1) {
      Homer.LogRecvMsg("System", "failed to updatePackageStatus");
      return -1;
    }
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
 * when world ack our request, we should remove out seqnum from db
 * to indicate it is complete
 * always return 0
 * pass test
 */
int WorldBridge::ack_handler(UPS::UResponses &msg) {
  for (int i = 0; i < msg.acks_size(); i++) {
    if (Zeus.rmOutSeqNum(std::to_string(msg.acks(i)),
                         std::to_string(world_id)) == -1)
      Homer.LogRecvMsg("System", "failed to rmOutSeqNum");
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
 * pass test
 */
int WorldBridge::truck_handler(UPS::UResponses &msg,
                               std::vector<int64_t> &seqnums) {
  for (int i = 0; i < msg.truckstatus_size(); i++) {
    UPS::UTruck truck = msg.truckstatus(i);
    std::cout << truck.truckid() << std::endl;
    seqnums.push_back(truck.seqnum());
    if (Zeus.lookupInSeqNum(std::to_string(truck.seqnum()),
                            std::to_string(world_id)) == 0)
      continue;
    if (Zeus.updateTruckStatus(std::to_string(truck.truckid()),
                               std::to_string(truck.x()),
                               std::to_string(truck.y()), truck.status(),
                               std::to_string(world_id)) == -1) {
      Homer.LogRecvMsg("System", "failed to updateTruckStatus");
      return -1;
    }
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
    if (Zeus.lookupInSeqNum(std::to_string(err.seqnum()),
                            std::to_string(world_id)) == 0)
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
