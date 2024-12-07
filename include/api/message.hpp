#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <nlohmann/json.hpp>
#include <zmq.hpp>

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
  [[deprecated]] explicit Message(const MessageType& type,
                                  nlohmann::json content) noexcept;

  explicit Message(const MessageType& type) noexcept;

  /**
   * @brief Constructs a Message from a JSON object.
   * @param json The JSON object containing the message data.
   */
  [[deprecated]] explicit Message(const nlohmann::json& json) noexcept;

  /**
   * @brief Constructs a Message from a string.
   * @param str The string containing the message data.
   */
  explicit Message(const std::string& str) noexcept;

  /**
   * @brief Destructor for the Message class.
   */
  ~Message();

  /**
   * @brief Gets the type of the message.
   * @return The type of the message.
   */
  [[nodiscard]] MessageType getType() const noexcept;

  /**
   * @brief Gets the content of the message.
   * @return The content of the message in JSON format.
   */
  [[nodiscard]] nlohmann::json getContent() const noexcept;

  /**
   * @brief Converts the message to a JSON object.
   * @return The JSON representation of the message.
   */
  [[nodiscard]] nlohmann::json toJson() const noexcept;

  /**
   * @brief Converts the message to a string.
   * @return The string representation of the message.
   */
  [[nodiscard]] std::string toString() const noexcept;

  [[nodiscard]] std::unique_ptr<zmq::message_t> toZmqMessage() const noexcept;

  void setUsername(const std::string& username) noexcept;
  void setPassword(const std::string& password) noexcept;
  void setTag(const std::string& tag) noexcept;
  void setFrom(const std::string& from) noexcept;
  void setTo(const std::string& to) noexcept;
  void setMessage(const std::string& message) noexcept;
  void setVector(const std::vector<std::string>& vector) noexcept;

  [[nodiscard]] std::string getUsername() const noexcept;
  [[nodiscard]] std::string getPassword() const noexcept;
  [[nodiscard]] std::string getTag() const noexcept;
  [[nodiscard]] std::string getFrom() const noexcept;
  [[nodiscard]] std::string getTo() const noexcept;
  [[nodiscard]] std::string getMessage() const noexcept;
  [[nodiscard]] std::vector<std::string> getVector() const noexcept;

 private:
  MessageType type_;        ///< The type of the message
  nlohmann::json content_;  ///< The content of the message in JSON format

};

#endif  // MESSAGE_HPP
