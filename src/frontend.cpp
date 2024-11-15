#include <iostream>

#include "api/client.hpp"

int main() {
  std::cout << "Frontend Hello, World!" << std::endl;

  Client client("tcp://localhost:30200");
  client.start();

  for (int i = 0; i <= 100; ++i) {
    std::cout << std::format("user{}", i) << std::endl;
    client.addUser(std::format("user{}", i), "password");
  }

  return 0;
}
