#include "api/server.hpp"

int main() {
  Server server("tcp://localhost:30200");
  server.start();

  return 0;
}
