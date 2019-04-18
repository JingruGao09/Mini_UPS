#include "upserver.h"

UPServer::UPServer(const char *h, const char *p) : wb(h, p) { ConnectWorld(); }

/*
 * ConnectWorld
 * This function will automatically connect to a world,
 * if we already have a world, then connect to it.
 * if there is no world, then it will ask for one, and init trucks inside
 * anything fail, it will throw exception
 *
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

int main() { UPServer upserver("localhost", "12345"); }
