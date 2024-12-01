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
 std::vector<Message> messages;  // store the messages
 std::vector<std::string> users; // store the users
public:
 /**
  * @brief Constructs a Dialog object.
  * @param from The username of the sender.
  * @param to The username of the receiver.
  */
 Dialog(std::string from, std::string to);

 /**
  * @brief Destroy the Dialog object.
  */
 ~Dialog();

 /**
  * @brief get the username of the sender
  * @return the username of the sender
  */
 [[nodiscard]] std::string getFromUser() const;

 /**
  * @brief get the username of the receiver
  * @return the username of the receiver
  */
 [[nodiscard]] std::string getToUser() const;

 /**
  * @brief get all messages in the dialog
  * @return a vector containing all messages
  */
 [[nodiscard]] std::vector<Message> getAllMessages() const;

 /**
  * @brief Sends a message in the dialog.
  * @param message The message to be sent.
  * @param sender the message sender
  * @return true if the message was sent successfully, false otherwise
  */
 bool sendMessage(const std::string& sender, std::string message);

 void displayMessages() const;


 /**
  * @brief delete a message from the dialog
  * @param index the index of the message to delete
  * @return true if the message was deleted successfully, false otherwise
  */
 bool deleteMessage(size_t index);
};

#endif  // DIALOG_HPP