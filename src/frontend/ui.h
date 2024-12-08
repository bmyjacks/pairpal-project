#ifndef UI_H
#define UI_H

#include <string>
#include <vector>
#include <client.hpp>

class UI {
 public:
  UI();

  static Client client;

  static bool addUser(const std::string& username, const std::string& password);
    // 添加一个静态变量来存储当前用户名
  static std::string currentUsername;

  static bool removeUser(const std::string& username);

  static bool authenticateUser(const std::string& username,
                               const std::string& password);

  static bool addUserTag(const std::string& username, const std::string& tag);

  static bool removeUserTag(const std::string& username,
                            const std::string& tag);

  static std::vector<std::string> getUserTags(const std::string& username);

  static bool sendMessage(const std::string& from, const std::string& to,
                          const std::string& message);

  static std::vector<std::string> getSentMessages(const std::string& username);

  static std::vector<std::string> getReceivedMessages(
      const std::string& username);

  static std::vector<std::string> getPair(const std::string& username);
};

#endif  // UI_H
