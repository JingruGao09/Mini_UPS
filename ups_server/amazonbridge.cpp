#include "amazonbridge.h"

AmazonBridge::AmazonBridge(const char *hostname, const char *port)
    : world_id(-1), ConAmazonClient(hostname, port) {
  Homer.LogSendMsg("Amazon", "connected to amazon");
}
AmazonBridge::~AmazonBridge() {}

int AmazonBridge::setWid(const int64_t &wid) {
  world_id = wid;
  return 0;
}
/*
 * Send World Id to Amazon
 * Send msg to inform Amazon world to connect
 * If success return 0, else, return -1
 *
 */
int AmazonBridge::SendWorldId() {
  UA::UACommands command;
  UA::InitWorld *msg;
  int64_t seqnum;
  msg = command.add_worlds();
  msg->set_worldid(world_id);
  if ((seqnum = Zeus.AfetchOutSeqNum()) == -1)
    return -1;
  msg->set_seqnum(seqnum);
  Homer.LogSendMsg("Amazon",
                   "please connecting to world " + std::to_string(world_id),
                   std::to_string(seqnum));
  return ConAmazonClient.sendMsg<UA::UACommands>(command);
}

/*
 * sendTruckid
 *
 * tell amazon, which truck is coming
 *
 * if success return 0, else, return -1
 */
int AmazonBridge::SendTruckId(std::vector<truck_location> &trucks) {
  UA::UACommands command;
  UA::DetermineTruck *detertrucks;
  int64_t seqnum;
  detertrucks = command.add_trucks();
  if ((seqnum = Zeus.AfetchOutSeqNum()) == -1)
    return -1;
  detertrucks->set_seqnum(seqnum);
  UA::TruckLocation *trucklocation;
  for (auto truck : trucks) {
    trucklocation = detertrucks->add_arrivedtrucks();
    trucklocation->set_truckid(truck.truck_id);
    trucklocation->set_wh_x(truck.wh_x);
    trucklocation->set_wh_y(truck.wh_y);
    Homer.LogSendMsg(
        "Amazon", "sending truck " + std::to_string(truck.truck_id) +
                      " to warehouse located at(" + std::to_string(truck.wh_x) +
                      "," + std::to_string(truck.wh_y) + ")");
  }
  return ConAmazonClient.sendMsg<UA::UACommands>(command);
}

/*
 * SendPackageId
 *
 * tell amazon, the package is out for delivery
 *
 * return -1 if fail, else 0
 */
int AmazonBridge::SendPackageId(std::vector<int64_t> &package_ids) {
  UA::UACommands command;
  UA::SettleShipment *shipments;
  int64_t seqnum;
  shipments = command.add_settled();
  if ((seqnum = Zeus.AfetchOutSeqNum()) == -1)
    return -1;
  shipments->set_seqnum(seqnum);
  for (auto package_id : package_ids) {
    shipments->add_packageid(package_id);
    Homer.LogSendMsg("Amazon",
                     "package " + std::to_string(package_id) +
                         " is out for delivery",
                     std::to_string(seqnum));
  }
  return ConAmazonClient.sendMsg<UA::UACommands>(command);
}

/*
 * FinishShipment
 *
 * Tell Amazon, package is delivered
 *
 * return -1 if fail, else 0
 */
int AmazonBridge::FinishShipment(std::vector<int64_t> &package_ids) {
  UA::UACommands command;
  UA::FinishShipment *finished;
  int64_t seqnum;
  finished = command.add_finished();
  if ((seqnum = Zeus.AfetchOutSeqNum()) == -1)
    return -1;
  finished->set_seqnum(seqnum);
  for (auto package_id : package_ids) {
    finished->add_packageid(package_id);
    Homer.LogSendMsg("Amazon",
                     "package " + std::to_string(package_id) + " is delivered",
                     std::to_string(seqnum));
  }
  return ConAmazonClient.sendMsg<UA::UACommands>(command);
}

/*
 * ack
 * send ack info to server
 *
 * return 0 if succeed, else -1
 */
int AmazonBridge::ack(const std::vector<int64_t> &seqnum) {
  UA::UACommands command;
  for (unsigned long i = 0; i < seqnum.size(); i++) {
    command.add_ack(seqnum[i]);
    Homer.LogSendMsg("Amazon", "acking " + std::to_string(seqnum[i]));
  }
  return ConAmazonClient.sendMsg<UA::UACommands>(command);
}
/*
 * ParseResponses
 *
 * handle all messages from amazon
 *
 * error return -1, else 0
 */
