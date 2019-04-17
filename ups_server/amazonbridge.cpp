#include "amazonbridge.h"

AmazonBridge::AmazonBridge(const char *hostname, const char *port)
    : world_id(-1), ConAmazonClient(hostname, port) {}
AmazonBridge::~AmazonBridge() {}

/*
 * Send World Id to Amazon
 * Send msg to inform Amazon world to connect
 * If success return 0, else, return -1
 */
int AmazonBridge::SendWorldId(const int &world_id, const int64_t &seqnum) {
  UA::InitWorld msg;
  msg.set_worldid(world_id);
  msg.set_seqnum(seqnum);
  return SendMsg<UA::InitWorld>(msg);
}
/*
void init_truck_location(){

}
*/

int AmazonBridge::CreateTruckLocation(const int &truck_id, const int &wh_id,
                                      UA::DetermineTruck &msg) {
  UA::TruckLocation *arrivedtrucks;
  arrivedtrucks = msg.add_arrivedtrucks();
  arrivedtrucks->set_truckid(truck_id);
  arrivedtrucks->set_whid(wh_id);
  // I should update this in database 'table truck'(only truck_id & wh_id are
  // required in this stage) maybe we can add world_id as well, and set the
  // truck status to '2' if success, return 0 if fail, return -1
  return 0;
}

int AmazonBridge::SendTruckId(const int64_t &seqnum) {
  UA::DetermineTruck msg;
  UA::TruckLocation *arrivedtruck;
  arrivedtruck = msg.add_arrivedtrucks();
  msg.set_seqnum(seqnum);
  return SendMsg<UA::DetermineTruck>(msg)
}

UA::PackageInfo AmazonBridge::CreatePackageInfo(const int64_t &package_id,
                                                const string &description,
                                                const int &count,
                                                const int64_t &ship_id) {
  UA::PackageInfo msg;
  msg.set_packageid(package_id);
  msg.set_description(description);
  msg.set_count(count);
  msg.set_shipid(ship_id);
  return msg;
}

int AmazonBridge::SendPackageId(const int64_t &seqnum) {
  UA::SettleShipment msg;
  UA::PackageInfo *package;
  package = msg.add_packages();
  msg.set_seqnum(seqnum);
  return SendMsg<UA::SettleShipment>(msg);
}
