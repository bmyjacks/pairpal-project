#include "message.hpp"
#include <chrono>
#include <string>


/**
 * @brief Constructs a Message object.
 * @param from The username of the sender.
 * @param to The username of the receiver.
 * @param message The content of the message.
 */
Message::Message(std::string from, std::string to, std::string message)
    : from(std::move(from)), to(std::move(to)), message(std::move(message)) {
    timestamp = std::chrono::system_clock::now();
}


/**
 * @brief destructor
 */
Message::~Message() = default;

/**
 * @brief get the type of message
 * @return the type of message
 */
std::string Message::getFromUser() const {
    return from;
}

/**
 * @brief get the content of the message
 * @return the content of the message
 */
std::string Message::getMessage() const {
    return message;
}

/**
 * @brief get the username of the receiver
 * @return the username of the receiver
 */
std::string Message::getToUser() const {
    return to;
}
/**
 * @brief Convert the message to a string representation.
 * @return A string representation of the message.
 */
std::string Message::toString() const {
    return "From: " + from + "\nTo: " + to + "\nMessage: " + message;
}


/**
 * @brief get the timestamp of when the message was sent
 * @return the timestamp of the message
 */
std::chrono::system_clock::time_point Message::getTimestamp() const {
    return timestamp;
}
/**
 * @brief Converts the timestamp to a string.
 * @return A string representation of the timestamp.
 */
std::string Message::getFormatTimestamp() const {
    auto time = std::chrono::system_clock::to_time_t(timestamp);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
