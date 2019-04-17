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

int AmazonBridge::SendTruckId(const int &truck_id, const int64_t &seqnum) {
  UA::DetermineTruck msg;
  UA::TruckLocation arrivedtrucks;
  msg.set_seqnum(seqnum);
  return SendMsg<UA::DetermineTruck>(msg)
}

int AmazonBridge::SendPackageId() {}
