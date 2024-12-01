#include "api/client.hpp"

#include <chrono>
#include <iostream>
#include <zmq.hpp>

#include "api/message.hpp"

Client::Client(std::string serverAddr)
    : serverAddr_(std::move(serverAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::req) {}

Client::~Client() = default;

bool Client::start() noexcept {
  try {
    socket_.connect(serverAddr_);
  } catch (const zmq::error_t& e) {
    std::cerr << "Error starting client: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool Client::stop() noexcept {
  try {
    socket_.disconnect(serverAddr_);
    context_.close();
  } catch (const zmq::error_t& e) {
    std::cerr << "Error stopping client: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool Client::restart() noexcept {
  if (!stop()) {
    return false;
  }

  return start();
}

bool Client::sendRequestAndReceiveReply_(zmq::message_t& request,
                                         zmq::message_t& reply) noexcept {
  try {
    socket_.send(request, zmq::send_flags::none);
    if (const auto result = socket_.recv(reply, zmq::recv_flags::none);
        !result.has_value()) {
      return false;
    }
  } catch (const zmq::error_t& e) {
    std::cerr << "Error sending&receiving message: " << e.what() << std::endl;
    return false;
  }

  return true;
}

bool Client::addUser(const std::string& username,
                     const std::string& password) noexcept {
  Message msg(MessageType::ADD_USER);
  msg.setUsername(username);
  msg.setPassword(password);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

bool Client::removeUser(const std::string& username) noexcept {
  Message msg(MessageType::REMOVE_USER);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

bool Client::isExistUser(const std::string& username) noexcept {
  Message msg(MessageType::IS_EXIST_USER);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

std::vector<std::string> Client::listAllUsers() noexcept {
  const Message msg(MessageType::LIST_ALL_USERS);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}

bool Client::authenticateUser(const std::string& username,
                              const std::string& password) noexcept {
  Message msg(MessageType::AUTHENTICATE_USER);
  msg.setUsername(username);
  msg.setPassword(password);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

bool Client::addUserTag(const std::string& username,
                        const std::string& tag) noexcept {
  Message msg(MessageType::ADD_USER_TAG);
  msg.setUsername(username);
  msg.setTag(tag);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

bool Client::removeUserTag(const std::string& username,
                           const std::string& tag) noexcept {
  Message msg(MessageType::REMOVE_USER_TAG);
  msg.setUsername(username);
  msg.setTag(tag);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

std::vector<std::string> Client::getUserTags(
    const std::string& username) noexcept {
  Message msg(MessageType::GET_USER_TAGS);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}

bool Client::sendMessage(const std::string& from, const std::string& to,
                         const std::string& message) noexcept {
  Message msg(MessageType::SEND_MESSAGE);
  msg.setFrom(from);
  msg.setTo(to);
  msg.setMessage(message);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

std::vector<std::string> Client::getSentMessages(
    const std::string& username) noexcept {
  Message msg(MessageType::GET_SENT_MESSAGES);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}

std::vector<std::string> Client::getReceivedMessages(
    const std::string& username) noexcept {
  Message msg(MessageType::GET_RECEIVED_MESSAGES);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}

std::vector<std::string> Client::getPair(const std::string& username) noexcept {
  Message msg(MessageType::GET_PAIR);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["vector"];
    }
  }
  return {};
}
