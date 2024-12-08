#include "message_store.hpp"
#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <tuple>
#include <string>



Message_store::Message_store() {
    int return_code = sqlite3_open("message_store.db", &db);
    if (return_code != SQLITE_OK) {
        std::cerr << "Error opening message_store.db" << std::endl;
        sqlite3_close(db);
        return;
    }else{
        std::cout << "Opened message_store.db successfully" << std::endl;
    }




const char* create_tableSQL = R"(CREATE TABLE IF NOT EXISTS Messages (ID INTEGER PRIMARY KEY,
                                    FromUser TEXT NOT NULL,
                                    ToUser TEXT NOT NULL,
                                    Message TEXT NOT NULL,
                                    TimeStamp DATETIME DEFAULT CURRENT_TIMESTAMP))";

if (sqlite3_exec(db, create_tableSQL, nullptr, nullptr, nullptr) != SQLITE_OK) {
    std::cerr << "Error creating message_store table" << std::endl;
    sqlite3_close(db);
}else{
    std::cout << "Message_store Table created successfully" << std::endl;
}

}

Message_store::~Message_store() {
    sqlite3_close(db);
    std::cout << "Message_store closed successfully" << std::endl;
}

bool Message_store::addMessage(const std::string& fromUser, const std::string& toUser, const std::string& message,  std::string& timeStamp) {

    if(!db){
        std::cerr << "Error opening message_store.db" << std::endl;
        return false;
    }
    const char* insertSQL = "INSERT INTO Messages (FromUser, ToUser, Message, TimeStamp) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement" << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, fromUser.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, toUser.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, message.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, timeStamp.c_str(), -1, SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error executing statement" << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}
 std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> Message_store::getMessages(){
    std::vector<std::tuple<int, std::string, std::string, std::string, std::string>> messages;
    const char* selectSQL = "SELECT * FROM Messages;";
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing statement" << std::endl;
        return messages;
    }
    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string fromUser = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string toUser = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string message = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string timeStamp = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        messages.emplace_back(id, fromUser, toUser, message, timeStamp);
    }
    sqlite3_finalize(stmt);
    return messages;
 }





