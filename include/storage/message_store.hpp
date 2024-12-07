#ifndef MESSAGE_STORE_HPP
#define MESSAGE_STORE_HPP
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <sqlite3.h>
class Message_store {
public:
    Message_store();
    ~Message_store();
    bool addMessage(const std::string& fromUser, const std::string& toUser, const std::string& messageconst, std::string& timeStamp);
    std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> getMessages();
    //可以加个撤回


private:
    sqlite3* db;
};
#endif // MESSAGE_STORE_HPP