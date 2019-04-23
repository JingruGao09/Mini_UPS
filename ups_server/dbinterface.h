#ifndef __DBINTERFACE_H__
#define __DBINTERFACE_H__
#include "helper.h"
#include <limits>
#include <mutex>
#include <pqxx/pqxx>
#include <string>
#define GOPICKUP 1
#define GODELIVER 2
#define QUERY 3
struct _resend_msg_t {
  int seqnum;
  int type;
  int truck_id;
  int wh_id;
  int package_id;
  int package_x;
  int package_y;
};
typedef struct _resend_msg_t resend_msg_t;
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
  int initializer();
  package_t getPackageInfo(const int &packageid);
  std::vector<int> getPackageId(const int &truck_id, const int &wh_x,
                                const int &wh_y, const int &worldid);
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
  int updateTruckStatus(const std::string &truck_id, std::string status,
                        const std::string &WORLD_id);
  int createTruck(const std::string &truck_id, const std::string &x,
                  const std::string &y, const std::string &WORLD_id);
  int createPackage(const std::string &package_id, const std::string &dep_x,
                    const std::string &dep_y, const std::string &des_x,
                    const std::string &des_y, const std::string &desc,
                    const std::string &count, std::string status,
                    const std::string &WORLD_id,
                    const std::string &upsaccount = "0");
  int updatePackageStatus(const std::string &package_id,
                          const std::string &truck_id, std::string status,
                          const std::string &WORLD_id);
  int updatePackageStatus(const std::string &package_id,
                          const std::string status,
                          const std::string &WORLD_id);
  int lookupInSeqNum(const std::string &seqnum, const std::string &WORLD_id);
  int docInSeqNum(const std::string &seqnum, const std::string &WORLD_id);
  int docOutMsg(const std::string &seqnum, const resend_msg_t &msg,
                const std::string &WORLD_id);
  int64_t fetchSeqNum(const std::string &WORLD_id);
  int rmOutSeqNum(const std::string &seqnum, const std::string &WORLD_id);
  std::vector<resend_msg_t> getDatedOutMsg(const int64_t &world_id);
  int updateOutMsgDate(const std::string &seqnum, const std::string &WORLD_id);
  int64_t AfetchOutSeqNum();
  int ArmOutSeqNum(const std::string &seqnum);
  int AdocOutMsg(const std::string &seqnum, const std::string &msg);
  int AdocInSeqNum(const std::string &seqnum);
};
#endif
