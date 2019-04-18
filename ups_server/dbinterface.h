#ifndef __DBINTERFACE_H__
#define __DBINTERFACE_H__
#include "helper.h"
#include <limits>
#include <pqxx/pqxx>
#include <string>
class DBInterface {
private:
  std::string errmsg;
  std::unique_ptr<pqxx::connection> C;
  int execute(const std::string &sql);
  /*
   * execute and return
   *
   * execute sql and return required value in one transaction
   *
   *
   */
  template <typename T> T execute_and_return(const std::string &sql) {
    pqxx::work W(*C);
    try {
      auto v = W.exec(sql);
      W.commit();
      pqxx::result R(v);
      auto c = R.begin();
      return c[0].as<T>();
    } catch (const std::exception &e) {
      W.abort();
      throw std::string("Database error");
      return -1;
    }
  }
  pqxx::result lookup(const std::string &sql);
  int lookupTruck(const std::string &sql);

public:
  DBInterface();
  ~DBInterface();
  int getWorldNum();
  int updateWorldNum(const std::string &WORLD_ID);
  int getArrivedTruck(const int &WH_x, const int &WH_y,
                      const std::string &WORLD_id);
  int getIdleTruck(const int &WH_x, const int &WH_y,
                   const std::string &WORLD_id);
  int getDeliveringTruck(const int &WH_x, const int &WH_y,
                         const std::string &WORLD_id);
  int updateTruckStatus(const std::string &truck_id, const std::string &x,
                        const std::string &y, std::string status,
                        const std::string &WORLD_id);
  int createTruck(const std::string &truck_id, const std::string &x,
                  const std::string &y, const std::string &WORLD_id);
  int createPackage(const std::string &package_id, const std::string &truck_id,
                    const std::string &x, const std::string &y,
                    std::string status, const std::string &WORLD_id);
  int updatePackageStatus(const std::string &package_id, std::string status,
                          const std::string &WORLD_id);
  int docInSeqNum(const std::string &seqnum);
  int docOutMsg(const std::string &seqnum, const std::string &msg);
  int64_t fetchSeqNum();
  int rmOutSeqNum(const std::string &seqnum);
};
#endif
