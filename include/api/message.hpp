#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <nlohmann/json.hpp>

/**
 * @enum MessageType
 * @brief Enum representing different types of messages.
 */
enum class MessageType {
    UNKNOWN, ///< Unknown message type
    ADD_USER, ///< Message type for adding a user
    REMOVE_USER, ///< Message type for removing a user
    USER_EXISTS, ///< Message type for checking if a user exists
    GET_USER, ///< Message type for getting a user
    AUTHENTICATE, ///< Message type for authenticating a user
    ADD_USER_TAG, ///< Message type for adding a tag to a user
    REMOVE_USER_TAG, ///< Message type for removing a tag from a user
    GET_USER_TAGS, ///< Message type for getting tags of a user
};

/**
 * @class Message
 * @brief Class representing a message with a type and content.
 */
class Message {
public:
    /**
     * @brief Constructs a Message with a specified type and content.
     * @param type The type of the message.
     * @param content The content of the message in JSON format.
     */
    explicit Message(MessageType type, nlohmann::json content);

    /**
     * @brief Constructs a Message from a JSON object.
     * @param json The JSON object containing the message data.
     */
    explicit Message(const nlohmann::json&json);

    /**
     * @brief Destructor for the Message class.
     */
    ~Message();

    /**
     * @brief Gets the type of the message.
     * @return The type of the message.
     */
    [[nodiscard]] MessageType getType() const;

    /**
     * @brief Gets the content of the message.
     * @return The content of the message in JSON format.
     */
    [[nodiscard]] nlohmann::json getContent() const;

    /**
     * @brief Converts the message to a JSON object.
     * @return The JSON representation of the message.
     */
    [[nodiscard]] nlohmann::json toJson() const;

private:
    MessageType type_; ///< The type of the message
    nlohmann::json content_; ///< The content of the message in JSON format
};

#endif //MESSAGE_HPP
