#include "api/server.hpp"

#include <chrono>
#include <format>
#include <iostream>
#include <list>
#include <thread>
#include <zmq.hpp>

#include "api/message.hpp"

using namespace std::chrono_literals;

Server::Server(std::string listenAddr)
    : listenAddr_(std::move(listenAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::rep) {}
Server::~Server() = default;

bool Server::start() {
  socket_.bind(listenAddr_);

  std::cout << std::format("Server started on {}", listenAddr_) << std::endl;

  const Message message(MessageType::SUCCESS, {"SUCCESS"});
  const std::string serializedMessage = message.toString();
  zmq::message_t reply(serializedMessage);

  for (;;) {
    try {
      zmq::message_t request;
      socket_.recv(request, zmq::recv_flags::none);
      std::cout << "Received request" << request.to_string() << std::endl;
    } catch (const zmq::error_t& e) {
      std::cerr << "Error receiving message: " << e.what() << std::endl;
    }

    try {
      socket_.send(reply, zmq::send_flags::none);
    } catch (const zmq::error_t& e) {
      std::cerr << "Error sending message: " << e.what() << std::endl;
    }
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
