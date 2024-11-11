#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
public:
    User();

    ~User();

    bool setUsername(const std::string&username);

    [[nodiscard]] std::string getUsername() const;

    bool sendMessage(const std::string&message);
};

#endif //USER_HPP
