#include "api/server.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <zmq.hpp>

#include "api/message.hpp"
#include "pair/pair.hpp"

Server::Server(std::string listenAddr)
    : listenAddr_(std::move(listenAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::rep),
      running_(false) {
  pair_.setStorage(storage_);
}
Server::~Server() = default;

std::string Server::getListenAddr() const { return listenAddr_; }

bool Server::start() {
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

void Server::run_() {
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

bool Server::stop() {
  try {
    running_ = false;
    serverThread_.join();

    socket_.unbind(listenAddr_);
    context_.close();
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

zmq::message_t Server::handleRequest_(const zmq::message_t& request) {
  const Message requestMessage(request.to_string());
  const MessageType requestType = requestMessage.getType();
  const nlohmann::json requestContent = requestMessage.getContent();

  const Message successMessage(MessageType::SUCCESS, "");
  const Message failureMessage(MessageType::FAILURE, "");

  zmq::message_t replySuccess(successMessage.toString());
  zmq::message_t replyFailure(failureMessage.toString());

  if (requestType == MessageType::ADD_USER) {
    const std::string username = requestContent["username"];
    const std::string password = requestContent["password"];

    if (addUser_(username, password)) {
      return replySuccess;
    } else {
      return replyFailure;
    }
  }

  if (requestType == MessageType::REMOVE_USER) {
    const std::string username = requestContent["username"];
    if (removeUser_(username)) {
      return replySuccess;
    } else {
      return replyFailure;
    }
  }

  if (requestType == MessageType::IS_EXIST_USER) {
    const std::string username = requestContent["username"];
    if (isExistUser_(username)) {
      return replySuccess;
    } else {
      return replyFailure;
    }
  }

  if (requestType == MessageType::LIST_ALL_USERS) {
    const std::vector<std::string> users = listAllUsers();
    nlohmann::json content;
    content["vector"] = users;

    return zmq::message_t(Message(MessageType::SUCCESS, content).toString());
  }

  if (requestType == MessageType::AUTHENTICATE_USER) {
    const std::string username = requestContent["username"];
    const std::string password = requestContent["password"];

    if (authenticateUser_(username, password)) {
      return replySuccess;
    } else {
      return replyFailure;
    }
  }

  if (requestType == MessageType::ADD_USER_TAG) {
    const std::string username = requestContent["username"];
    const std::string tag = requestContent["tag"];

    if (addUserTag_(username, tag)) {
      return replySuccess;
    } else {
      return replyFailure;
    }
  }

  if (requestType == MessageType::REMOVE_USER_TAG) {
    const std::string username = requestContent["username"];
    const std::string tag = requestContent["tag"];

    if (removeUserTag_(username, tag)) {
      return replySuccess;
    } else {
      return replyFailure;
    }
  }

  if (requestType == MessageType::GET_USER_TAGS) {
    const std::string username = requestContent["username"];
    const std::vector<std::string> tags = getUserTags_(username);
    nlohmann::json content;
    content["vector"] = tags;

    return zmq::message_t(Message(MessageType::SUCCESS, content).toString());
  }

  if (requestType == MessageType::SEND_MESSAGE) {
    const std::string from = requestContent["from"];
    const std::string to = requestContent["to"];
    const std::string message = requestContent["message"];

    if (sendMessage_(from, to, message)) {
      return replySuccess;
    } else {
      return replyFailure;
    }
  }

  if (requestType == MessageType::GET_SENT_MESSAGES) {
    const std::string username = requestContent["username"];
    const std::vector<std::string> messages = getSentMessages_(username);
    nlohmann::json content;
    content["vector"] = messages;

    return zmq::message_t(Message(MessageType::SUCCESS, content).toString());
  }

  if (requestType == MessageType::GET_RECEIVED_MESSAGES) {
    const std::string username = requestContent["username"];
    const std::vector<std::string> messages = getReceivedMessages_(username);
    nlohmann::json content;
    content["vector"] = messages;

    return zmq::message_t(Message(MessageType::SUCCESS, content).toString());
  }

  if (requestType == MessageType::GET_PAIR) {
    const std::string username = requestContent["username"];
    const std::vector<std::string> pair = getPair_(username);
    nlohmann::json content;
    content["vector"] = pair;

    return zmq::message_t(Message(MessageType::SUCCESS, content).toString());
  }

  return replyFailure;
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

bool Server::isExistUser_(const std::string& username) {
  // Check if user exists
  return true;
}

std::vector<std::string> Server::listAllUsers() {
  // List all users
  return {};
}

bool Server::authenticateUser_(const std::string& username,
                               const std::string& password) {
  // Authenticate user
  return true;
}

bool Server::addUserTag_(const std::string& username, const std::string& tag) {
  // Add tag to user
  return true;
}

bool Server::removeUserTag_(const std::string& username,
                            const std::string& tag) {
  // Remove tag from user
  return true;
}

std::vector<std::string> Server::getUserTags_(const std::string& username) {
  // Get all tags of user
  return {};
}

bool Server::sendMessage_(const std::string& from, const std::string& to,
                          const std::string& message) {
  // Send message to user
  return true;
}

std::vector<std::string> Server::getSentMessages_(const std::string& username) {
  // Get all sent messages of user
  return {};
}

std::vector<std::string> Server::getReceivedMessages_(
    const std::string& username) {
  // Get all received message of user
  return {};
}

std::vector<std::string> Server::getPair_(const std::string& username) {
  return pair_.getPair(username);
}
