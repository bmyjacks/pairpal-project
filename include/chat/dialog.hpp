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

#endif  // DIALOG_HPP