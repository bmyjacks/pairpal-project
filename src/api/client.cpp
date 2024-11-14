#include "api/client.hpp"

#include <iostream>
#include <utility>
#include <zmq.hpp>

#include "api/message.hpp"

Client::Client(std::string serverAddr)
    : serverAddr_(std::move(serverAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::req) {}

Client::~Client() = default;

bool Client::start() {
  try {
    socket_.connect(serverAddr_);
  } catch (const zmq::error_t& e) {
    std::cerr << "Error starting client: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool Client::stop() {
  try {
    socket_.disconnect(serverAddr_);
    context_.close();
  } catch (const zmq::error_t& e) {
    std::cerr << "Error stopping client: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool Client::restart() {
  if (!stop()) {
    return false;
  }

  return start();
}

bool Client::addUser(const std::string& username, const std::string& password) {
  nlohmann::json content;
  content["username"] = username;
  content["password"] = password;

  const Message message(MessageType::ADD_USER, content);
  const std::string serializedMessage = message.toString();

  try {
    zmq::message_t request(serializedMessage);
    socket_.send(request, zmq::send_flags::none);
  } catch (const zmq::error_t& e) {
    std::cerr << "Error sending message: " << e.what() << std::endl;
    return false;
  }

  try {
    zmq::message_t reply;
    socket_.recv(reply, zmq::recv_flags::none);
    std::cout << "Received reply" << reply.to_string() << std::endl;
  } catch (const zmq::error_t& e) {
    std::cerr << "Error receiving message: " << e.what() << std::endl;
    return false;
  }

  return true;
}
