#include "api/client.hpp"

#include <iostream>
#include <zmq.hpp>

#include "api/message.hpp"

Client::Client(std::string serverAddr)
    : serverAddr_(std::move(serverAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::req) {}

auto Client::operator=(const Client& other) -> Client& {
  if (this == &other) {
    return *this;  // Handle self-assignment
  }

  // Release any resources held by the current object
  socket_.close();
  context_.close();

  // Copy the resources from the source object
  serverAddr_ = other.serverAddr_;
  context_ = zmq::context_t(1);
  socket_ = zmq::socket_t(context_, zmq::socket_type::req);
  socket_.connect(serverAddr_);

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

auto Client::removeUser(const std::string& username) noexcept -> bool {
  Message msg(MessageType::REMOVE_USER);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

auto Client::isExistUser(const std::string& username) noexcept -> bool {
  Message msg(MessageType::IS_EXIST_USER);
  msg.setUsername(username);

  if (zmq::message_t reply;
      sendRequestAndReceiveReply_(*msg.toZmqMessage(), reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

auto Client::listAllUsers() -> std::vector<std::string> {
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

auto Client::authenticateUser(const std::string& username,
                              const std::string& password) noexcept -> bool {
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

auto Client::addUserTag(const std::string& username,
                        const std::string& tag) noexcept -> bool {
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

auto Client::removeUserTag(const std::string& username,
                           const std::string& tag) noexcept -> bool {
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

auto Client::getUserTags(const std::string& username)
    -> std::vector<std::string> {
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

auto Client::sendMessage(const std::string& from, const std::string& to,
                         const std::string& message) noexcept -> bool {
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

auto Client::getSentMessages(const std::string& username)
    -> std::vector<std::string> {
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

auto Client::getReceivedMessages(const std::string& username)
    -> std::vector<std::string> {
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

auto Client::getPair(const std::string& username) -> std::vector<std::string> {
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
