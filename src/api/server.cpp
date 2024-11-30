#include "api/server.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <zmq.hpp>

#include "api/message.hpp"
#include "pair/pair.hpp"

Server::Server(std::string listenAddr) noexcept
    : listenAddr_(std::move(listenAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::rep),
      running_(false) {
  pair_.setStorage(storage_);
}
Server::~Server() noexcept = default;

std::string Server::getListenAddr() const noexcept { return listenAddr_; }

bool Server::start() noexcept {
  try {
    running_ = true;
    socket_.bind(listenAddr_);
  } catch (const zmq::error_t& e) {
    std::cerr << "Error starting server: " << e.what() << std::endl;
    return false;
  }

  std::cout << std::format("Server started on {}", listenAddr_) << std::endl;

  serverThread_ = std::thread(&Server::run_, this);

  return true;
}

void Server::run_() noexcept {
  while (running_) {
    try {
      zmq::message_t request;
      zmq::recv_result_t result =
          socket_.recv(request, zmq::recv_flags::dontwait);

      if (result.has_value()) {
        std::cout << "Received request" << request.to_string() << std::endl;

        auto reply = handleRequest_(request);
        socket_.send(reply, zmq::send_flags::none);
        std::cout << "Send back" << reply.to_string() << std::endl;
      }
    } catch (const zmq::error_t& e) {
      std::cerr << "Error receiving message: " << e.what() << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

bool Server::stop() noexcept {
  try {
    running_ = false;
    serverThread_.join();

    socket_.unbind(listenAddr_);
    socket_.close();
    context_.close();
  } catch (const zmq::error_t& e) {
    std::cerr << "Error stopping server: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool Server::restart() noexcept {
  if (!stop()) {
    return false;
  }

  return start();
}

zmq::message_t Server::handleRequest_(const zmq::message_t& request) noexcept {
  const Message requestMessage(request.to_string());
  const MessageType requestType = requestMessage.getType();
  // const nlohmann::json requestContent = requestMessage.getContent();

  const Message successMessage(MessageType::SUCCESS);
  const Message failureMessage(MessageType::FAILURE);

  zmq::message_t replySuccess(successMessage.toString());
  zmq::message_t replyFailure(failureMessage.toString());

  if (requestType == MessageType::ADD_USER &&
      addUser_(requestMessage.getUsername(), requestMessage.getPassword())) {
    return replySuccess;
  }

  if (requestType == MessageType::REMOVE_USER &&
      removeUser_(requestMessage.getUsername())) {
    return replySuccess;
  }

  if (requestType == MessageType::IS_EXIST_USER &&
      isExistUser_(requestMessage.getUsername())) {
    return replySuccess;
  }

  if (requestType == MessageType::LIST_ALL_USERS) {
    const std::vector<std::string> users = listAllUsers();

    Message response(MessageType::SUCCESS);
    response.setVector(users);

    return std::move(*response.toZmqMessage());
  }

  if (requestType == MessageType::AUTHENTICATE_USER &&
      authenticateUser_(requestMessage.getUsername(),
                        requestMessage.getPassword())) {
    return replySuccess;
  }

  if (requestType == MessageType::ADD_USER_TAG &&
      addUserTag_(requestMessage.getUsername(), requestMessage.getTag())) {
    return replySuccess;
  }

  if (requestType == MessageType::REMOVE_USER_TAG &&
      removeUserTag_(requestMessage.getUsername(), requestMessage.getTag())) {
    return replySuccess;
  }

  if (requestType == MessageType::GET_USER_TAGS) {
    const auto tags = getUserTags_(requestMessage.getUsername());
    Message response(MessageType::SUCCESS);
    response.setVector(tags);

    return std::move(*response.toZmqMessage());
  }

  if (requestType == MessageType::SEND_MESSAGE &&
      sendMessage_(requestMessage.getFrom(), requestMessage.getTo(),
                   requestMessage.getMessage())) {
    return replySuccess;
  }

  if (requestType == MessageType::GET_SENT_MESSAGES) {
    const auto messages = getSentMessages_(requestMessage.getUsername());

    Message response(MessageType::SUCCESS);
    response.setVector(messages);

    return std::move(*response.toZmqMessage());
  }

  if (requestType == MessageType::GET_RECEIVED_MESSAGES) {
    const auto messages = getReceivedMessages_(requestMessage.getUsername());

    Message response(MessageType::SUCCESS);
    response.setVector(messages);

    return std::move(*response.toZmqMessage());
  }

  if (requestType == MessageType::GET_PAIR) {
    const auto messages = getPair_(requestMessage.getUsername());

    Message response(MessageType::SUCCESS);
    response.setVector(messages);

    return std::move(*response.toZmqMessage());
  }

  return replyFailure;
}

bool Server::addUser_(const std::string& username,
                      const std::string& password) noexcept {
  // Add user to the database
  return true;
}

bool Server::removeUser_(const std::string& username) noexcept {
  // Remove user from the database
  return true;
}

bool Server::isExistUser_(const std::string& username) noexcept {
  // Check if user exists
  return true;
}

std::vector<std::string> Server::listAllUsers() noexcept {
  // List all users
  return {};
}

bool Server::authenticateUser_(const std::string& username,
                               const std::string& password) noexcept {
  // Authenticate user
  return true;
}

bool Server::addUserTag_(const std::string& username,
                         const std::string& tag) noexcept {
  // Add tag to user
  return true;
}

bool Server::removeUserTag_(const std::string& username,
                            const std::string& tag) noexcept {
  // Remove tag from user
  return true;
}

std::vector<std::string> Server::getUserTags_(
    const std::string& username) noexcept {
  // Get all tags of user
  return {};
}

bool Server::sendMessage_(const std::string& from, const std::string& to,
                          const std::string& message) noexcept {
  // Send message to user
  return true;
}

std::vector<std::string> Server::getSentMessages_(
    const std::string& username) noexcept {
  // Get all sent messages of user
  return {};
}

std::vector<std::string> Server::getReceivedMessages_(
    const std::string& username) noexcept {
  // Get all received message of user
  return {};
}

std::vector<std::string> Server::getPair_(
    const std::string& username) noexcept {
  return pair_.getPair(username);
}
