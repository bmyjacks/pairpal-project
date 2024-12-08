#include <chrono>
#include <server.hpp>

[[noreturn]] auto main() -> int {
  Server server("tcp://localhost:57880");
  server.start();

  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}
