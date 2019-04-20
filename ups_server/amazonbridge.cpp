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
  if ((seqnum = Zeus.fetchSeqNum(std::to_string(world_id))) == -1)
    return -1;
  msg->set_seqnum(seqnum);
  return ConAmazonClient.sendMsg<UA::UCommands>(command);
}

/*
UA::TruckLocation AmazonBridge::CreateTruckLocation(const int &truck_id,
                                                    const int &wh_id,
                                                    UA::DetermineTruck &msg) {
  UA::TruckLocation *arrivedtrucks;
  arrivedtrucks = msg.add_arrivedtrucks();
  arrivedtrucks->set_truckid(truck_id);
  arrivedtrucks->set_whid(wh_id);
  // I should update this in database 'table truck'(only truck_id & wh_id are
  // required in this stage) maybe we can add world_id as well, and set the
  // truck status to '2' if success, return 0 if fail, return -1
  return arrivedtrucks;
}
*/
int AmazonBridge::SendTruckId(std::vector<truck_location> &trucks) {
  UA::UCommands command;
  UA::DetermineTruck *detertrucks;
  int64_t seqnum;
  detertrucks = command.add_trucks();
  if ((seqnum = Zeus.fetchSeqNum(std::to_string(world_id))) == -1)
    return -1;
  detertrucks->set_seqnum(seqnum);
  UA::TruckLocation *trucklocation;
  for (auto truck : trucks) {
    trucklocation = detertrucks->add_arrivedtrucks();
    trucklocation->set_truckid(truck.truck_id);
    trucklocation->set_whid(truck.wh_id);
  }

  return ConAmazonClient.sendMsg<UA::UCommands>(command);
}
/*
UA::PackageInfo AmazonBridge::CreatePackageInfo(const int64_t &package_id,
                                                const string &description,
                                                const int &count,
                                                const int64_t &ship_id) {
  UA::PackageInfo package;
  msg.set_packageid(package_id);
  msg.set_description(description);
  msg.set_count(count);
  msg.set_shipid(ship_id);
  return package;
}
*/

int AmazonBridge::SendPackageId(std::vector<package_info> &packages) {
  UA::UCommands command;
  UA::SettleShipment *shipments;
  int64_t seqnum;
  shipments = command.add_shipments();
  if ((seqnum = Zeus.fetchSeqNum(std::to_string(world_id))) == -1)
    return -1;
  shipments->set_seqnum(seqnum);
  UA::PackageInfo *packageinfo;
  for (auto package : packages) {
    packageinfo = shipments->add_packages();
    packageinfo->set_packageid(package.package_id);
    packageinfo->set_description(package.description);
    packageinfo->set_count(package.count);
    packageinfo->set_shipid(package.ship_id);
  }
  return ConAmazonClient.sendMsg<UA::UCommands>(command);
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
    if (Zeus.docInSeqNum(std::to_string(warehouse.seqnum()),
                         std::to_string(world_id)) == -1)
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
