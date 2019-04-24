#include "log.h"
void Log::save(const std::string &msg) {
  out.open("UPS.log", std::ios::out | std::ios::app);
  out << msg;
  out.close();
}
std::string now() {
  auto now = std::chrono::system_clock::now();
  std::time_t now_time = std::chrono::system_clock::to_time_t(now);
  char *time = std::ctime(&now_time);
  return std::string(time);
}
void Log::LogRecvMsg(std::string who, const std::string &what,
                     const std::string &seqnum) {

  std::string msg =
      "[" + currentDateTime() + "] " + "Received message from " + who;
  if (!seqnum.empty())
    msg += " seqnum is " + seqnum;
  msg += ", about " + what + "\n";
  save(msg);
}

void Log::LogSendMsg(std::string who, const std::string &what,
                     const std::string &seqnum) {
  std::string msg = "[" + currentDateTime() + "] " + "Sent message to " + who;
  if (!seqnum.empty())
    msg += " seqnum is " + seqnum;
  msg += ", about " + what + "\n";
  save(msg);
}
