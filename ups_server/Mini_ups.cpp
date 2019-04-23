#include "upserver.h"
std::atomic<bool> exit_thread_flag{false};
void listen_thread(UPServer &upserver);
void A_listen_thread(UPServer &upserver);
int main() {
  while (1) {

    try {
<<<<<<< HEAD
      std::cout << "in main\n";
      UPServer upserver("vcm-8950.vm.duke.edu", "12345", "10.197.40.0", "7890");

      // UPServer upserver("vcm-8129.vm.duke.edu", "12345", "10.197.193.1",
      // "80");

      // UPServer upserver("vcm-8129.vm.duke.edu", "12345", "10.197.193.1",
      // "80");

      // UPServer upserver("localhost", "12345", "localhost", "8080");
=======

      // UPServer upserver("vcm-8129.vm.duke.edu", "12345", "10.197.193.1",
      // "80");
      UPServer upserver("localhost", "12345", "localhost", "8080");
>>>>>>> 9997e1b5795d02c6c94d18dfda3ea7d18cf7b948
      // UPServer upserver("vcm-8950.vm.duke.edu", "12345", "10.197.40.0",
      // "7893");
      std::cout << "finish initialization\n";
      exit_thread_flag = false;
      std::thread t = std::thread(listen_thread, std::ref(upserver));
      std::thread t2 = std::thread(A_listen_thread, std::ref(upserver));

      t.join();
      t2.join();
    } catch (std::string &e) {
      continue;
    }
  }
<<<<<<< HEAD
  // upserver.test();
  // while (1)
  //;
=======
>>>>>>> 9997e1b5795d02c6c94d18dfda3ea7d18cf7b948
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
