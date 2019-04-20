#include "amazonbridge.h"

AmazonBridge::AmazonBridge(const char *hostname, const char *port)
    : world_id(-1), ConAmazonClient(hostname, port) {}
AmazonBridge::~AmazonBridge() {}

/*
 * Send World Id to Amazon
 * Send msg to inform Amazon world to connect
 * If success return 0, else, return -1
 */
int AmazonBridge::SendWorldId() {
  UA::UCommands command;
  UA::InitWorld *msg;
  int64_t seqnum;
  msg->set_worldid(world_id);
  if ((seqnum = Zeus.AfetchOutSeqNum()) == -1)
    return -1;
  msg->set_seqnum(seqnum);
  Homer.LogSendMsg("Amazon", "InitWorld " + std::to_string(seqnum));
  return ConAmazonClient.sendMsg<UA::UCommands>(command);
}

int AmazonBridge::SendTruckId(std::vector<truck_location> &trucks) {
  UA::UCommands command;
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
    trucklocation->set_whid(truck.wh_id);
    Homer.LogSendMsg("Amazon",
                     "sending truck id " + std::to_string(truck.truck_id) +
                         " to warehouse " + std::to_string(truck.wh_id));
  }
  return ConAmazonClient.sendMsg<UA::UCommands>(command);
}

int AmazonBridge::SendPackageId(std::vector<int64_t> &package_ids) {
  UA::UCommands command;
  UA::SettleShipment *shipments;
  int64_t seqnum;
  shipments = command.add_settled();
  if ((seqnum = Zeus.AfetchOutSeqNum()) == -1)
    return -1;
  shipments->set_seqnum(seqnum);
  for (auto package_id : package_ids) {
    shipments->set_packageid(package_id);
    Homer.LogSendMsg("Amazon", "sending settleshipment, package_id is " +
                                   std::to_string(package_id) + "seqnum is " +
                                   std::to_string(seqnum));
  }
  return ConAmazonClient.sendMsg<UA::UCommands>(command);
}

int AmazonBridge::FinishShipment(std::vector<int64_t> &package_ids) {
  UA::UCommands command;
  UA::FinishShipment *finished;
  int64_t seqnum;
  finished = command.add_finished();
  if ((seqnum = Zeus.AfetchOutSeqNum()) == -1)
    return -1;
  finished->set_seqnum(seqnum);
  for (auto package_id : package_ids) {
    finished->set_packageid(package_id);
    Homer.LogSendMsg("Amazon", "sending finishshipment, package_id is " +
                                   std::to_string(package_id) + "seqnum is " +
                                   std::to_string(seqnum));
  }
  return ConAmazonClient.sendMsg<UA::UCommands>(command);
}

/*
 * ack
 * send ack info to server
 *
 * return 0 if succeed, else -1
 */
int AmazonBridge::ack(const std::vector<int64_t> &seqnum) {
  UA::UCommands command;
  for (unsigned long i = 0; i < seqnums.size(); i++) {
    command.add_acks(seqnum[i]);
    Homer.LogSendMsg("Amazon", "acking " + std::to_string(seqnum[i]));
  }
  return ConAmazonClient.sendMsg<UA::UCommands>(command);
}

