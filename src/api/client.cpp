#include "client.hpp"

#include <iostream>
#include <zmq.hpp>

#include "network_message.hpp"

Client::Client(std::string serverAddr)
    : serverAddr_(std::move(serverAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::req) {}

Client::Client(const Client& other)
    : serverAddr_(other.serverAddr_),
      context_(1),
      socket_(context_, zmq::socket_type::req) {}

Client::Client(Client&& other) noexcept
    : serverAddr_(std::move(other.serverAddr_)),
      context_(std::move(other.context_)),
      socket_(std::move(other.socket_)) {}

auto Client::operator=(const Client& other) -> Client& {
  if (this == &other) {
    return *this;
  }

  socket_.close();
  context_.close();

  serverAddr_ = other.serverAddr_;
  context_ = zmq::context_t(1);
  socket_ = zmq::socket_t(context_, zmq::socket_type::req);
  socket_.connect(serverAddr_);

  return *this;
}

auto Client::operator=(Client&& other) noexcept -> Client& {
  if (this == &other) {
    return *this;
  }

  socket_.close();
  context_.close();

  serverAddr_ = std::move(other.serverAddr_);
  context_ = std::move(other.context_);
  socket_ = std::move(other.socket_);

  return *this;
}

Client::~Client() = default;

auto Client::start() noexcept -> bool {
  try {
    socket_.connect(serverAddr_);
  } catch (const zmq::error_t& e) {
    std::cerr << "Error starting client: " << e.what() << '\n';
    return false;
  }
  return true;
}

auto Client::stop() noexcept -> bool {
  try {
    socket_.disconnect(serverAddr_);
    context_.close();
  } catch (const zmq::error_t& e) {
    std::cerr << "Error stopping client: " << e.what() << '\n';
    return false;
  }
  return true;
}

auto Client::restart() noexcept -> bool {
  if (!stop()) {
    return false;
  }

  return start();
}

auto Client::sendRequestAndReceiveReply_(zmq::message_t& request,
                                         zmq::message_t& reply) noexcept
    -> bool {
  try {
    socket_.send(request, zmq::send_flags::none);
    if (const auto result = socket_.recv(reply, zmq::recv_flags::none);
        !result.has_value()) {
      return false;
    }
  } catch (const zmq::error_t& e) {
    std::cerr << "Error sending&receiving message: " << e.what() << '\n';
    return false;
  }

  return true;
}

auto Client::addUser(const std::string& username,
                     const std::string& password) noexcept -> bool {
  NetworkMessage msg(NetworkMessageType::ADD_USER);
  msg.setUsername(username);
  msg.setPassword(password);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const NetworkMessage replyMessage(reply.to_string());
    return replyMessage.getType() == NetworkMessageType::SUCCESS;
  }
  return false;
}

auto Client::removeUser(const std::string& username) noexcept -> bool {
  NetworkMessage msg(NetworkMessageType::REMOVE_USER);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const NetworkMessage replyMessage(reply.to_string());
    return replyMessage.getType() == NetworkMessageType::SUCCESS;
  }
  return false;
}

auto Client::isExistUser(const std::string& username) noexcept -> bool {
  NetworkMessage msg(NetworkMessageType::IS_EXIST_USER);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const NetworkMessage replyMessage(reply.to_string());
    return replyMessage.getType() == NetworkMessageType::SUCCESS;
  }
  return false;
}

auto Client::listAllUsers() -> std::vector<std::string> {
  const NetworkMessage msg(NetworkMessageType::LIST_ALL_USERS);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const NetworkMessage replyMessage(reply.to_string());
        replyMessage.getType() == NetworkMessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}

auto Client::authenticateUser(const std::string& username,
                              const std::string& password) noexcept -> bool {
  NetworkMessage msg(NetworkMessageType::AUTHENTICATE_USER);
  msg.setUsername(username);
  msg.setPassword(password);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const NetworkMessage replyMessage(reply.to_string());
    return replyMessage.getType() == NetworkMessageType::SUCCESS;
  }
  return false;
}

auto Client::addUserTag(const std::string& username,
                        const std::string& tag) noexcept -> bool {
  NetworkMessage msg(NetworkMessageType::ADD_USER_TAG);
  msg.setUsername(username);
  msg.setTag(tag);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const NetworkMessage replyMessage(reply.to_string());
    return replyMessage.getType() == NetworkMessageType::SUCCESS;
  }
  return false;
}

auto Client::removeUserTag(const std::string& username,
                           const std::string& tag) noexcept -> bool {
  NetworkMessage msg(NetworkMessageType::REMOVE_USER_TAG);
  msg.setUsername(username);
  msg.setTag(tag);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const NetworkMessage replyMessage(reply.to_string());
    return replyMessage.getType() == NetworkMessageType::SUCCESS;
  }
  return false;
}

auto Client::getUserTags(const std::string& username)
    -> std::vector<std::string> {
  NetworkMessage msg(NetworkMessageType::GET_USER_TAGS);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const NetworkMessage replyMessage(reply.to_string());
        replyMessage.getType() == NetworkMessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}

auto Client::sendMessage(const std::string& from, const std::string& to,
                         const std::string& message) noexcept -> bool {
  NetworkMessage msg(NetworkMessageType::SEND_MESSAGE);
  msg.setFrom(from);
  msg.setTo(to);
  msg.setMessage(message);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const NetworkMessage replyMessage(reply.to_string());
    return replyMessage.getType() == NetworkMessageType::SUCCESS;
  }
  return false;
}

auto Client::getSentMessages(const std::string& username)
    -> std::vector<std::string> {
  NetworkMessage msg(NetworkMessageType::GET_SENT_MESSAGES);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const NetworkMessage replyMessage(reply.to_string());
        replyMessage.getType() == NetworkMessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}

auto Client::getReceivedMessages(const std::string& username)
    -> std::vector<std::string> {
  NetworkMessage msg(NetworkMessageType::GET_RECEIVED_MESSAGES);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const NetworkMessage replyMessage(reply.to_string());
        replyMessage.getType() == NetworkMessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}

auto Client::getPair(const std::string& username) -> std::vector<std::string> {
  NetworkMessage msg(NetworkMessageType::GET_PAIR);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const NetworkMessage replyMessage(reply.to_string());
        replyMessage.getType() == NetworkMessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}
