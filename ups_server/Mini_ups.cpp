#include "upserver.h"
#include <chrono>
#include <thread>
std::atomic<bool> exit_thread_flag{false};
void listen_thread(UPServer &upserver);
void A_listen_thread(UPServer &upserver);
void query_thread(UPServer &upserver);
int main() {
  while (1) {
    try {
      UPServer upserver("vcm-9229.vm.duke.edu", "12345", "10.197.40.0", "7893");

      std::cout << "finish initialization\n";
      exit_thread_flag = false;
      std::thread t = std::thread(listen_thread, std::ref(upserver));
      std::thread t2 = std::thread(A_listen_thread, std::ref(upserver));
      std::thread t3 = std::thread(query_thread, std::ref(upserver));

      t.join();
      t2.join();
      t3.join();
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

void query_thread(UPServer &upserver) {
  while (!exit_thread_flag) {
    try {
      upserver.Query();
      std::this_thread::sleep_for(std::chrono::minutes(1));
    } catch (std::string &e) {
      exit_thread_flag = true;
      std::cout << e << std::endl;
      return;
    }
  }
}
