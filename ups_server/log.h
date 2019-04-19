#ifndef __LOG_H__
#define __LOG_H__
#include <chrono>
#include <ctime>
#include <fstream>
class Log {
private:
  std::ofstream out;
  void save(const std::string &msg);

public:
  Log();
  ~Log();
  void LogRecvMsg(std::string who, const std::string &what);
  void LogSendMsg(std::string who, const std::string &wha);
};
#endif
