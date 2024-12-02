#ifndef CHAT_HPP
#define CHAT_HPP

#include <vector>

#include "chat/message.hpp"

/**
 * @class Chat
 * @brief A class to handle chat functionalities including sending and
 * retrieving messages.
 */
class Chat {
 public:
  /**
   * @brief Constructor for the Chat class.
   */
  Chat();

  /**
   * @brief Destructor for the Chat class.
   */
  ~Chat();

  /**
   * @brief Sends a message from one user to another.
   * @param from The username of the sender.
   * @param to The username of the receiver.
   * @param message The content of the message to be sent.
   * @return True if the message was sent successfully, false otherwise.
   */
  bool sendMessage(const std::string &from, const std::string &to,
                   const std::string &message);

  /**
   * @brief Retrieves the messages sent by a specific user.
   * @param username The username of the sender.
   * @return A vector of messages sent by the specified user.
   */
  [[nodiscard]] std::vector<Message> getSentMessages(
      const std::string &username) const;

  /**
   * @brief Retrieves the messages received by a specific user.
   * @param username The username of the receiver.
   * @return A vector of messages received by the specified user.
   */
  [[nodiscard]] std::vector<Message> getReceivedMessages(
      const std::string &username) const;
};

#endif  // CHAT_HPP