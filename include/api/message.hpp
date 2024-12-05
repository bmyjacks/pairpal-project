#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <cstdint>
#include <nlohmann/json.hpp>
#include <zmq.hpp>

/**
 * @enum MessageType
 * @brief Enum representing different types of messages.
 */
enum class MessageType : uint8_t {
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
                                  nlohmann::json content);

  explicit Message(const MessageType& type);

  /**
   * @brief Constructs a Message from a JSON object.
   * @param json The JSON object containing the message data.
   */
  [[deprecated]] explicit Message(const nlohmann::json& json);

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
  [[nodiscard]] auto getType() const -> MessageType;

  /**
   * @brief Gets the content of the message.
   * @return The content of the message in JSON format.
   */
  [[deprecated, nodiscard]] auto getContent() const -> nlohmann::json;

  /**
   * @brief Converts the message to a JSON object.
   * @return The JSON representation of the message.
   */
  [[nodiscard]] auto toJson() const -> nlohmann::json;

  /**
   * @brief Converts the message to a string.
   * @return The string representation of the message.
   */
  [[nodiscard]] auto toString() const -> std::string;

  [[nodiscard]] auto toZmqMessage() const -> std::unique_ptr<zmq::message_t>;

  void setUsername(const std::string& username);
  [[nodiscard]] auto getUsername() const -> std::string;

  void setPassword(const std::string& password);
  [[nodiscard]] auto getPassword() const -> std::string;

  void setTag(const std::string& tag);
  [[nodiscard]] auto getTag() const -> std::string;

  void setFrom(const std::string& from);
  [[nodiscard]] auto getFrom() const -> std::string;

  void setTo(const std::string& to);
  [[nodiscard]] auto getTo() const -> std::string;

  void setMessage(const std::string& message);
  [[nodiscard]] auto getMessage() const -> std::string;

  void setVector(const std::vector<std::string>& vector);
  [[nodiscard]] auto getVector() const -> std::vector<std::string>;

 private:
  MessageType type_;        ///< The type of the message
  nlohmann::json content_;  ///< The content of the message in JSON format
};

#endif  // MESSAGE_HPP
