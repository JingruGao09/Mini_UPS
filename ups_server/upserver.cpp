#include "upserver.h"
#include <iostream>
UPServer::UPServer(const char *h, const char *p) : wb(h, p) {
  ConnectWorld();
  wb.SetWorldOptions(SIMSPEED);
}
/* ConnectWorld
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
  // for (int i = 0; i < 200; i++) {
  wb.Query(1);
  // }

  return 0;
}
void MsgHandler_thread(WorldBridge &wb, UPS::UResponses response) {
  std::vector<truck_t> trucks;
  if (wb.ParseResponses(response, trucks) == -1)
    return;
  if (!trucks.empty()) {
    // tell amazon truck info
  }
}
int UPServer::WorldMsgHandler() {
  UPS::UResponses response;
  wb.RecvMsg<UPS::UResponses>(response);
  std::thread t = std::thread(MsgHandler_thread, std::ref(wb), response);
  t.detach();
  // std::vector<truck_t> trucks;
  // wb.ParseResponses(response, trucks);
  return 0;
}
void listen_thread(UPServer &upserver) {
  try {
    while (1) {
      upserver.WorldMsgHandler();
    }
  } catch (std::string &e) {
    return;
  }
}

int main() {
  UPServer upserver("localhost", "12345");
  std::cout << "finish initialization\n";
  std::thread t = std::thread(listen_thread, std::ref(upserver));
  t.detach();
  upserver.test();
  while (1)
    ;
}
