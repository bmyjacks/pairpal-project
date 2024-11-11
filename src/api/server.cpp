#include "api/server.hpp"

#include <iostream>

Server::Server() = default;
Server::~Server() = default;

bool Server::start(const uint8_t listenPort) {
  port = listenPort;

  std::cout << "Server started on port " << port << std::endl;

  return true;
}
