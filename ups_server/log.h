#ifndef __LOG_H__
#define __LOG_H__
#include "helper.h"
#include <chrono>
#include <ctime>
#include <fstream>
class Log {
private:
  std::ofstream out;
  void save(const std::string &msg);

public:
  void LogRecvMsg(std::string who, const std::string &what,
                  const std::string &seqnum = "");
  void LogSendMsg(std::string who, const std::string &what,
                  const std::string &seqnum = "");
};
#endif
