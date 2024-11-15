#include "api/server.hpp"

#include <chrono>
#include <future>
#include <iostream>
#include <list>
#include <thread>
#include <vector>
#include <zmq.hpp>

#include "api/message.hpp"

using namespace std::chrono_literals;

Server::Server(std::string listenAddr)
    : listenAddr_(std::move(listenAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::rep) {}
Server::~Server() = default;

std::string Server::getListenAddr() const { return listenAddr_; }

bool Server::start() {
  socket_.bind(listenAddr_);

  std::cout << std::format("Server started on {}", listenAddr_) << std::endl;

  for (;;) {
    try {
      zmq::message_t request;
      socket_.recv(request, zmq::recv_flags::none);
      std::cout << "Received request" << request.to_string() << std::endl;

      const bool success = handleRequest_(request);

      if (success) {
        const Message message(MessageType::SUCCESS, {"SUCCESS"});
        const std::string serializedMessage = message.toString();

        zmq::message_t reply(serializedMessage);
        socket_.send(reply, zmq::send_flags::none);
        std::cout << "Send back" << std::endl;
      } else {
        const Message message(MessageType::FAILURE, {"FAILURE"});
        const std::string serializedMessage = message.toString();

        zmq::message_t reply(serializedMessage);
        socket_.send(reply, zmq::send_flags::none);
        std::cout << "Send back" << std::endl;
      }
    } catch (const zmq::error_t& e) {
      std::cerr << "Error receiving message: " << e.what() << std::endl;
    }
  }
}

bool Server::handleRequest_(const zmq::message_t& request) {
  switch (const Message message(request.to_string()); message.getType()) {
    case MessageType::ADD_USER:
      return addUser_(message.getContent()["username"],
                      message.getContent()["password"]);
    default:
      return false;
  }
}

bool Server::addUser_(const std::string& username,
                      const std::string& password) {
  std::cout << std::format("DATABASE ADD USER {}{}", username, password)
            << std::endl;

  return true;
}
