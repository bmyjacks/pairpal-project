#include "api/message.hpp"

Message::Message() : type_(MessageType::UNKNOWN) {
}

Message::Message(MessageType type, const std::string&content) : type_(type) {
    // Set content_
}

Message::Message(const std::string&json) {
    // Parse json and set type_
}

Message::~Message() = default;

std::string Message::toJson() const {
    // Return json representation of the message
    return "";
}
