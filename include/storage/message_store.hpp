#ifndef MESSAGE_STORE_HPP
#define MESSAGE_STORE_HPP
#include <vector>
#include <tuple>
#include <string>
#include <map>

class message_store {
public:
    message_store();
    ~message_store();
    bool addMessage(const std::string& fromUser, const std::string& toUser, const std::string& message);
    std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> Message_store::getMessages();
    //可以加个撤回

};

#endif // MESSAGE_STORE_HPP