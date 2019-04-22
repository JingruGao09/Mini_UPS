#include "upserver.h"
void listen_thread(UPServer &upserver);
void A_listen_thread(UPServer &upserver);
int main() {
  while (1) {
    UPServer upserver("vcm-8129.vm.duke.edu", "12345", "10.197.193.1", "80");
    std::cout << "finish initialization\n";
    std::thread t = std::thread(listen_thread, std::ref(upserver));
    // t.detach();
    std::thread t2 = std::thread(A_listen_thread, std::ref(upserver));
    // t2.detach();

    t.join();
    t2.join();
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