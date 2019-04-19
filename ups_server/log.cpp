#include "log.h"
void Log::save(const std::string &msg) {
  out.open("UPS.log", std::ios::out | std::ios::app);
  out << msg;
  out.close();
}
const std::string currentDateTime() {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
  // for more information about date/time format
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}
std::string now() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  char *time = std::ctime(&now_time);
  return std::string(time);
}
void Log::LogRecvMsg(std::string who, const std::string &what) {

  std::string msg = "[" + currentDateTime() + "] " + "Received message from  " +
                    who + " about " + what + "\n";
  save(msg);
}

void Log::LogSendMsg(std::string who, const std::string &what) {
  std::string msg = "[" + currentDateTime() + "] " + "Sent message to " + who +
                    " about " + what + "\n";
  save(msg);
}
