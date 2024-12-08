#include "chat.hpp"
#include "message.hpp"
#include "dialog.hpp"

Chat::Chat()
    : messageStore_(std::make_unique<Message_store>())
{ }

bool Chat::sendMessage(const std::string &from, const std::string &to, const std::string &message) {
  auto key = std::make_pair(from, to);
  // Try to emplace a new Dialog if it doesn't exist
  auto& dialog = dialogs_.try_emplace(key, from, to).first->second;
  dialog.sendMessage(from, message);
  return true;
}

std::vector<Message> Chat::getSentMessages(const std::string &username) const {
    std::vector<Message> messages;
    for (const auto& pair : dialogs_) {
        const Dialog& dialog = pair.second;
        std::vector<Message> dialogMessages = dialog.getAllMessages();
        for (const auto& message : dialogMessages) {
            if (message.getFromUser() == username) {
                messages.push_back(message);
            }
        }
    }
    return messages;
}

std::vector<Message> Chat::getReceivedMessages(const std::string &username) const {
    std::vector<Message> messages;
    for (const auto& pair : dialogs_) {
        const Dialog& dialog = pair.second;
        std::vector<Message> dialogMessages = dialog.getAllMessages();
        for (const auto& message : dialogMessages) {
            if (message.getToUser() == username) {
                messages.push_back(message);
            }
        }
    }
    return messages;
}

Chat::~Chat() = default;

