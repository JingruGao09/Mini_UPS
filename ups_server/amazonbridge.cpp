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
  UPS_AMAZON::InitWorld msg;
  msg.set_worldid(5);
  msg.set_seqnum(1);
  return SendMsg<UPS_AMAZON::InitWorld>(msg);
}


