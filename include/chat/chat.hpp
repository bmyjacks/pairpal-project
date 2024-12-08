#ifndef CHAT_HPP
#define CHAT_HPP

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "message.hpp"
#include "message_store.hpp"
#include "dialog.hpp"

/**
 * @class Chat
 * @brief A class to handle Chat_test functionalities including sending and
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

 private:
  std::unique_ptr<Message_store> messageStore_;
  //std::map<std::string, User> users_;
  std::map<std::pair<std::string, std::string>, Dialog> dialogs_;
};

#endif  // CHAT_HPP