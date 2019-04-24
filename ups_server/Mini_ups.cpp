#include "upserver.h"
#include "webridge.h"
std::atomic<bool> exit_thread_flag{false};
void listen_thread(UPServer &upserver);
void A_listen_thread(UPServer &upserver);
int main() {
  while (1) {
    try {
      // UPServer upserver("vcm-9320.vm.duke.edu", "12345", "10.197.40.0",
      // "7893");

      UPServer upserver("vcm-8129.vm.duke.edu", "12345", "10.197.193.1",
                        "34343");
      // UPServer upserver(argv[1], argv[2], argv[3], argv[4]);
      // UPServer upserver("vcm-8129.vm.duke.edu", "12345", "10.197.193.1",
      // "80");
      // UPServer upserver("vcm-9448.vm.duke.edu", "12345", "10.197.40.0",
      // "7893");
      std::cout << "finish initialization\n";
      exit_thread_flag = false;
      std::thread t = std::thread(listen_thread, std::ref(upserver));
      std::thread t2 = std::thread(A_listen_thread, std::ref(upserver));

      t.join();
      t2.join();
      continue;
    } catch (std::string &e) {
      continue;
    }
  }
}

void listen_thread(UPServer &upserver) {
  while (!exit_thread_flag) {
    try {
      upserver.WorldMsgHandler();
    } catch (std::string &e) {
      for (int i = 0; i < 500; i++) {
        if (upserver.World_reconnect() == 0) {
          std::cout << "reconnect successfully\n";
          continue;
        }
      }
      exit_thread_flag = true;
      std::cout << e << std::endl;
      return;
    }
  }
}

void A_listen_thread(UPServer &upserver) {
  while (!exit_thread_flag) {
    try {
      upserver.AmazonMsgHandler();
    } catch (std::string &e) {
      for (int i = 0; i < 500; i++) {
        if (upserver.Amazon_reconnect() == 0) {
          std::cout << "reconnect successfully\n";
          continue;
        }
      }
      exit_thread_flag = true;
      std::cout << e << std::endl;
      return;
    }
  }
}

void web_handler(WeBridge &wb, UPServer &upserver) {
  std::vector<char> msg = wb.recv();
  int id = wb.getTruckId(msg);
  upserver.Query(id);
}

void Web_listen_thread(UPServer &upserver) {

  while (1) {
    WeBridge wb("8080");
    wb.accptNewConn();
    std::thread t = std::thread(web_handler, std::ref(wb), std::ref(upserver));
    t.detach();
  }
}
