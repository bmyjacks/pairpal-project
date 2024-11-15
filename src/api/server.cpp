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
    case MessageType::REMOVE_USER:
      return removeUser_(message.getContent()["username"]);
    case MessageType::AUTHENTICATE_USER:
      return authenticateUser_(message.getContent()["username"],
                               message.getContent()["password"]);
    case MessageType::IS_EXIST_USER:
      return isExistUser_(message.getContent()["username"]);
    case MessageType::LIST_ALL_USERS:
      // listUsers();
      return true;
    case MessageType::SEND_MESSAGE:
      return sendMessage_(message.getContent()["from"],
                          message.getContent()["to"],
                          message.getContent()["message"]);
    case MessageType::ADD_USER_TAG:
      return addUserTag_(message.getContent()["username"],
                         message.getContent()["tag"]);
    case MessageType::GET_USER_TAGS:
      // getUserTags_(message.getContent()["username"]);
      return true;
    case MessageType::GET_SENT_MESSAGES:
      // getSentMessages_(message.getContent()["username"]);
      return true;
    case MessageType::GET_PAIR:
      // getPair_(message.getContent()["username"]);
      return true;
    default:
      return false;
  }
}

bool Server::addUser_(const std::string& username,
                      const std::string& password) {
  // Add user to the database
  return true;
}

bool Server::removeUser_(const std::string& username) {
  // Remove user from the database
  return true;
}

bool Server::authenticateUser_(const std::string& username,
                               const std::string& password) {
  // Authenticate user
  return true;
}

bool Server::isExistUser_(const std::string& username) {
  // Check if user exists
  return true;
}

std::vector<std::string> Server::listUsers() {
  // List all users
  return {};
}

bool Server::sendMessage_(const std::string& from, const std::string& to,
                          const std::string& message) {
  // Send message to user
  return true;
}

bool Server::addUserTag_(const std::string& username, const std::string& tag) {
  // Add tag to user
  return true;
}

std::vector<std::string> Server::getUserTags_(const std::string& username) {
  // Get all tags of user
  return {};
}

std::vector<std::string> Server::getSentMessages_(const std::string& username) {
  // Get all sent messages of user
  return {};
}

std::vector<std::string> Server::getPair_(const std::string& username) {
  // Get all pairs of user
  return {};
}
