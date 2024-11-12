#include "api/message.hpp"

#include <nlohmann/json.hpp>
#include <utility>

Message::Message(MessageType type, nlohmann::json content) : type_(type), content_(std::move(content)) {
}

Message::Message(const nlohmann::json&json) {
    type_ = static_cast<MessageType>(json["type"].get<int>());
    content_ = json["content"];
}

Message::~Message() = default;

MessageType Message::getType() const {
    return type_;
}

nlohmann::json Message::getContent() const {
    return content_;
}

nlohmann::json Message::toJson() const {
    nlohmann::json json;
    json["type"] = type_;
    json["content"] = content_;
    return json;
}
