#include "network_message.hpp"

#include <nlohmann/json.hpp>

NetworkMessage::NetworkMessage(const NetworkMessageType& type) : type_(type) {}

NetworkMessage::NetworkMessage(const std::string& str) {
  nlohmann::json json = nlohmann::json::parse(str);

  type_ = json["type"].get<NetworkMessageType>();
  content_ = json["content"];
}

NetworkMessage::~NetworkMessage() = default;

auto NetworkMessage::getType() const -> NetworkMessageType { return type_; }

auto NetworkMessage::toJson() const -> nlohmann::json {
  nlohmann::json json;
  json["type"] = type_;
  json["content"] = content_;
  return json;
}

auto NetworkMessage::toString() const -> std::string { return toJson().dump(); }

auto NetworkMessage::toZmqMessage() const -> std::unique_ptr<zmq::message_t> {
  return std::make_unique<zmq::message_t>(toString());
}

void NetworkMessage::setUsername(const std::string& username) {
  content_["username"] = username;
}
auto NetworkMessage::getUsername() const -> std::string {
  return content_["username"].get<std::string>();
}

void NetworkMessage::setPassword(const std::string& password) {
  content_["password"] = password;
}
auto NetworkMessage::getPassword() const -> std::string {
  return content_["password"].get<std::string>();
}

void NetworkMessage::setTag(const std::string& tag) { content_["tag"] = tag; }
auto NetworkMessage::getTag() const -> std::string {
  return content_["tag"].get<std::string>();
}

void NetworkMessage::setFrom(const std::string& from) {
  content_["from"] = from;
}
auto NetworkMessage::getFrom() const -> std::string {
  return content_["from"].get<std::string>();
}

void NetworkMessage::setTo(const std::string& to) { content_["to"] = to; }
auto NetworkMessage::getTo() const -> std::string {
  return content_["to"].get<std::string>();
}

void NetworkMessage::setMessage(const std::string& message) {
  content_["message"] = message;
}

void NetworkMessage::setVector(const std::vector<std::string>& vec) {
  content_["vec"] = vec;
}

auto NetworkMessage::getVector() const -> std::vector<std::string> {
  return content_["vec"].get<std::vector<std::string>>();
}

auto NetworkMessage::getMessage() const -> std::string {
  return content_["message"].get<std::string>();
}
