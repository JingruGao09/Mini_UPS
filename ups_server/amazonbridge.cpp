#include "amazonbridge.h"

AmazonBridge::AmazonBridge(const char *hostname, const char *port)
    : ConAmazonClient(hostname, port) {}
AmazonBridge::~AmazonBridge() {}

/*
 * Send World Id to Amazon
 * Send msg to inform Amazon world to connect
 * If success return 0, else, return -1
 */
int AmazonBridge::SendWorldId(const int &world_id){
  UA::InitWorld msg;
  msg.set_worldid(world_id);
  msg.set_seqnum(1);
  return SendMsg<UA::InitWorld>(msg);
}

int AmazonBridge::SendTruckId(){

}

int AmazonBridge::SendPackageId(){

}
