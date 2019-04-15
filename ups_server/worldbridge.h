#ifndef __WORLDBRIDGE_H__
#define __WORLDBRIDGE_H__
#include "world_ups.pb.h"
#include <iostream>
#include <string>
class WorldBridge {
private:
public:
  int RequireANewWorld();
  int ConnectToAWolrd();
  int CreateTrucks(int truckNum);
  int GoPickUp();
  int GoDeliver();
};
#endif
