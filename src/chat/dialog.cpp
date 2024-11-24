#include "chat/dialog.hpp"
#include <utility>
#include <iostream>

/**
 * @brief Constructs a Dialog object.
 * @param from The username of the sender.
 * @param to The username of the receiver.
 */
Dialog::Dialog(std::string from, std::string to)
    : users{std::move(from), std::move(to)} {
    // 初始化对话对象时，存储参与对话的两个用户
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
    return users[0];  // 假设第一个用户为发送者
}

/**
 * @brief Gets the username of the receiver.
 * @return The username of the receiver.
 */
std::string Dialog::getToUser() const {
    return users[1];  // 假设第二个用户为接收者
}

/**
 * @brief Gets all messages in the dialog.
 * @return A vector containing all messages.
 */
std::vector<Message> Dialog::getAllMessages() const {
    return messages;
}

/**
 * @brief Sends a message in the dialog.
 * @param sender The username of the sender.
 * @param messageContent The content of the message to be sent.
 * @return True if the message was sent successfully, false otherwise.
 */
bool Dialog::sendMessage(const std::string& sender, std::string messageContent) {
    // 验证发送者是否在对话用户中
    if (sender != users[0] && sender != users[1]) {
        std::cerr << "Invalid sender: " << sender << " is not part of this dialog." << std::endl;
        return false;  // 如果发送者不在对话的用户列表中，发送失败
    }

    // 如果当前消息数量已达到上限20条，弹窗询问用户是否继续
    if (messages.size() >= 20) {
        std::cout << "消息数量已达到上限（20条）。请确认聊天是否需要继续？(y/n): ";
        char user1Response, user2Response;

        // 询问第一个用户
        std::cout << users[0] << "，消息数量已达到上限。是否同意继续？(y/n): ";
        std::cin >> user1Response;
        if (user1Response != 'y' && user1Response != 'Y') {
            std::cout << users[0] << "不同意继续发送消息。" << std::endl;
            return false;  // 第一个用户不同意，返回 false 表示消息未发送
        }

        // 询问第二个用户
        std::cout << users[1] << "，消息数量已达到上限。是否同意继续？(y/n): ";
        std::cin >> user2Response;
        if (user2Response != 'y' && user2Response != 'Y') {
            std::cout << users[1] << "不同意继续发送消息。" << std::endl;
            return false;  // 第二个用户不同意，返回 false 表示消息未发送
        }
    }

    // 创建新消息并添加到消息列表
    Message newMessage(sender, "All", std::move(messageContent));  // "All" 表示所有用户都能看到
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
 * @brief Searches for messages containing the specified keyword.
 * @param keyword The keyword to search for.
 * @return A vector containing all messages that contain the keyword.
 */
std::vector<Message> Dialog::searchMessages(const std::string& keyword) const {
    std::vector<Message> foundMessages;

    // 遍历所有消息，查找包含关键字的消息
    for (const auto& message : messages) {
        if (message.getMessage().find(keyword) != std::string::npos) {
            foundMessages.push_back(message);
        }
    }

    return foundMessages;
}
/**
 * @brief Displays all messages in the dialog in a formatted manner.
 * 格式化输出消息，包括发送者、时间戳和内容
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