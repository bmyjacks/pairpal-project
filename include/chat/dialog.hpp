#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <string>
#include <vector>

#include "message.hpp"

/**
 * @class Dialog
 * @brief Represents a dialog between two users.
 */
class Dialog {

private:
 std::vector<Message> messages;  // 用于存储对话中的消息
 std::vector<std::string> users; // 用于存储参与对话的用户
 public:
  /**
   * @brief Constructs a Dialog object.
   * @param from The username of the sender.
   * @param to The username of the receiver.
   */
  Dialog(std::string from, std::string to);

  /**
   * @brief Destroys the Dialog object.
   */
  ~Dialog();

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
   * @brief Gets all messages in the dialog.
   * @return A vector containing all messages.
   */
  [[nodiscard]] std::vector<Message> getAllMessages() const;

  /**
   * @brief Sends a message in the dialog.
   * @param message The message to be sent.
   * @return True if the message was sent successfully, false otherwise.
   */
  bool sendMessage(std::string message);
};

/**
 * @brief Deletes a message from the dialog.
 * @param index The index of the message to delete.
 * @return True if the message was deleted successfully, false otherwise.
 */
bool deleteMessage(size_t index);

/**
 * @brief Searches for messages containing the specified keyword.
 * @param keyword The keyword to search for.
 * @return A vector containing all messages that contain the keyword.
 */
[[nodiscard]] std::vector<Message> searchMessages(const std::string& keyword) const;

/**
 * @brief Displays all messages in the dialog in a formatted manner.
 */
void Dialog::displayMessages();
#endif  // DIALOG_HPP