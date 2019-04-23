#include "upserver.h"
#include <iostream>
UPServer::UPServer(const char *h, const char *p, const char *a_h,
                   const char *a_p)
    : wb(h, p), ab(a_h, a_p) {
  ConnectWorld();
  wb.SetWorldOptions(SIMSPEED);
  ab.setWid(wid);
  ab.SendWorldId();
  std::cout << "sent world id " << wid << " to amazon\n";
}
UPServer::~UPServer() { wb.DisconnectAWorld(); }
/* ConnectWorld
 * This function will automatically connect to a world,
 * if we already have a world, then connect to it.
 * if there is no world, then it will ask for one, and init trucks inside
 * anything fail, it will throw exception
 *
 * pass test, it will not fail
 */
void UPServer::ConnectWorld() {

  // get world id from db, if no valid wid, request one from server
  if ((wid = Zeus.getWorldNum()) == -1) {
    std::vector<truck_t> trucks;
    wb.RequireANewWorld(trucks);
    UPS::UConnected response;
    wb.RecvMsg<UPS::UConnected>(response);
    wid = response.worldid();
    Homer.LogRecvMsg("World", response.result());
    if (response.result() != "connected!")
      throw std::string("failed to connect!");
    Zeus.updateWorldNum(std::to_string(wid));
    wb.setWid(wid);
    for (auto truck : trucks) {
      if (Zeus.createTruck(std::to_string(truck.truck_id),
                           std::to_string(truck.x), std::to_string(truck.y),
                           std::to_string(wid)) == -1)
        return;
    }
  } else { // connect to world
    if (wb.ConnectToAWorld(wid) == -1)
      throw std::string("failed to send msg");
    UPS::UConnected response;
    wb.RecvMsg<UPS::UConnected>(response);
    if (wb.ParseConnectWorldInfo(response) == -1)
      throw std::string("failed to connect world");
  }
}
int UPServer::test() {
  // for (int i = 0; i < 200; i++) {
  wb.Query(1);
  // }

  return 0;
}
void MsgHandler_thread(WorldBridge &wb, AmazonBridge &ab,
                       UPS::UResponses response) {
  std::vector<truck_t> trucks;
  std::vector<int64_t> packageids;
  if (wb.ParseResponses(response, trucks, packageids) == -1)
    return;
  if (!trucks.empty()) {
    std::vector<truck_location> truck_locations;
    for (auto truck : trucks) {
      truck_locations.push_back({truck.truck_id, truck.x, truck.y});
    }
    ab.SendTruckId(truck_locations);
  }
  if (!packageids.empty()) {
    ab.FinishShipment(packageids);
  }
}

void A_MsgHandler_thread(AmazonBridge &ab, WorldBridge &wb,
                         UA::AUCommands response) {
  std::vector<warehouse_info> whs;
  std::vector<truck_dest> truck_dsts;
  if (ab.ParseResponses(response, whs, truck_dsts) == -1)
    return;
  if (!whs.empty()) {
    // assign truck to wh
    for (auto wh : whs) {
      wb.GoPickUp(wh.wh_id, wh.wh_x, wh.wh_y, wh.package_ids);
    }
  }
  if (!truck_dsts.empty()) {
    // tell truck to destination
    std::vector<int64_t> packageids;
    for (auto t : truck_dsts) {
      wb.GoDeliver(t.truck_id, t.package_id);
      packageids.push_back(t.package_id);
    }
    ab.SendPackageId(packageids);
  }
}
int UPServer::WorldMsgHandler() {
  UPS::UResponses response;
  wb.RecvMsg<UPS::UResponses>(response);
  std::thread t =
      std::thread(MsgHandler_thread, std::ref(wb), std::ref(ab), response);
  t.detach();
  // std::vector<truck_t> trucks;
  // wb.ParseResponses(response, trucks);
  return 0;
}
int UPServer::AmazonMsgHandler() {
  UA::AUCommands response;
  ab.RecvMsg<UA::AUCommands>(response);
  std::thread t =
      std::thread(A_MsgHandler_thread, std::ref(ab), std::ref(wb), response);
  t.detach();
  return 0;
}
