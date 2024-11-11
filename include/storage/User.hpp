#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
 public:
  User();

  ~User();

  bool setUsername(const std::string& username);

  [[nodiscard]] std::string getUsername() const;

  bool setTags(const std::string& tags);

  [[nodiscard]] std::string getTags() const;
};

#endif  // USER_HPP
