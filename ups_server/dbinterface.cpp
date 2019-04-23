#include "dbinterface.h"
#include <iostream>
DBInterface::DBInterface() {
  // Allocate & initialize a Postgres connection object

  // Establish a connection to the database
  // Parameters: database name, user name, user password
  C = std::unique_ptr<pqxx::connection>(
      new pqxx::connection("dbname=UPS user=postgres "
                           "password=passw0rd port = 5432"));
  /*
      C = std::unique_ptr<pqxx::connection>(
      new pqxx::connection("host=db dbname=UPS user=postgres "
                           "password=passw0rd port = 5432"));

   */
  if (C->is_open()) {
    //  cout << "Opened database successfully: " << C->dbname() << endl;
  } else {
    throw std::string("Fail to open db");
  }
  if (initializer() == -1)
    throw std::string("Fail to initialize db");
}

DBInterface::~DBInterface() { C->disconnect(); }

/*
 * execute sql
 *
 * return 0 if success, else -1
 */
std::mutex mtx;
int DBInterface::execute(const std::string &sql) {
  pqxx::work W(*C);
  try {
    std::lock_guard<std::mutex> lck(mtx);
    W.exec(sql);
    W.commit();
    return 0;
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
 * pass test
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
 * pass test
 */
int DBInterface::updateWorldNum(const std::string &WORLD_ID) {
  try {
    std::string sql =
        "INSERT INTO WORLD(WORLD_ID,STATUS) VALUES(" + WORLD_ID + ", 'OPEN');";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

/*
 * getPackageId
 *
 * check which cargo is waiting to be collected
 *
 * return an array of package id, or empty
 */
std::vector<int> DBInterface::getPackageId(const int &truck_id, const int &wh_x,
                                           const int &wh_y,
                                           const int &worldid) {
  std::string sql = "SELECT PACKAGE_ID FROM PACKAGE WHERE PACKAGE_STATUS= "
                    "'TRUCK EN ROUTE TO WAREHOUSE' AND TRUCK_ID=" +
                    std::to_string(truck_id) +
                    " AND DEP_X=" + std::to_string(wh_x) +
                    " AND DEP_Y=" + std::to_string(wh_y) +
                    " AND WORLD_ID=" + std::to_string(worldid) + ";";
  pqxx::result R = lookup(sql);
  if (R.empty()) {
    return {};
  }
  std::vector<int> packageids;
  for (auto c : R) {
    packageids.push_back(c["PACKAGE_ID"].as<int>());
  }
  return packageids;
}

/*
 * getArrivedTruck
 *
 * assign a truck which status is arrive warehouse
 * to the warehouse
 * succeed return truck_id, else return -1
 * pass test
 */
int DBInterface::getArrivedTruck(const int &WH_x, const int &WH_y,
                                 const std::string &WORLD_id) {
  std::string sql = "SELECT TRUCK_ID FROM TRUCK WHERE TRUCK_STATUS='ARRIVE "
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
 * pass test
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
 * getPackageInfo
 *
 * use package id to query its destination
 *
 */
package_t DBInterface::getPackageInfo(const int &packageid) {
  package_t package;
  std::string sql = "SELECT DES_X, DES_Y FROM PACKAGE WHERE PACKAGE_ID=" +
                    std::to_string(packageid) + ";";
  pqxx::result R = lookup(sql);
  if (R.empty()) {
    package.package_id = -1;
    return package;
  }
  auto c = R.begin();
  package.package_id = packageid;
  package.x = c["DES_X"].as<int>();
  package.y = c["DES_Y"].as<int>();
  return package;
}
/*
 * getIdleTruck
 *
 * assign a truck which status is Idle
 * to the warehouse
 * succeed return truck_id, else return -1
 * pass test
 */
int DBInterface::getIdleTruck(const int &WH_x, const int &WH_y,
                              const std::string &WORLD_id) {
  std::string sql = "SELECT TRUCK_ID, X, Y FROM TRUCK WHERE "
                    "TRUCK_STATUS='IDLE' AND WORLD_ID=" +
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
 * pass test
 */
int DBInterface::getDeliveringTruck(const int &WH_x, const int &WH_y,
                                    const std::string &WORLD_id) {
  std::string sql = "SELECT TRUCK_ID, X, Y FROM TRUCK WHERE "
                    "TRUCK_STATUS='DELIVERING' AND WORLD_ID=" +
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
 * pass test
 */
int DBInterface::updateTruckStatus(const std::string &truck_id,
                                   const std::string &x, const std::string &y,
                                   std::string status,
                                   const std::string &WORLD_id) {
  try {
    std::string sql =
        "UPDATE TRUCK SET X=" + x + " , Y=" + y + " ,TRUCK_STATUS='" + status +
        "' WHERE TRUCK_ID=" + truck_id + " AND WORLD_ID=" + WORLD_id + ";";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

/*
 * createPackage
 *
 * create a new package
 *
 * succeed return 0, else return -1
 * pass test
 */
int DBInterface::createPackage(
    const std::string &package_id, const std::string &dep_x,
    const std::string &dep_y, const std::string &des_x,
    const std::string &des_y, const std::string &desc, const std::string &count,
    std::string status, const std::string &WORLD_id,
    const std::string &upsaccount) {
  try {
    std::string sql =
        "INSERT INTO PACKAGE(PACKAGE_ID,DEP_X,DEP_Y,DES_X, DES_Y, "
        "PACKAGE_STATUS,DESCP,COUNT,WORLD_ID";
    if (upsaccount != "0")
      sql += ",USER_ID";
    sql += ") VALUES(" + package_id + "," + dep_x + "," + dep_y + "," + des_x +
           "," + des_y + ",'" + status + "','" + desc + "'," + count + "," +
           WORLD_id;
    if (upsaccount != "0")
      sql += "," + upsaccount;
    sql += ");";
    /*std::string sql =
      "INSERT INTO PACKAGE(PACKAGE_ID,DEP_X,DEP_Y,DES_X, DES_Y, "
      "PACKAGE_STATUS,DESCP,COUNT,WORLD_ID";
  sql += ") VALUES(" + package_id + "," + dep_x + "," + dep_y + "," + des_x +
         "," + des_y + ",'" + status + "','" + desc + "'," + count + "," +
         WORLD_id;
         sql += ");";*/
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
/*
 * updatePackageStatus
 *
 * update the status and location of package
 *
 * return 0 if succeed, else -1
 * pass test
 */
int DBInterface::updatePackageStatus(const std::string &package_id,
                                     const std::string &truck_id,
                                     std::string status,
                                     const std::string &WORLD_id) {
  try {
    std::string sql = "UPDATE PACKAGE SET PACKAGE_STATUS='" + status +
                      "', TRUCK_ID=" + truck_id +
                      " WHERE PACKAGE_ID=" + package_id +
                      " AND WORLD_ID=" + WORLD_id + ";";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

/*
 * updatePackageStatus
 *
 * update the status and location of package
 *
 * return 0 if succeed, else -1
 * pass test
 */
int DBInterface::updatePackageStatus(const std::string &package_id,
                                     const std::string status,
                                     const std::string &WORLD_id) {
  try {
    std::string sql = "UPDATE PACKAGE SET PACKAGE_STATUS='" + status + "'" +
                      " WHERE PACKAGE_ID=" + package_id +
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
 * pass test
 */
int DBInterface::createTruck(const std::string &truck_id, const std::string &x,
                             const std::string &y,
                             const std::string &WORLD_id) {
  try {
    std::string sql = "INSERT INTO TRUCK(TRUCK_ID, X, Y, WORLD_ID) VALUES(" +
                      truck_id + "," + x + "," + y + "," + WORLD_id +
                      ") ON CONFLICT DO NOTHING;";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
int DBInterface::lookupInSeqNum(const std::string &seqnum,
                                const std::string &WORLD_id) {
  try {
    std::string sql = "SELECT * FROM INSEQNUM WHERE ID=" + seqnum +
                      " AND WORLD_ID=" + WORLD_id + ";";
    pqxx::result R = lookup(sql);
    if (R.empty())
      return -1;
    return 0;
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
/*
 * docInSeqNum
 *
 * add the seqnum into database
 *
 * return 0 if success, if exist return -1
 * pass test
 */
int DBInterface::docInSeqNum(const std::string &seqnum,
                             const std::string &WORLD_id) {
  try {
    std::string sql = "INSERT INTO INSEQNUM(ID,WORLD_ID) VALUES(" + seqnum +
                      "," + WORLD_id + ");";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

/*
 * docOutMsg
 *
 * add the outgoing msg into database to enable resend it
 *
 * if success return 0, else -1
 * pass test
 */
int DBInterface::docOutMsg(const std::string &seqnum, const resend_msg_t &msg,
                           const std::string &WORLD_id) {
  try {
    std::string sql = "UPDATE OUTSEQNUM SET TYPE=" + std::to_string(msg.type) +
                      ", TRUCK_ID=" + std::to_string(msg.truck_id) +
                      ", WH_ID=" + std::to_string(msg.wh_id) +
                      ",PACKAGE_ID=" + std::to_string(msg.package_id) +
                      ", PACKAGE_X=" + std::to_string(msg.package_x) +
                      ", PACKAGE_Y=" + std::to_string(msg.package_y) +
                      " WHERE ID=" + seqnum + " AND WORLD_ID=" + WORLD_id + ";";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

/*
 * getDatedOutMsg
 *
 * get all the msg which is out of dated, we need to resend them.
 *
 *
 * return an array of outdated msg
 *
 */
std::vector<resend_msg_t> DBInterface::getDatedOutMsg(const int64_t &world_id) {
  std::string sql =
      "SELECT *FROM OUTSEQNUM WHERE WORLD_ID=" + std::to_string(world_id) +
      "AND TIME+900 <" + std::to_string(unix_timestamp()) + ";";
  pqxx::result R = lookup(sql);
  if (R.empty())
    return {};
  std::vector<resend_msg_t> msg;
  for (auto C : R) {
    resend_msg_t m;
    m.seqnum = C["ID"].as<int>();
    m.type = C["TYPE"].as<int>();
    m.truck_id = C["TRUCK_ID"].as<int>();
    m.wh_id = C["WH_ID"].as<int>();
    m.package_id = C["PACKAGE_ID"].as<int>();
    m.package_x = C["PACKAGE_X"].as<int>();
    m.package_y = C["PACKAGE_Y"].as<int>();
    msg.push_back(m);
  }
  return msg;
}
/*
 * updateOutMsgDate
 *
 * This function update the time of unack out msg
 * return 0 if succeed, else -1
 */
int DBInterface::updateOutMsgDate(const std::string &seqnum,
                                  const std::string &WORLD_id) {
  try {
    std::string sql =
        "UPDATE OUTSEQNUM SET TIME=" + std::to_string(unix_timestamp()) +
        " WHERE ID=" + seqnum + " AND WORLD_ID=" + WORLD_id + ";";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
/*
 * fetchSeqNum
 *
 * generate a new seqnum
 *
 * return seqnum if success, else return -1;
 * pass test
 */
int64_t DBInterface::fetchSeqNum(const std::string &WORLD_id) {
  try {
    std::string sql = "INSERT INTO OUTSEQNUM (WORLD_ID,time) VALUES (" +
                      WORLD_id + "," + std::to_string(unix_timestamp()) +
                      ") RETURNING ID;";
    return execute_and_return<int64_t>(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

/*
 *
 * rmOutSeqNum
 *
 * rm the given seqnum in OUTSEQNUM to indicate it is finished
 *
 * return 0 if succeed , else -1
 * pass test
 */
int DBInterface::rmOutSeqNum(const std::string &seqnum,
                             const std::string &WORLD_id) {
  try {
    std::string sql = "DELETE FROM OUTSEQNUM WHERE ID=" + seqnum +
                      " AND WORLD_ID=" + WORLD_id + ";";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
int64_t DBInterface::AfetchOutSeqNum() {
  try {
    std::string sql = "INSERT INTO AOUTSEQNUM (MSG,TIME) VALUES (NULL," +
                      std::to_string(unix_timestamp()) + ") RETURNING ID;";
    return execute_and_return<int64_t>(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

int DBInterface::ArmOutSeqNum(const std::string &seqnum) {
  try {
    std::string sql = "DELETE FROM AOUTSEQNUM WHERE ID=" + seqnum + ";";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

int DBInterface::AdocOutMsg(const std::string &seqnum, const std::string &msg) {
  try {
    std::string sql =
        "UPDATE AOUTSEQNUM SET MSG='" + msg + "' WHERE ID=" + seqnum + ";";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}

int DBInterface::AdocInSeqNum(const std::string &seqnum) {
  try {
    std::string sql = "INSERT INTO AINSEQNUM(ID) VALUES(" + seqnum + ");";
    return execute(sql);
  } catch (std::string &e) {
    errmsg = e;
    return -1;
  }
}
/*
 * initializer
 *
 * initalize the db to create require tables
 *
 * pass test
 */
int DBInterface::initializer() {
  pqxx::work W(*C);
  try {
    std::string sql =
        "CREATE TABLE IF NOT EXISTS WORLD(WORLD_ID INT PRIMARY KEY NOT NULL, "
        "STATUS VARCHAR(10) NOT NULL);";
    W.exec(sql);
    sql =
        "CREATE TABLE IF NOT EXISTS INSEQNUM(ID BIGINT NOT NULL, WORLD_ID INT "
        "NOT NULL REFERENCES WORLD(WORLD_ID),PRIMARY KEY(ID, WORLD_ID));";
    W.exec(sql);
    sql = "CREATE TABLE IF NOT EXISTS OUTSEQNUM(ID BIGSERIAL NOT "
          "NULL,TYPE INT, TRUCK_ID INT, WH_ID INT,PACKAGE_ID INT,PACKAGE_X "
          "INT,PACKAGE_Y INT,WORLD_ID INT NOT NULL REFERENCES "
          "WORLD(WORLD_ID),TIME INT NOT NULL, "
          "PRIMARY KEY(ID, WORLD_ID));";
    W.exec(sql);

    sql =
        "CREATE TABLE IF NOT EXISTS AINSEQNUM(ID BIGINT PRIMARY KEY NOT NULL);";
    W.exec(sql);
    sql = "CREATE TABLE IF NOT EXISTS AOUTSEQNUM(ID BIGSERIAL NOT "
          "NULL PRIMARY KEY, MSG "
          "VARCHAR(65535),TIME INT NOT NULL);";
    W.exec(sql);
    sql = "CREATE TABLE IF NOT EXISTS TRUCK(TRUCK_ID INT NOT NULL, X INT NOT "
          "NULL, Y INT NOT NULL, WORLD_ID INT NOT NULL REFERENCES "
          "WORLD(WORLD_ID),TRUCK_STATUS VARCHAR(20) NOT NULL DEFAULT 'IDLE', "
          "PRIMARY KEY(TRUCK_ID, WORLD_ID));";
    W.exec(sql);
    sql = "CREATE TABLE IF NOT EXISTS PACKAGE(PACKAGE_ID BIGINT NOT NULL, "
          "WORLD_ID INT NOT NULL REFERENCES WORLD(WORLD_ID),TRUCK_ID INT "
          ",USER_ID INT NULL"
          ",PACKAGE_STATUS VARCHAR(50) NOT NULL "
          "DEFAULT 'CREATED', DEP_X INT NOT NULL, DEP_Y INT NOT NULL,DES_X INT "
          "NOT NULL, DES_Y INT NOT NULL, DESCP "
          "TEXT, COUNT INT ,PRIMARY "
          "KEY(PACKAGE_ID, WORLD_ID));";
    W.exec(sql);
    W.commit();
  } catch (const std::exception &e) {
    W.abort();
    return -1;
  }
  return 0;
}
