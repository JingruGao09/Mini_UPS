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
pqxx::result DBInterface::lookup(const std::string &sql) {
  pqxx::nontransaction N(*C);
  pqxx::result R(N.exec(sql));
  return R;
}
int DBInterface::getWorldNum() {
  std::string sql =
      "SELECT WORLD_ID FROM WORLD WHERE STATUS='OPEN' ORDER BY WORLD_ID ASC";
  pqxx::result R = lookup(sql);
  if (R.empty())
    return -1;
  auto c = R.begin();
  return c["WORLD_ID"].as<int>();
}
int DBInterface::updateWorldNum(const std::string &WORLD_ID) {
  try {
    std::string sql = "INSERT INTO WORLD(WORLD_ID) VALUES(" + WORLD_ID + ");";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
int DBInterface::getArrivedTruck(const int &WH_x, const int &WH_y) {
  std::string sql =
      "SELECT TRUCK_ID FROM TRUCK WHERE STATUS='ARRIVE WAREHOUSE' AND X=" +
      std::to_string(WH_x) + " AND Y=" + std::to_string(WH_y) + " LIMIT 1;";
  pqxx::result R = lookup(sql);
  if (R.empty()) {
    return -1;
  }
  auto c = R.begin();
  return c["TRUCK_ID"].as<int>();
}
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
int DBInterface::getIdleTruck(const int &WH_x, const int &WH_y) {
  std::string sql = "SELECT TRUCK_ID, X, Y FROM TRUCK WHERE STATUS='IDLE';";
  pqxx::result R = lookup(sql);
  if (R.empty()) {
    return -1;
  }
  return findNearestTruck(R, WH_x, WH_y);
}

int DBInterface::getDeliveringTruck(const int &WH_x, const int &WH_y) {
  std::string sql =
      "SELECT TRUCK_ID, X, Y FROM TRUCK WHERE STATUS='DELIVERING'";
  pqxx::result R = lookup(sql);
  if (R.empty()) {
    return -1;
  }
  return findNearestTruck(R, WH_x, WH_y);
  // return findNearestnBestDestTruck(R);
}

int DBInterface::updateTruckStatus(const std::string &truck_id,
                                   const std::string &x, const std::string &y,
                                   std::string &status) {
  try {
    std::string sql = "UPDATE TRUCK SET X=" + x + " , Y=" + y + " ,STATUS='" +
                      status + "' WHERE TRUCK_ID=" + truck_id + ";";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

int DBInterface::createTruck(const std::string &truck_id, const std::string &x,
                             const std::string &y) {
  try {
    std::string sql = "INSERT INTO TRUCK(TRUCK_ID, X, Y) VALUES(" + truck_id +
                      "," + x + "," + y + ");";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
