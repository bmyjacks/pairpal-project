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
                                    Name TEXT NOT NULL, Password TEXT NOT NULL, Tag TEXT NOT NULL DEFAULT '0000000');)";
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
  std::cout<<"The pass word is :"<< password << std::endl;
  std::cout<<"Successfully added"<<std::endl;
  return true;
}

bool Storage::authenticateUser(const std::string& username, const std::string& password) {
  if(!db) {
    std::cout<<"Error opening database"<<std::endl;
    return false;
  }
  const char* querySQL = "SELECT Password FROM Users_list WHERE Name=?; ";
  sqlite3_stmt *stmt;
  if(sqlite3_prepare_v2(db, querySQL, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cout<<"Error preparing statement"<<std::endl;
    return false;
  }
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  std::string cor_password;
  if(sqlite3_step(stmt) != SQLITE_ROW) {
    std::cout<<"Error executing statement"<<std::endl;
    return false;
  }
  if(sqlite3_step(stmt) == SQLITE_ROW) {
    const char* pw = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    if(pw) {
      cor_password = pw;
    }
    else {
      std::cout<<"Error getting the user's name"<<std::endl;
      return false;
    }
    if(cor_password == password) {
      return true;
    }
    if(cor_password != password) {
      std::cout<<"Wrong password"<<std::endl;
      std::cout << "THe correct password is:" << cor_password << std::endl;
      return false;
    }
  }
}