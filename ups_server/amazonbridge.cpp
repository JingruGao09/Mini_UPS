#include "amazonbridge.h"

AmazonBridge::AmazonBridge(const char *hostname, const char *port)
    : ConAmazonClient(hostname, port) {}
AmazonBridge::~AmazonBridge() {}
int AmazonBridge::SendWorldId(const int &world_id){
  
}
