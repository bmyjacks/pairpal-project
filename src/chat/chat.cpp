#include "chat/chat.hpp"
#include "chat/dialog.hpp"
#include "chat/message.hpp"
Chat::Chat() 
    : messageStore_(std::make_unique<Message_store>())
{ }


bool Chat::sendMessage(const std::string &from, const std::string &to, const std::string &message) {
// whether the user exists
if (users_.find(from) == users_.end() || users_.find(to) == users_.end()) {
    return false;
}
    // create or get the existing Dialog object
    Dialog& dialog = dialogs_[std::make_pair(from, to)];
    // use the Dialog to send the message
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

