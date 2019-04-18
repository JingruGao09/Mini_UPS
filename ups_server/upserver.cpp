#include "upserver.h"

UPServer::UPServer(const char *h, const char *p) : wb(h, p) { ConnectWorld(); }

void UPServer::ConnectWorld() {
  bool initTruck = false;
  if ((wid = Zeus.getWorldNum()) == -1) {
    wb.RequireANewWorld();
    std::vector<char> response = wb.RecvMsg();
    wid = wb.ParseWorldid(response);
    initTruck = true;
  }
  if (wb.ConnectToAWorld(wid, initTruck) == -1)
    throw std::string("failed to send msg");
  std::vector<char> response = wb.RecvMsg();
  if (wb.ParseConnectWorldInfo(response) == -1)
    throw std::string("failed to connect world");
}

int main() { UPServer upserver("localhost", "12345"); }
