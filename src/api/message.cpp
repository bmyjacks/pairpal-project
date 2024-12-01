#include "api/message.hpp"

#include <memory>
#include <nlohmann/json.hpp>
#include <utility>

Message::Message(const MessageType& type, nlohmann::json content) noexcept
    : type_(type), content_(std::move(content)) {}

Message::Message(const MessageType& type) noexcept : type_(type) {}

Message::Message(const nlohmann::json& json) noexcept {
  type_ = static_cast<MessageType>(json["type"].get<int>());
  content_ = json["content"];
}

Message::Message(const std::string& str) noexcept
    : Message(nlohmann::json::parse(str)) {}

Message::~Message() = default;

MessageType Message::getType() const noexcept { return type_; }

nlohmann::json Message::getContent() const noexcept { return content_; }

nlohmann::json Message::toJson() const noexcept {
  nlohmann::json json;
  json["type"] = type_;
  json["content"] = content_;
  return json;
}

std::string Message::toString() const noexcept { return toJson().dump(); }

std::unique_ptr<zmq::message_t> Message::toZmqMessage() const noexcept {
  return std::make_unique<zmq::message_t>(toString());
}

void Message::setUsername(const std::string& username) noexcept {
  content_["username"] = username;
}
std::string Message::getUsername() const noexcept {
  return content_["username"].get<std::string>();
}

void Message::setPassword(const std::string& password) noexcept {
  content_["password"] = password;
}
std::string Message::getPassword() const noexcept {
  return content_["password"].get<std::string>();
}

void Message::setTag(const std::string& tag) noexcept { content_["tag"] = tag; }
std::string Message::getTag() const noexcept {
  return content_["tag"].get<std::string>();
}

void Message::setFrom(const std::string& from) noexcept {
  content_["from"] = from;
}
std::string Message::getFrom() const noexcept {
  return content_["from"].get<std::string>();
}

void Message::setTo(const std::string& to) noexcept { content_["to"] = to; }
std::string Message::getTo() const noexcept {
  return content_["to"].get<std::string>();
}

void Message::setMessage(const std::string& message) noexcept {
  content_["message"] = message;
}

void Message::setVector(const std::vector<std::string>& vec) noexcept {
  content_["vec"] = vec;
}

std::vector<std::string> Message::getVector() const noexcept {
  return content_["vec"].get<std::vector<std::string>>();
}

std::string Message::getMessage() const noexcept {
  return content_["message"].get<std::string>();
}
