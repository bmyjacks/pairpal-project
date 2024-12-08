#include "api/server.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <zmq.hpp>

#include "api/message.hpp"
#include "pair/pair.hpp"

namespace api {

Server::Server(std::string listenAddr)
    : listenAddr_(std::move(listenAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::rep),
      running_(false) {
  pair_.setStorage(storage_);
}
Server::~Server() = default;

auto Server::getListenAddr() const -> std::string { return listenAddr_; }

auto Server::start() -> bool {
  try {
    running_ = true;
    socket_.bind(listenAddr_);
  } catch (const zmq::error_t& e) {
    std::cerr << std::format("[ERROR] {} Error starting server: {}",
                             std::chrono::system_clock::now(), e.what())
              << '\n';
    return false;
  }

  std::cout << std::format("[INFO] {} started on {}",
                           std::chrono::system_clock::now(), listenAddr_)
            << '\n';

  serverThread_ = std::thread(&Server::run_, this);

  return true;
}

void Server::run_() {
  while (running_) {
    try {
      zmq::message_t request;
      const zmq::recv_result_t result =
          socket_.recv(request, zmq::recv_flags::dontwait);

      if (result.has_value()) {
        std::cout << std::format("[INFO] {} Received request {}",
                                 std::chrono::system_clock::now(),
                                 request.to_string())
                  << '\n';

        auto reply = handleRequest_(request);
        socket_.send(reply, zmq::send_flags::none);
        std::cout << std::format("[INFO] {} Sent reply {}",
                                 std::chrono::system_clock::now(),
                                 reply.to_string())
                  << '\n';
      }
    } catch (const zmq::error_t& e) {
      std::cerr << std::format("[ERROR] {} Error receiving message: {}",
                               std::chrono::system_clock::now(), e.what())
                << '\n';
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

auto Server::stop() -> bool {
  try {
    running_ = false;

    if (serverThread_.joinable()) {
      serverThread_.join();
    }

    socket_.unbind(listenAddr_);
    socket_.close();
    context_.close();
  } catch (const zmq::error_t& e) {
    std::cerr << std::format("[ERROR] {} Error stopping server: {}",
                             std::chrono::system_clock::now(), e.what())
              << '\n';
    return false;
  }
  return true;
}

auto Server::handleRequest_(const zmq::message_t& request) -> zmq::message_t {
  const Message requestMessage(request.to_string());
  const MessageType requestType = requestMessage.getType();

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

auto Server::addUser_(const std::string& username, const std::string& password)
    -> bool {
  return storage_.addUser(username, password);
}

auto Server::removeUser_(const std::string& username) -> bool {
  return storage_.removeUser(username);
}

auto Server::isExistUser_(const std::string& username) -> bool {
  return storage_.isUserExist(username);
}

auto Server::listAllUsers() -> std::vector<std::string> {
  std::vector<std::string> users;

  for (const auto& [id, username, password, tags] : storage_.getUsers()) {
    users.push_back(username);
  }

  return users;
}

auto Server::authenticateUser_(const std::string& username,
                               const std::string& password) -> bool {
  return storage_.authenticateUser(username, password);
}

auto Server::addUserTag_(const std::string& username, const std::string& tag)
    -> bool {
  return storage_.addTag(username, tag);
}

auto Server::removeUserTag_(const std::string& username, const std::string& tag)
    -> bool {
  return storage_.removeTag(username, tag);
}

auto Server::getUserTags_(const std::string& username)
    -> std::vector<std::string> {
  return storage_.getTags(username);
}

auto Server::sendMessage_(const std::string& from, const std::string& to,
                          const std::string& message) -> bool {
  // Send message to user
  return true;
}

auto Server::getSentMessages_(const std::string& username)
    -> std::vector<std::string> {
  // Get all sent messages of user
  return {};
}

auto Server::getReceivedMessages_(const std::string& username)
    -> std::vector<std::string> {
  // Get all received message of user
  return {};
}

auto Server::getPair_(const std::string& username) -> std::vector<std::string> {
  return pair_.getPair(username);
}

}  // namespace api
