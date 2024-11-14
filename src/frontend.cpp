#include <iostream>

#include "api/client.hpp"

int main() {
  std::cout << "Frontend Hello, World!" << std::endl;

  Client client("tcp://localhost:30200");
  client.start();

  return 0;
}
