#include "api/server.hpp"

#include <chrono>
#include <iostream>
#include <list>
#include <thread>
#include <zmq.hpp>

using namespace std::chrono_literals;

Server::Server(std::string listenAddr)
    : listenAddr_(std::move(listenAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::rep) {}
Server::~Server() = default;

bool Server::start() {
  socket_.bind(listenAddr_);

  std::cout << std::format("Server started on {}", listenAddr_) << std::endl;

  // prepare some static data for responses
  const std::string data{"World8"};

  for (;;) {
    zmq::message_t request;

    // receive a request from client
    socket_.recv(request, zmq::recv_flags::none);
    std::cout << "Received " << request.to_string() << std::endl;

    // simulate work
    // std::this_thread::sleep_for(1s);

    // send the reply to the client
    socket_.send(zmq::buffer(data), zmq::send_flags::none);
  }

  return true;
}

bool Server::stop() {
  try {
    socket_.unbind(listenAddr_);
  } catch (const zmq::error_t& e) {
    std::cerr << "Error stopping server: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool Server::restart() {
  if (!stop()) {
    return false;
  }

  return start();
}
