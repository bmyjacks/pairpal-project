#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <chrono>
#include <string>

/**
 * @class Message
 * @brief Represents a message exchanged between two users.
 */
class Message {
 public:
  /**
   * @brief Constructs a Message object.
   * @param from The username of the sender.
   * @param to The username of the receiver.
   * @param message The content of the message.
   */
  Message(std::string from, std::string to, std::string message);

  /**
   * @brief Destroys the Message object.
   */
  ~Message();

  /**
   * @brief Gets the username of the sender.
   * @return The username of the sender.
   */
  [[nodiscard]] std::string getFromUser() const;

  /**
   * @brief Gets the username of the receiver.
   * @return The username of the receiver.
   */
  [[nodiscard]] std::string getToUser() const;

  /**
   * @brief Gets the content of the message.
   * @return The content of the message.
   */
  [[nodiscard]] std::string getMessage() const;

  /**
   * @brief Converts the message to a string representation.
   * @return A string representation of the message.
   */
  [[nodiscard]] std::string toString() const;

  /**
   * @brief Gets the timestamp of when the message was sent.
   * @return The timestamp of the message.
   */
  [[nodiscard]] std::chrono::system_clock::time_point getTimestamp() const;

private:
  std::string from;   // Sender's username
  std::string to;     // Receiver's username
  std::string message; // Content of the message
  std::chrono::system_clock::time_point timestamp; // Timestamp of the message
};
#endif  // MESSAGE_HPP