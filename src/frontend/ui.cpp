#include "ui.h"

std::string UI::currentUsername;

UI::UI() { client_ = Client("tcp://localhost:5555"); }

bool UI::addUser(const std::string& username, const std::string& password) {
  currentUsername = username;
  return true;
}

bool UI::removeUser(const std::string& username) { return true; }

bool UI::authenticateUser(const std::string& username,
                          const std::string& password) {
  return true;
}

bool UI::addUserTag(const std::string& username, const std::string& tag) {
  return true;
}

bool UI::removeUserTag(const std::string& username, const std::string& tag) {
  return true;
}

std::vector<std::string> UI::getUserTags(const std::string& username) {
  return std::vector<std::string>();
}

bool UI::sendMessage(const std::string& from, const std::string& to,
                     const std::string& message) {
  return true;
}

std::vector<std::string> UI::getSentMessages(const std::string& username) {
  return {"sent1", "sent2"};
}

std::vector<std::string> UI::getReceivedMessages(const std::string& username) {
  return {"recv1", "recv2"};
}

std::vector<std::string> UI::getPair(const std::string& username) {
  return {"pair1", "pair2"};
}
