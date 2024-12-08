#include "api/message.hpp"

#include <nlohmann/json.hpp>

Message::Message(const MessageType& type, nlohmann::json content)
    : type_(type), content_(std::move(content)) {}

Message::Message(const MessageType& type) : type_(type) {}

Message::Message(const nlohmann::json& json)
    : type_(static_cast<MessageType>(json["type"].get<int>())),
      content_(json["content"]) {}

Message::Message(const std::string& str)
    : Message(nlohmann::json::parse(str)) {}

Message::~Message() = default;

auto Message::getType() const -> MessageType { return type_; }

auto Message::getContent() const -> nlohmann::json { return content_; }

auto Message::toJson() const -> nlohmann::json {
  nlohmann::json json;
  json["type"] = type_;
  json["content"] = content_;
  return json;
}

auto Message::toString() const -> std::string { return toJson().dump(); }

auto Message::toZmqMessage() const -> std::unique_ptr<zmq::message_t> {
  return std::make_unique<zmq::message_t>(toString());
}

void Message::setUsername(const std::string& username) {
  content_["username"] = username;
}
auto Message::getUsername() const -> std::string {
  return content_["username"].get<std::string>();
}

void Message::setPassword(const std::string& password) {
  content_["password"] = password;
}
auto Message::getPassword() const -> std::string {
  return content_["password"].get<std::string>();
}

void Message::setTag(const std::string& tag) { content_["tag"] = tag; }
auto Message::getTag() const -> std::string {
  return content_["tag"].get<std::string>();
}

void Message::setFrom(const std::string& from) { content_["from"] = from; }
auto Message::getFrom() const -> std::string {
  return content_["from"].get<std::string>();
}

void Message::setTo(const std::string& to) { content_["to"] = to; }
auto Message::getTo() const -> std::string {
  return content_["to"].get<std::string>();
}

void Message::setMessage(const std::string& message) {
  content_["message"] = message;
}

void Message::setVector(const std::vector<std::string>& vec) {
  content_["vec"] = vec;
}

auto Message::getVector() const -> std::vector<std::string> {
  return content_["vec"].get<std::vector<std::string>>();
}

auto Message::getMessage() const -> std::string {
  return content_["message"].get<std::string>();
}
