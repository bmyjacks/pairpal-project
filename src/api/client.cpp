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

bool Client::sendRequestAndReceiveReply_(zmq::message_t& request,
                                         zmq::message_t& reply) {
  try {
    // const auto start = std::chrono::high_resolution_clock::now();

    socket_.send(request, zmq::send_flags::none);
    socket_.recv(reply, zmq::recv_flags::none);
    //
    // const auto end = std::chrono::high_resolution_clock::now();
    //
    // const auto duration =
    //     std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // std::cout << "Request took " << duration.count() << "ms" << std::endl;
  } catch (const zmq::error_t& e) {
    std::cerr << "Error sending&receiving message: " << e.what() << std::endl;
    return false;
  }

  return true;
}

bool Client::addUser(const std::string& username, const std::string& password) {
  nlohmann::json content;
  content["username"] = username;
  content["password"] = password;

  const Message message(MessageType::ADD_USER, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

bool Client::removeUser(const std::string& username) {
  nlohmann::json content;
  content["username"] = username;

  const Message message(MessageType::REMOVE_USER, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

bool Client::isExistUser(const std::string& username) {
  nlohmann::json content;
  content["username"] = username;

  const Message message(MessageType::IS_EXIST_USER, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

std::vector<std::string> Client::listAllUsers() {
  nlohmann::json content;
  content["LIST_ALL_USERS"] = true;

  const Message message(MessageType::LIST_ALL_USERS, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["users"];
    }
  }
  return {};
}

bool Client::authenticateUser(const std::string& username,
                              const std::string& password) {
  nlohmann::json content;
  content["username"] = username;
  content["password"] = password;

  const Message message(MessageType::AUTHENTICATE_USER, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

bool Client::addUserTag(const std::string& username, const std::string& tag) {
  nlohmann::json content;
  content["username"] = username;
  content["tag"] = tag;

  const Message message(MessageType::ADD_USER_TAG, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

bool Client::removeUserTag(const std::string& username,
                           const std::string& tag) {
  nlohmann::json content;
  content["username"] = username;
  content["tag"] = tag;

  const Message message(MessageType::REMOVE_USER_TAG, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

std::string Client::getUserTags(const std::string& username) {
  nlohmann::json content;
  content["username"] = username;

  const Message message(MessageType::GET_USER_TAGS, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["tags"];
    }
  }
  return "";
}

bool Client::sendMessage(const std::string& from, const std::string& to,
                         const std::string& message) {
  nlohmann::json content;
  content["from"] = from;
  content["to"] = to;
  content["message"] = message;

  const Message msg(MessageType::SEND_MESSAGE, content);
  const std::string serializedMessage = msg.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    const Message replyMessage(reply.to_string());
    return replyMessage.getType() == MessageType::SUCCESS;
  }
  return false;
}

std::vector<std::string> Client::getSentMessages(const std::string& username) {
  nlohmann::json content;
  content["username"] = username;

  const Message message(MessageType::GET_SENT_MESSAGES, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["messages"];
    }
  }
  return {};
}

std::vector<std::string> Client::getReceivedMessages(
    const std::string& username) {
  nlohmann::json content;
  content["username"] = username;

  const Message message(MessageType::GET_RECEIVED_MESSAGES, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["messages"];
    }
  }
  return {};
}

std::vector<std::string> Client::getPair(std::string& username) {
  nlohmann::json content;
  content["username"] = username;

  const Message message(MessageType::GET_PAIR, content);
  const std::string serializedMessage = message.toString();

  zmq::message_t request(serializedMessage);

  if (zmq::message_t reply; sendRequestAndReceiveReply_(request, reply)) {
    if (const Message replyMessage(reply.to_string());
        replyMessage.getType() == MessageType::SUCCESS) {
      return replyMessage.getContent()["messages"];
    }
  }
  return {};
}
