#include "upserver.h"
void listen_thread(UPServer &upserver);
void A_listen_thread(UPServer &upserver);
int main() {
  while (1) {
    try {
      UPServer upserver("vcm-8950.vm.duke.edu", "12345", "10.197.40.0", "7890");
      // UPServer upserver("localhost", "12345", "localhost", "8080");
      // UPServer upserver("vcm-5475.vm.duke.edu", "12345", "10.197.40.0",
      // "8080");
      std::cout << "finish initialization\n";
      std::thread t = std::thread(listen_thread, std::ref(upserver));
      // t.detach();
      std::thread t2 = std::thread(A_listen_thread, std::ref(upserver));
      // t2.detach();

      t.join();
      t2.join();
    } catch (std::string &e) {
      continue;
    }
  }
  // upserver.test();
  while (1)
    ;
}

void listen_thread(UPServer &upserver) {
  try {
    while (1) {
      upserver.WorldMsgHandler();
    }
  } catch (std::string &e) {
    return;
  }
}

void A_listen_thread(UPServer &upserver) {
  try {
    while (1) {
      upserver.AmazonMsgHandler();
    }
  } catch (std::string &e) {
    return;
  }
}
