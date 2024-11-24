#include <chrono>

#include "api/server.hpp"

[[noreturn]] int main() {
  Server server("tcp://localhost:30200");
  server.start();

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
