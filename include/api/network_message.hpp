#ifndef NETWORK_MESSAGE_HPP
#define NETWORK_MESSAGE_HPP

#include <cstdint>
#include <nlohmann/json.hpp>
#include <zmq.hpp>

/**
 * @enum NetworkMessageType
 * @brief Enum representing different types of messages.
 */
enum class NetworkMessageType : uint8_t {
  SUCCESS,            ///< NetworkMessage type for successful operations
  FAILURE,            ///< NetworkMessage type for failed operations
  UNKNOWN,            ///< Unknown message type
  ADD_USER,           ///< NetworkMessage type for adding a user
  REMOVE_USER,        ///< NetworkMessage type for removing a user
  IS_EXIST_USER,      ///< NetworkMessage type for checking if a user exists
  LIST_ALL_USERS,     ///< NetworkMessage type for getting a user
  AUTHENTICATE_USER,  ///< NetworkMessage type for authenticating a user
  ADD_USER_TAG,       ///< NetworkMessage type for adding a tag to a user
  REMOVE_USER_TAG,    ///< NetworkMessage type for removing a tag from a user
  GET_USER_TAGS,      ///< NetworkMessage type for getting tags of a user
  SEND_MESSAGE,       ///< NetworkMessage type for sending a message
  GET_SENT_MESSAGES,  ///< NetworkMessage type for getting all sent messages
  GET_RECEIVED_MESSAGES,  ///< NetworkMessage type for getting all received
                          ///< messages
  GET_PAIR  ///< NetworkMessage type for getting the pair of a user
};

/**
 * @class NetworkMessage
 * @brief Class representing a message with a type and content.
 */
class NetworkMessage {
 public:
  /**
   * @brief Constructs a NetworkMessage with a specified type and content.
   * @param type The type of the message.
   * @param content The content of the message in JSON format.
   */
  [[deprecated]] explicit NetworkMessage(const NetworkMessageType& type,
                                         nlohmann::json content);

  /**
   * @brief Constructs a NetworkMessage with a specified type.
   * @param type The type of the message.
   */
  explicit NetworkMessage(const NetworkMessageType& type);

  /**
   * @brief Constructs a NetworkMessage from a JSON object.
   * @param json The JSON object containing the message data.
   */
  [[deprecated]] explicit NetworkMessage(const nlohmann::json& json);

  /**
   * @brief Constructs a NetworkMessage from a string.
   * @param str The string containing the message data.
   */
  explicit NetworkMessage(const std::string& str);

  /**
   * @brief Destructor for the NetworkMessage class.
   */
  ~NetworkMessage();

  /**
   * @brief Gets the type of the message.
   * @return The type of the message.
   */
  [[nodiscard]] auto getType() const -> NetworkMessageType;

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

  /**
   * @brief Converts the message to a ZMQ message.
   * @return A unique pointer to the ZMQ message.
   */
  [[nodiscard]] auto toZmqMessage() const -> std::unique_ptr<zmq::message_t>;

  /**
   * @brief Sets the username associated with the message.
   * @param username The username to set.
   */
  void setUsername(const std::string& username);

  /**
   * @brief Gets the username associated with the message.
   * @return The username.
   */
  [[nodiscard]] auto getUsername() const -> std::string;

  /**
   * @brief Sets the password associated with the message.
   * @param password The password to set.
   */
  void setPassword(const std::string& password);

  /**
   * @brief Gets the password associated with the message.
   * @return The password.
   */
  [[nodiscard]] auto getPassword() const -> std::string;

  /**
   * @brief Sets the tag associated with the message.
   * @param tag The tag to set.
   */
  void setTag(const std::string& tag);

  /**
   * @brief Gets the tag associated with the message.
   * @return The tag.
   */
  [[nodiscard]] auto getTag() const -> std::string;

  /**
   * @brief Sets the sender of the message.
   * @param from The sender to set.
   */
  void setFrom(const std::string& from);

  /**
   * @brief Gets the sender of the message.
   * @return The sender.
   */
  [[nodiscard]] auto getFrom() const -> std::string;

  /**
   * @brief Sets the recipient of the message.
   * @param to The recipient to set.
   */
  void setTo(const std::string& to);

  /**
   * @brief Gets the recipient of the message.
   * @return The recipient.
   */
  [[nodiscard]] auto getTo() const -> std::string;

  /**
   * @brief Sets the message content.
   * @param message The message content to set.
   */
  void setMessage(const std::string& message);

  /**
   * @brief Gets the message content.
   * @return The message content.
   */
  [[nodiscard]] auto getMessage() const -> std::string;

  /**
   * @brief Sets a vector of strings associated with the message.
   * @param vector The vector of strings to set.
   */
  void setVector(const std::vector<std::string>& vector);

  /**
   * @brief Gets the vector of strings associated with the message.
   * @return The vector of strings.
   */
  [[nodiscard]] auto getVector() const -> std::vector<std::string>;

 private:
  NetworkMessageType type_;  ///< The type of the message
  nlohmann::json content_;   ///< The content of the message in JSON format
};

#endif  // NETWORK_MESSAGE_HPP
