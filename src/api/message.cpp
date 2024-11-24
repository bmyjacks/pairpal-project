#include "api/message.hpp"

#include <nlohmann/json.hpp>
#include <utility>

Message::Message(MessageType type, nlohmann::json content)
    : type_(type), content_(std::move(content)) {}

Message::Message(const nlohmann::json& json) {
    try{
        if (json.contains("type")&&json.contains("content")) {
            type_ = static_cast<MessageType>(json["type"].get<int>());
            content_ = json["content"];
        } else {
            throw std::invalid_argument("Invalid JSON");
        }
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid JSON");
    }
}

Message::Message(const std::string& str)
    : Message(nlohmann::json::parse(str)) {}

Message::~Message() = default;

MessageType Message::getType() const { return type_; }

nlohmann::json Message::getContent() const { return content_; }

nlohmann::json Message::toJson() const {
  nlohmann::json json;
  json["type"] = type_;
  json["content"] = content_;
  return json;
}

std::string Message::toString() const { return toJson().dump(); }

