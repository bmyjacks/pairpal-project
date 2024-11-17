#include "storage/storage.hpp"

#include <iostream>

#include <storage/sqlite3.h>
Storage::Storage() {
  std::cout << "Storage constructor" << std::endl;
  int exit = sqlite3_open("storage_test.db", &db);
  if (exit != SQLITE_OK) {
    std::cerr << "Error opening database" << std::endl;
  }
  else {
    std::cout << "Opened database successfully" << std::endl;
  }
  //先打开数据库
  const char* create_tableSQL = R"(CREATE TABLE IF NOT EXISTS Users_list (ID INTEGER PRIMARY KEY,
                                    Name TEXT NOT NULL, Password TEXT NOT NULL);)";
  if(sqlite3_exec(db, create_tableSQL, nullptr, nullptr, nullptr) != SQLITE_OK) {
    std::cerr << "Error creating table" << std::endl;
    sqlite3_close(db);
  }
  else {
    std::cout << "Table created successfully" << std::endl;
  }
}


Storage::~Storage() {
  std::cout << "Storage destructor" << std::endl;
  sqlite3_close(db);
  std::cout << "Closed database successfully" << std::endl;
}
bool Storage::addUser(const std::string& username, const std::string& password) {
  if(!db) {
    std::cout<<"Error opening database"<<std::endl;
    return false;
  }
  const char* insertSQL = "INSERT INTO Users_list (Name, Password) VALUES (?,?);";
  sqlite3_stmt *stmt;
  if(sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cout<<"Error preparing statement"<<std::endl;
    return false;
  }
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
  if(sqlite3_step(stmt) != SQLITE_DONE) {
    std::cout<<"Error executing statement"<<std::endl;
    sqlite3_finalize(stmt);
    return false;
  }
  sqlite3_finalize(stmt);
  std::cout<<"Successfully added"<<std::endl;
  return true;
}