int AmazonBridege::ParseResponses(UA::AUCommands &msg,
                                  std::vector<package_info> &package_infos,
                                  std::vector<warehouse_info> &warehouse_infos,
                                  std::vector<truck_dest> &truck_dsts) {
  std::vector<int64_t> seqnums;
  if (determinewarehouse_handler(msg, seqnums, warehouse_infos,
                                 package_infos) == -1)
    return -1;

  if (determinedst_handler(msg, seqnums, truck_dsts) == -1)
    return -1;

  if (ack(seqnums) == -1)
    return -1;
  return 0;
}
int AmazonBridge::apackageinfo_handler(
    UA::WarehouseInfo &warehouseinfo,
    std::vector<package_info> &package_infos) {
  for (int i = 0; i < msg.packageinfos_size(); i++) {
    UA::APackageInfo apackageinfo = msg.packageinfos(i);
    package_infos.push_back({apackageinfo.packageid(),
                             apackageinfo.description(), apackageinfo.count()});
    Homer.LogRecvMsg("Amazon", "package detail " +
                                   std::to_string(apackageinfo.packageid()) +
                                   " " + apackageinfo.description() + " " +
                                   std::to_string(apackageinfo.count()));
  }
  return 0;
  // May need to create package here ???
}
int AmazonBridge::warehouseinfo_handler(
    UA::DetermineWarehouse &deterwarehouse,
    std::vector<warehouse_info> &warehouse_infos,
    std::vector<package_info> &package_infos) {
  for (int i = 0; i < msg.warehouses_size(); i++) {
    UA::WarehouseInfo warehouseinfo = msg.warehouses(i);
    warehouse_infos.push_back(
        {warehouseinfo.whid(), warehouseinfo.wh_x(), warehouseinfo.wh_y()});
    Homer.LogRecvMsg(
        "Amazon", "warehouse detail " + std::to_string(warehouseinfo.whid()) +
                      " location " + std::to_string(warehouseinfo.wh_x()) +
                      " " + std::to_string(warehouseinfo.wh_y()));
    if (apackageinfo_handler(warehouseinfo, package_infos) != 0)
      return -1;
  }
  return 0;
  // may need to update warehouse info in TABLE truck here???
}
int AmazonBridge::determinewarehouse_handler(
    UA::AUCommands &msg, std::vector<int64_t> &seqnums,
    std::vector<warehouse_info> &warehouse_infos,
    std::vector<package_info> &package_infos) {
  for (int i = 0; i < msg.warehouses_size(); i++) {
    UA::DetermineWarehouse deterwarehouse = msg.warehouses(i);
    seqnums.push_back(deterwarehouse.seqnum());
    if (Zeus.AdocInSeqNum(std::to_string(deterwarehouse.seqnum())) == -1)
      continue;
    Homer.LogRecvMsg("Amazon", "determine warehouse with seqnum " +
                                   std::to_string(deterwarehouse.seqnum()));
    if (warehouseinfo_handler(deterwarehouse, warehouse_infos, package_infos) !=
        0)
      return -1;
  }
  return 0;
  // may need to update sth in table here???
}

int AmazonBridge::truckdst_handler(UA::DetermineDst &msg,
                                   std::vector<truck_dest> &truck_dsts) {
  for (int i = 0; i < msg.leavingtrucks_size(); i++) {
    UA::TruckDst truckdst = msg.leavingtrucks(i);
    truck_dsts.push_back(
        {truckdst.truckid(), truckdst.x(), truckdst.y(), truckdst.packageid()});
    Homer.LogRecvMsg("Amazon",
                     "leaving truck detail is " +
                         std::to_string(truckdst.truckid()),
                     " dest " + std::to_string(truckdst.x()) + " " +
                         std::to_string(truckdst.y()) + " " +
                         std::to_string(truckdst.packageid()));
    // may need to update db TABLE 'package' here
  }
  return 0;
}
int AmazonBridge::determinedst_handler(UA::AUCommands &msg,
                                       std::vector<int64_t> &seqnums,
                                       std::vector<truck_dest> &truck_dsts) {
  for (int i = 0; i < msg.dests_size(); i++) {
    UA::DetermineDst destination = msg.dests(i);
    seqnums.push_back(destination.seqnum());
    if (Zeus.AdocInSeqNum(std::to_string(destination.seqnum())) == -1)
      continue;
    Homer.LogRecvMsg("Amazon", "leaving trucks with seqnum " +
                                   std::to_string(destination.seqnum()));
    if (truckdst_handler(destination, truck_dsts) != 0)
      return -1;
  }
  return 0;
}
int AmazonBridge::ack_handler(UA::AUCommands &msg) {
  for (int i = 0; i < msg.ack_size(); i++) {
    if (Zeus.ArmOutSeqNum(std::to_string(msg.acks(i)) == -1))
      return -1;
    Homer.LogRecvMsg("Amazon", "acking " + std::to_string(msg.acks(i)));
  }
  return 0;
}

/*
 *Recving and parsing the mesg
 *
 *
 */
int AmazonBridge::warehouse_handler(UA::ACommands &msg,
                                    std::vector<int64_t> &seqnums) {
  for (int i = 0; i < msg.warehouses_size(); i++) {
    UA::DetermineWarehouse warehouse = msg.warehouses(i);
    seqnums.push_back(warehouse.seqnum());
    if (Zeus.AdocInSeqNum(std::to_string(warehouse.seqnum()))
      continue;
    if ()
  }
  return 0;
}

/*
int main() {
  AmazonBridge ab("vcm-7989.vm.duke.edu", "12345");
  ab.SendWorldId();
  }*/
