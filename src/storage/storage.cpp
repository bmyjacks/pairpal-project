#include "storage/storage.hpp"

#include <iostream>

#include <storage/sqlite3.h>
Storage::Storage() {
  std::cout << "Storage constructor" << std::endl;
  int exit = sqlite3_open("storage_test.db", &db);
  if (exit != SQLITE_OK) {
    std::cerr << "Error opening database" << std::endl;
    return;
  }
  else {
    std::cout << "Opened database successfully" << std::endl;
  }
  //先打开数据库
  const char* create_tableSQL = R"(CREATE TABLE IF NOT EXISTS Users_list (ID INTEGER PRIMARY KEY,
                                    Name TEXT NOT NULL, Password TEXT NOT NULL, Tag TEXT NOT NULL DEFAULT ' ');)";
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
bool Storage::addUser(const std::string& username, const std::string& password) {//准备增加一个拒绝重复用户名的功能
  if(!db) {
    std::cout<<"Error opening database"<<std::endl;
    return false;
  }
  const char* selectsql="SELECT Password FROM Users_list WHERE Name=?;";
  sqlite3_stmt *stmt_0;
  if(sqlite3_prepare(db, selectsql, -1, &stmt_0, nullptr) != SQLITE_OK) {
    std::cerr<<"Error preparing statement"<<std::endl;
    return false;
  }
  sqlite3_bind_text(stmt_0, 1, username.c_str(), -1, nullptr);
  int qc=sqlite3_step(stmt_0);
  if(qc==SQLITE_ROW) {
    std::cout<<"the name has already been used!" << std::endl;
    sqlite3_finalize(stmt_0);
    return false;
  }
  else{  const char* insertSQL = "INSERT INTO Users_list (Name, Password) VALUES (?,?);";
    sqlite3_stmt *stmt;
    if(sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
      std::cout<<"Error preparing statement"<<std::endl;
      return false;
    }
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);
    if(sqlite3_step(stmt) != SQLITE_DONE) {
      std::cout<<"Error executing statement"<<std::endl;
      sqlite3_finalize(stmt_0);
      sqlite3_finalize(stmt);
      return false;
    }
    sqlite3_finalize(stmt);
    std::cout<<"The pass word is :"<< password << std::endl;
    std::cout<<"Successfully added"<<std::endl;
    return true;
  }

}
bool Storage::authenticateUser(const std::string& username, const std::string& password) {
  if (!db) {
    std::cerr << "Error: Database is not open! " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  const char* querySQL = "SELECT Password FROM Users_list WHERE Name = ?;";
  sqlite3_stmt* stmt;

  if (sqlite3_prepare_v2(db, querySQL, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Error preparing statement: " << sqlite3_errmsg(db) << std::endl;
    return false;
  }

  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

  int rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW) {
    // 获取密码字段
    const char* pw = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
    std::string cor_password = pw ? pw : "";

    // 密码验证
    if (cor_password == password) {
      std::cout << "Authentication successful." << std::endl;
      sqlite3_finalize(stmt);
      return true;
    } else {
      std::cout << "Wrong password. The correct password is: " << cor_password << std::endl;
      sqlite3_finalize(stmt);
      return false;
    }
  } if (rc == SQLITE_DONE) {
    std::cout << "No user found with the given username." << std::endl;
  } else {
    std::cerr << "Error executing statement: " << sqlite3_errmsg(db) << std::endl;
  }

  sqlite3_finalize(stmt);
  return false;
}
std::vector<std::tuple<int,std::string,std::string,std::string>> Storage::getUsers() {
  const char* sql = "SELECT ID,Name,Password,Tag FROM Users_list";
  sqlite3_stmt *stmt;
  std::vector<std::tuple<int,std::string,std::string,std::string>> result;
  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if(rc!=SQLITE_OK) {
    std::cerr<<"Error preparing statement"<<sqlite3_errmsg<<std::endl;
    return result;
  }
  while(sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
    std::string tag = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    result.emplace_back(id, name, password, tag);
  }
  sqlite3_finalize(stmt);
  return result;

};
bool Storage::removeUser(std::string username) {
  if (!db) {
    std::cerr<<"Error opening database"<<std::endl;
    return false;
  }
  const char* dsql = "DELETE FROM Users_list WHERE Name = ?;";
  sqlite3_stmt *stmt;
  if(sqlite3_prepare_v2(db, dsql, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr<<"Error preparing statement"<<std::endl;
  }
  if(sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC)!=SQLITE_OK) {
    std::cerr<<"Error binding text"<<std::endl;
    return false;
  }
  if(sqlite3_step(stmt)!=SQLITE_DONE) {
    std::cerr<<"Error executing statement"<<std::endl;
    return false;
  }
  if(sqlite3_changes(db)==0) {
    std::cerr <<"No user found with the given username." << std::endl;
    return false;
    sqlite3_finalize(stmt);
  }
  sqlite3_finalize(stmt);
  std::cout <<"Successfully delect the user." << std::endl;
  return true;
}
bool Storage::isUserExist(std::string username) {
  if(!db) {
    std::cerr<<"Error opening database"<<std::endl;
    return false;
  }
  const char* ssql = "SELECT ID FROM Users_list WHERE Name=?;";
  sqlite3_stmt *stmt;
  if(sqlite3_prepare_v2(db, ssql, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr<<"Error preparing statement"<<std::endl;
    return false;
  }
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
  int qc = sqlite3_step(stmt);
  if(qc==SQLITE_DONE) {
    //std::cout<< "User exits." << std::endl;
    return false;
  }
  else {
    //std::cout <<"The user exist" << std::endl;
    return true;
  }
}
bool Storage::addTag(std::string username, std::string tag) {
  if(!db) {
    std::cerr<<"Error opening database"<<std::endl;
    return false;
  }
  const char* sSQL = "SELECT Tag FROM Users_list WHERE Name=?;";
  sqlite3_stmt *stmt_s;
  if (sqlite3_prepare_v2(db, sSQL, -1, &stmt_s, nullptr) != SQLITE_OK) {
    std::cerr<<"Error preparing statement"<<std::endl;
    return false;
  }
  sqlite3_bind_text(stmt_s, 1, username.c_str(), -1, SQLITE_TRANSIENT);
  if(sqlite3_step(stmt_s)!=SQLITE_ROW) {
    std::cerr<<"Not find the users!"<<std::endl;
    sqlite3_finalize(stmt_s);
    return false;
  }
  else {
    const char* tag_old_0 = reinterpret_cast<const char*>(sqlite3_column_text(stmt_s, 0));
    std::string tag_old= tag_old_0;
    std::string tag_new;
    if(tag_old.find(tag) != std::string::npos) {
      std::cerr<<"Tag already exists."<<std::endl;
      sqlite3_finalize(stmt_s);
      return false;
    }
    if(tag_old==" ") {
      tag_new = tag;
    }
    else {
      tag_new = tag_old + "^^" + tag;
    }

    const char* updateSQL = "UPDATE Users_list SET Tag=? WHERE Name=?;";
    sqlite3_stmt* stmt_update;
    if(sqlite3_prepare_v2(db, updateSQL, -1, &stmt_update, nullptr) != SQLITE_OK) {
      std::cerr<<"Error preparing statement"<<std::endl;
      return false;
    }
    sqlite3_bind_text(stmt_update, 1, tag_new.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt_update, 2, username.c_str(), -1, SQLITE_STATIC);
    int qc=sqlite3_step(stmt_update);
    if(qc != SQLITE_DONE) {
      std::cerr<<"Error executing statement"<<std::endl;
      return false;
    }
    sqlite3_finalize(stmt_update);
    sqlite3_finalize(stmt_s);
    return true;
  }
}