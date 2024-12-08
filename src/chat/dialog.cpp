#include "chat/dialog.hpp"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

Dialog::Dialog() = default;

/**
 * @brief Constructs a Dialog object
 * @param user1 the first user
 * @param user2 the second user
 */
Dialog::Dialog(std::string user1, std::string user2)
    : users{std::move(user1), std::move(user2)} {
  // store the users
}

/**
 * @brief Destroys the Dialog object.
 */
Dialog::~Dialog() = default;

/**
 * @brief Gets the username of the sender.
 * @return The username of the sender.
 */
std::string Dialog::getFromUser() const {
  // assume that the users can switch roles in the current dialog
  // here return the first user as the default
  return users[0];
}

/**
 * @brief Gets the username of the receiver.
 * @return The username of the receiver.
 */
std::string Dialog::getToUser() const {
  // assume that the users can switch roles in the current dialog
  // here return the second user as the default
  return users[1];
}

/**
 * @brief Gets all messages in the dialog.
 * @return A vector containing all messages.
 */
std::vector<Message> Dialog::getAllMessages() const { return messages; }

/**
 * @brief Sends a message in the dialog.
 * @param sender The username of the sender.
 * @param message The content of the message to be sent.
 * @return True if the message was sent successfully, false otherwise.
 */
bool Dialog::sendMessage(const std::string& sender, std::string message) {
  // verify if the sender is in the dialog users
  if (sender != users[0] && sender != users[1]) {
    std::cerr << "Invalid sender: " << sender << " is not part of this dialog."
              << std::endl;
    return false;
  }

  // determine the receiver dynamically
  std::string receiver = (sender == users[0]) ? users[1] : users[0];

  //  create a new message and add it to the message list
  Message newMessage(sender, receiver, std::move(message));
  messages.push_back(newMessage);

  return true;
}

/**
 * @brief Deletes a message from the dialog.
 * @param index The index of the message to delete.
 * @return True if the message was deleted successfully, false otherwise.
 */
bool Dialog::deleteMessage(size_t index) {
  if (index < messages.size()) {
    messages.erase(messages.begin() + index);
    return true;
  } else {
    std::cerr << "Invalid index: Unable to delete message." << std::endl;
    return false;
  }
}

/**
 * @brief Displays all messages in the dialog in a formatted manner.
 * format the messages
 */
void Dialog::displayMessages() const {
  for (const auto& message : messages) {
    auto time = std::chrono::system_clock::to_time_t(message.getTimestamp());
    std::tm* Time = std::localtime(&time);
    std::cout << "[" << std::put_time(Time, "%Y-%m-%d %H:%M:%S") << "] "
              << std::setw(10) << std::left << message.getFromUser() << " : "
              << message.getMessage() << "\n";
  }
}