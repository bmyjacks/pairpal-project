#include "ui.h"

std::string UI::currentUsername;
Client UI::client = Client("tcp://localhost:57880");

UI::UI() { client.start(); }

bool UI::addUser(const std::string& username, const std::string& password) {
  currentUsername = username;
  return client.addUser(username, password);
}

bool UI::removeUser(const std::string& username) {
  return client.removeUser(username);
}

bool UI::authenticateUser(const std::string& username,
                          const std::string& password) {
  currentUsername = username;
  return client.authenticateUser(username, password);
}

bool UI::addUserTag(const std::string& username, const std::string& tag) {
  return client.addUserTag(username, tag);
}

bool UI::removeUserTag(const std::string& username, const std::string& tag) {
  return client.removeUserTag(username, tag);
}

std::vector<std::string> UI::getUserTags(const std::string& username) {
  return client.getUserTags(username);
}

bool UI::sendMessage(const std::string& from, const std::string& to,
                     const std::string& message) {
  return client.sendMessage(from, to, message);
}

std::vector<std::string> UI::getSentMessages(const std::string& username) {
  return client.getSentMessages(username);
}

std::vector<std::string> UI::getReceivedMessages(const std::string& username) {
  return client.getReceivedMessages(username);
}

std::vector<std::string> UI::getPair(const std::string& username) {
  return client.getPair(username);
}
