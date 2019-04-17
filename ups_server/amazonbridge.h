#ifndef __AMAZONBRIDGE_H__
#define __AMAZONBRIDGE_H__
#include "client.h"
#include "dbinterface.h"
#include "server.h"
#include "ups_amazon.pb.h"
#include <iostream>
#include <string>
#define MAX_CHARACTER 1024
// client will do connection and garbage collection

struct _truck_location {
  int truck_id;
  int wh_id;
};
struct _package_info {
  int package_id;
  char description[MAX_CHARACTER];
  int count;
  int ship_id;
};

typedef struct _truck_location truck_location;
typedef struct _package_info package_info;

class AmazonBridge {
private:
  int world_id;
  std::string errmsg;
  Client ConAmazonClient;
  Server UpsServer;

  /* SendMsg
   * easy way to send google protocol message, return 0 if success
   * else return -1, check errmsg to find some idea
   */
  template <typename T> int SendMsg(T &msg) {
    std::vector<char> buf;
    if (msgToCharArray<T>(msg, buf) == -1)
      return -1;
    if (ConAmazonClient.sendData(buf) == -1) {
      errmsg = ConAmazonClient.getError();
      return -1;
    }
    return 0;
  }
  int CreateTruckLocation(const int &truck_id, const int &wh_id,
                          UA::DetermineTruck &msg);
  UA::PackageInfo CreatePackageInfo(const int64_t &package_id,
                                    const string &description, const int &count,
                                    const int64_t &ship_id);

public:
  AmazonBridge(const char *hostname, const char *port);
  ~AmazonBridge();
  int SendWorldId(const int &world_id, const int64_t &seqnum);
  int SendTruckId(const int64_t &seqnum);
  int SendPackageId();
};
#endif
