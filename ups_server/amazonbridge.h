#ifndef __AMAZONBRIDGE_H__
#define __AMAZONBRIDGE_H__
#include "client.h"
#include "dbinterface.h"
#include "server.h"
#include "ups_amazon.pb.h"
#include <iostream>
#include <string>
//#define MAX_CHARACTER 1024
// client will do connection and garbage collection

struct _truck_location {
  int truck_id;
  int wh_id;
};
struct _package_info {
  int package_id;
  std::string description;
  int count;
  int ship_id;
};

typedef struct _truck_location truck_location;
typedef struct _package_info package_info;

class AmazonBridge {
private:
  int world_id;
  // std::string errmsg;
  Client ConAmazonClient;
  // Server UpsServer;
  DBInterface Zeus;
  /*
  int CreateTruckLocation(const int &truck_id, const int &wh_id,
                          UA::DetermineTruck &msg);
  UA::PackageInfo CreatePackageInfo(const int64_t &package_id,
                                    const string &description, const int &count,
                                    const int64_t &ship_id);
  UA::TruckLocation CreateTruckLocation(const int &truck_id, const int &wh_id,
                                        UA::DetermineTruck &msg);
  */
public:
  AmazonBridge(const char *hostname, const char *port);
  ~AmazonBridge();
  int SendWorldId();
  int SendTruckId(std::vector<truck_location> &trucks);
  int SendPackageId(std::vector<package_info> &packages);
};
#endif