int AmazonBridge::ParseResponses(UA::AUCommands &msg,
                                 std::vector<warehouse_info> &warehouse_infos,
                                 std::vector<truck_dest> &truck_dsts) {
  std::vector<int64_t> seqnums;
  if (determinewarehouse_handler(msg, seqnums, warehouse_infos) == -1)
    return -1;

  if (determinedst_handler(msg, seqnums, truck_dsts) == -1)
    return -1;
  ack_handler(msg);
  if (ack(seqnums) == -1)
    return -1;
  return 0;
}
/*
 * determinewarehouse_handler
 *
 * parse warehouse destination
 *
 * if error, return -1, else 0
 */
int AmazonBridge::determinewarehouse_handler(
    UA::AUCommands &msg, std::vector<int64_t> &seqnums,
    std::vector<warehouse_info> &warehouse_infos) {
  for (int i = 0; i < msg.warehouses_size(); i++) {
    UA::DetermineWarehouse warehouse = msg.warehouses(i);
    seqnums.push_back(warehouse.seqnum());
    if (Zeus.AdocInSeqNum(std::to_string(warehouse.seqnum())) == -1)
      continue;
    warehouse_infos.push_back(
        {warehouse.whid(), warehouse.wh_x(), warehouse.wh_y()});
    Homer.LogRecvMsg("Amazon", "requesting a truck(s) to warehouse " +
                                   std::to_string(warehouse.whid()) +
                                   " ,located at (" +
                                   std::to_string(warehouse.wh_x()) + ", " +
                                   std::to_string(warehouse.wh_y()) + ")");
    if (apackageinfo_handler(warehouse) != 0)
      return -1;
  }
  return 0;
}

/*
 * apackageinfo_handler
 *
 * check all package info and store them into database
 *
 * return 0 if succeed, else -1
 */
int AmazonBridge::apackageinfo_handler(UA::DetermineWarehouse &msg) {
  for (int i = 0; i < msg.packageinfos_size(); i++) {
    UA::APackageInfo pack_info = msg.packageinfos(i);
    Homer.LogRecvMsg("Amazon",
                     "package: " + std::to_string(pack_info.packageid()) +
                         " x " + std::to_string(pack_info.count()) + ": " +
                         pack_info.description() + ", desctination: (" +
                         std::to_string(pack_info.x()) + "," +
                         std::to_string(pack_info.y()) + ")");
    if (Zeus.createPackage(
            std::to_string(pack_info.packageid()),
            std::to_string(pack_info.x()), std::to_string(pack_info.y()),
            pack_info.description(), std::to_string(pack_info.count()),
            "created", std::to_string(world_id)) == -1)
      return -1;
  }
  return 0;
}

/*
 * truckdst_handler
 *
 * receive the info about sending which truck to send which package to which
 * place
 *
 * if succeed return 0, else return -1
 *
 */
int AmazonBridge::truckdst_handler(UA::DetermineDst &msg,
                                   std::vector<truck_dest> &truck_dsts) {
  for (int i = 0; i < msg.leavingtrucks_size(); i++) {
    UA::TruckDst truckdst = msg.leavingtrucks(i);
    truck_dsts.push_back({truckdst.truckid(), truckdst.packageid()});
    Homer.LogRecvMsg("Amazon", "truck " + std::to_string(truckdst.truckid()) +
                                   " should send package " +
                                   std::to_string(truckdst.packageid()));
  }
  return 0;
}
/*
 * determinedst_handler
 *
 * parse truck-package-dst info
 *
 * return 0 if succeed, else -1
 */
int AmazonBridge::determinedst_handler(UA::AUCommands &msg,
                                       std::vector<int64_t> &seqnums,
                                       std::vector<truck_dest> &truck_dsts) {
  for (int i = 0; i < msg.dests_size(); i++) {
    UA::DetermineDst destination = msg.dests(i);
    seqnums.push_back(destination.seqnum());
    if (Zeus.AdocInSeqNum(std::to_string(destination.seqnum())) == -1)
      continue;
    if (truckdst_handler(destination, truck_dsts) != 0)
      return -1;
  }
  return 0;
}

/*
 * ack_handler
 *
 * update request status in db
 * always return 0
 * pass test
 */
int AmazonBridge::ack_handler(UA::AUCommands &msg) {
  for (int i = 0; i < msg.ack_size(); i++) {
    if (Zeus.ArmOutSeqNum(std::to_string(msg.ack(i))) == -1)
      return -1;
    Homer.LogRecvMsg("Amazon", "acking " + std::to_string(msg.ack(i)));
  }
  return 0;
}
