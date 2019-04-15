#include "worldbridge.h"

int WorldBridge::RequireANewWorld() {
  UPS::UConnect msg;
  msg.set_worldid(5);
  msg.set_isamazon(false);
  size_t size = msg.ByteSize();
  std::vector<char> sendMsg(size);

  msg.SerializeToArray(&sendMsg[0], size);
  std::cout << sendMsg.data() << std ::endl;
  return 0;
}

int main() {
  WorldBridge wb;
  wb.RequireANewWorld();
}
