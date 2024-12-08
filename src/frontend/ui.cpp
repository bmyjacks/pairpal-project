#include "ui.h"

std::string UI::currentUsername;
Client UI::client_ = Client("tcp://localhost:30200");

UI::UI() { client_.start(); }

bool UI::addUser(const std::string& username, const std::string& password) {
  currentUsername = username;
  return client_.addUser(username, password);
}

bool UI::removeUser(const std::string& username) {
  return client_.removeUser(username);
}

bool UI::authenticateUser(const std::string& username,
                          const std::string& password) {
  return client_.authenticateUser(username, password);
}

bool UI::addUserTag(const std::string& username, const std::string& tag) {
  return client_.addUserTag(username, tag);
}

bool UI::removeUserTag(const std::string& username, const std::string& tag) {
  return client_.removeUserTag(username, tag);
}

std::vector<std::string> UI::getUserTags(const std::string& username) {
  return client_.getUserTags(username);
}

bool UI::sendMessage(const std::string& from, const std::string& to,
                     const std::string& message) {
  return client_.sendMessage(from, to, message);
}

std::vector<std::string> UI::getSentMessages(const std::string& username) {
  return client_.getSentMessages(username);
}

std::vector<std::string> UI::getReceivedMessages(const std::string& username) {
  return client_.getReceivedMessages(username);
}

std::vector<std::string> UI::getPair(const std::string& username) {
  return client_.getPair(username);
}
