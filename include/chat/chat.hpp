#ifndef CHAT_HPP
#define CHAT_HPP

#include <string>

class Chat {
public:
    Chat();

    ~Chat();

    bool sendMessage(const std::string&message);
};

#endif //CHAT_HPP
