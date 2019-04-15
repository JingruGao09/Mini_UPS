#include "dbinterface.h"

DBInterface::DBInterface() {
  // Allocate & initialize a Postgres connection object

  // Establish a connection to the database
  // Parameters: database name, user name, user password
  C = std::unique_ptr<pqxx::connection>(
      new pqxx::connection("dbname=EXCHANGE user=postgres password=passw0rd"));
  if (C->is_open()) {
    //  cout << "Opened database successfully: " << C->dbname() << endl;
  } else {
    throw std::string("Fail to open db");
  }
}

DBInterface::~DBInterface() { C->disconnect(); }

/*
 * execute sql
 *
 * return 0 if success, else -1
 */
int DBInterface::execute(const std::string &sql) {
  pqxx::work W(*C);
  try {
    W.exec(sql);
    W.commit();
  } catch (const std::exception &e) {
    W.abort();
    throw std::string("Database error");
    return -1;
  }
  return 0;
}
/*
 * execute and return
 *
 * execute sql and return required value in one transaction
 *
 *
 */
int DBInterface::execute_and_return(const std::string &sql) {
  pqxx::work W(*C);
  try {
    auto v = W.exec(sql);
    W.commit();
    pqxx::result R(v);
    auto c = R.begin();
    return c[0].as<int>();
  } catch (const std::exception &e) {
    W.abort();
    throw std::string("Database error");
    return -1;
  }
}
/*
 * lookup
 *
 * use the given sql to look up info in the db
 * return any result
 */

pqxx::result DBInterface::lookup(const std::string &sql) {
  pqxx::nontransaction N(*C);
  pqxx::result R(N.exec(sql));
  return R;
}
/*
 * getWorldNum
 *
 * get a usable world number from db
 * succeed return world id, else -1
 */
int DBInterface::getWorldNum() {
  std::string sql =
      "SELECT WORLD_ID FROM WORLD WHERE STATUS='OPEN' ORDER BY WORLD_ID ASC";
  pqxx::result R = lookup(sql);
  if (R.empty())
    return -1;
  auto c = R.begin();
  return c["WORLD_ID"].as<int>();
}
/*
 * updateWorldNum
 *
 * store newly feteched world number into db
 * succeed return 0, else -1
 */
int DBInterface::updateWorldNum(const std::string &WORLD_ID) {
  try {
    std::string sql = "INSERT INTO WORLD(WORLD_ID) VALUES(" + WORLD_ID + ");";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
/*
 * getArrivedTruck
 *
 * assign a truck which status is arrive warehouse
 * to the warehouse
 * succeed return truck_id, else return -1
 *
 */
int DBInterface::getArrivedTruck(const int &WH_x, const int &WH_y,
                                 const std::string &WORLD_id) {
  std::string sql = "SELECT TRUCK_ID FROM TRUCK WHERE STATUS='ARRIVE "
                    "WAREHOUSE' AND WORLD_ID=" +
                    WORLD_id + " AND X=" + std::to_string(WH_x) +
                    " AND Y=" + std::to_string(WH_y) + " LIMIT 1;";
  pqxx::result R = lookup(sql);
  if (R.empty()) {
    return -1;
  }
  auto c = R.begin();
  return c["TRUCK_ID"].as<int>();
}
/*
 * findNearestTruck
 *
 * find the truck having smallest l2 distance to warehouse
 * succeed return truck_id, else return -1
 */
int findNearestTruck(pqxx::result R, const int &WH_x, const int &WH_y) {
  float min_dist = MAXFLOAT;
  int min_truck = -1;
  for (auto c : R) {
    int truck = c["TRUCK_ID"].as<int>();
    int truck_x = c["X"].as<int>();
    int truck_y = c["Y"].as<int>();
    float dist = getDist<int, float>(truck_x, truck_y, WH_x, WH_y);
    if (dist < min_dist) {
      min_dist = dist;
      min_truck = truck;
    }
  }
  return min_truck;
}
/*
 * getIdleTruck
 *
 * assign a truck which status is Idle
 * to the warehouse
 * succeed return truck_id, else return -1
 *
 */
int DBInterface::getIdleTruck(const int &WH_x, const int &WH_y,
                              const std::string &WORLD_id) {
  std::string sql =
      "SELECT TRUCK_ID, X, Y FROM TRUCK WHERE STATUS='IDLE' AND WORLD_ID=" +
      WORLD_id + ";";
  pqxx::result R = lookup(sql);
  if (R.empty()) {
    return -1;
  }
  return findNearestTruck(R, WH_x, WH_y);
}
/*
 * getDeliveringTruck
 *
 * assign a truck which status is delivering
 * to the warehouse
 * succeed return truck_id, else return -1
 *
 */
int DBInterface::getDeliveringTruck(const int &WH_x, const int &WH_y,
                                    const std::string &WORLD_id) {
  std::string sql = "SELECT TRUCK_ID, X, Y FROM TRUCK WHERE "
                    "STATUS='DELIVERING' AND WORLD_ID=" +
                    WORLD_id + ";";
  pqxx::result R = lookup(sql);
  if (R.empty()) {
    return -1;
  }
  return findNearestTruck(R, WH_x, WH_y);
  // return findNearestnBestDestTruck(R);
}

/*
 * updateTruckStatus
 *
 * update truck status and location,
 * succeed return 0, else -1
 *
 */
int DBInterface::updateTruckStatus(const std::string &truck_id,
                                   const std::string &x, const std::string &y,
                                   std::string &status,
                                   const std::string &WORLD_id) {
  try {
    std::string sql = "UPDATE TRUCK SET X=" + x + " , Y=" + y + " ,STATUS='" +
                      status + "' WHERE TRUCK_ID=" + truck_id +
                      " AND WORLD_ID=" + WORLD_id + ";";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
/*
 * createTruck
 *
 * save given truck data into db,
 * succeed return 0, else -1
 *
 */
int DBInterface::createTruck(const std::string &truck_id, const std::string &x,
                             const std::string &y,
                             const std::string &WORLD_id) {
  try {
    std::string sql = "INSERT INTO TRUCK(TRUCK_ID, X, Y, WORLD_ID) VALUES(" +
                      truck_id + "," + x + "," + y + "," + WORLD_id + ");";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
