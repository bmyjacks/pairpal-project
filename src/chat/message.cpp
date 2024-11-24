/**包括消息的内容、发送者、接收者等
*/
#include "chat/message.hpp"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>


/**
 * @brief Constructs a Message object with the given sender, receiver, and message content.
 * @param from The username of the sender.
 * @param to The username of the receiver.
 * @param message The content of the message.
 */
Message::Message(std::string from, std::string to, std::string message)
    : from(std::move(from)), to(std::move(to)), message(std::move(message)) {
    // Set the timestamp to the current time when the message is created
    timestamp = std::chrono::system_clock::now();
}

/**
 * @brief Destroys the Message object.
 */
Message::~Message() = default;

/**
 * @brief Gets the username of the sender.
 * @return The username of the sender.
 */
std::string Message::getFromUser() const {
    return from;
}

/**
 * @brief Gets the username of the receiver.
 * @return The username of the receiver.
 */
std::string Message::getToUser() const {
    return to;
}

/**
 * @brief Gets the content of the message.
 * @return The content of the message.
 */
std::string Message::getMessage() const {
    return message;
}

/**
 * @brief Converts the message to a string representation.
 * @return A string representation of the message.
 */
std::string Message::toString() const {
    std::ostringstream oss;

    // Convert the timestamp to a string
    auto time = std::chrono::system_clock::to_time_t(timestamp);
    std::tm* localTime = std::localtime(&time);
    oss << "[" << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << "] "
        << from << " -> " << to << ": " << message;

    return oss.str();
}

/**
 * @brief Gets the timestamp of when the message was sent.
 * @return The timestamp of the message.
 */
std::chrono::system_clock::time_point Message::getTimestamp() const {
    return timestamp;
}


/**
 * @brief Compares the current message timestamp with another message's timestamp.
 * @param other The other message to compare with.
 * @return True if the current message was sent before the other message.
 */
bool Message::isBefore(const Message& other) const {
    return timestamp < other.timestamp;
}

