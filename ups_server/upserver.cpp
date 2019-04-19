#include "upserver.h"
UPServer::UPServer(const char *h, const char *p) : wb(h, p) {
  ConnectWorld();
  wb.SetWorldOptions(SIMSPEED);
}

/*
 * ConnectWorld
 * This function will automatically connect to a world,
 * if we already have a world, then connect to it.
 * if there is no world, then it will ask for one, and init trucks inside
 * anything fail, it will throw exception
 *
 * pass test, it will not fail
 */
void UPServer::ConnectWorld() {
  bool initTruck = false;

  // get world id from db, if no valid wid, request one from server
  if ((wid = Zeus.getWorldNum()) == -1) {
    wb.RequireANewWorld();
    UPS::UConnected response;
    wb.RecvMsg<UPS::UConnected>(response);
    wid = response.worldid();
    Zeus.updateWorldNum(std::to_string(wid));
    initTruck = true;
  }

  // connect to world
  if (wb.ConnectToAWorld(wid, initTruck) == -1)
    throw std::string("failed to send msg");
  UPS::UConnected response;
  wb.RecvMsg<UPS::UConnected>(response);
  if (wb.ParseConnectWorldInfo(response) == -1)
    throw std::string("failed to connect world");
}
int UPServer::test() {
  for (int i = 0; i < 200; i++) {
    wb.Query(i);
  }

  return 0;
}
int UPServer::WorldMsgHandler() {
  UPS::UResponses response;
  std::vector<truck_t> trucks;
  wb.RecvMsg<UPS::UResponses>(response);
  if (wb.ParseResponses(response, trucks) == -1)
    return -1;
  if (!trucks.empty()) {
    // tell amazon truck info
  }
  return 0;
}
void listen_func(UPServer &upserver) {
  while (1) {
    upserver.WorldMsgHandler();
  }
}
int main() {
  UPServer upserver("localhost", "12345");
  std::thread t(listen_func, std::ref(upserver));
  // upserver.test();
}
