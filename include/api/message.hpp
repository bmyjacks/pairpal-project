#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <nlohmann/json.hpp>

/**
 * @enum MessageType
 * @brief Enum representing different types of messages.
 */
enum class MessageType {
  SUCCESS,                ///< Message type for successful operations
  FAILURE,                ///< Message type for failed operations
  UNKNOWN,                ///< Unknown message type
  ADD_USER,               ///< Message type for adding a user
  REMOVE_USER,            ///< Message type for removing a user
  IS_EXIST_USER,          ///< Message type for checking if a user exists
  LIST_ALL_USERS,         ///< Message type for getting a user
  AUTHENTICATE_USER,      ///< Message type for authenticating a user
  ADD_USER_TAG,           ///< Message type for adding a tag to a user
  REMOVE_USER_TAG,        ///< Message type for removing a tag from a user
  GET_USER_TAGS,          ///< Message type for getting tags of a user
  SEND_MESSAGE,           ///< Message type for sending a message
  GET_SENT_MESSAGES,      ///< Message type for getting all sent messages
  GET_RECEIVED_MESSAGES,  ///< Message type for getting all received messages
  GET_PAIR                ///< Message type for getting the pair of a user
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
  explicit Message(const nlohmann::json& json);

  /**
   * @brief Constructs a Message from a string.
   * @param str The string containing the message data.
   */
  explicit Message(const std::string& str);

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

  /**
   * @brief Converts the message to a string.
   * @return The string representation of the message.
   */
  [[nodiscard]] std::string toString() const;

 /**
 * @brief Compares the current message timestamp with another message's timestamp.
 * @param other The other message to compare with.
 * @return True if the current message was sent before the other message.
 */
 [[nodiscard]] bool isBefore(const Message& other) const;

 private:
  MessageType type_;        ///< The type of the message
  nlohmann::json content_;  ///< The content of the message in JSON format
};

#endif  // MESSAGE_HPP
