#include "log.h"
void Log::save(const std::string &msg) { out << msg; }
std::string now() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  char *time = std::ctime(&now_time);
  return std::string(time);
}
void Log::LogRecvMsg(std::string who, const std::string &what) {

  std::string msg =
      "[" + now() + "] " + "Received message from  " + who + " about " + what;
  save(msg);
}

void Log::LogSendMsg(std::string who, const std::string &what) {
  std::string msg =
      "[" + now() + "] " + "Sent message to " + who + " about " + what;
  save(msg);
}

Log::Log() { out.open("UPS.log", std::ios::out | std::ios::app); }

Log::~Log() { out.close(); }
