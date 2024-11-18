#include <storage/sqlite3.h>

#include <iostream>
#include <ostream>

#include "storage/storage.hpp"
using namespace  std;
int main() {
  Storage storage;
 // storage.removeUser("D");

  storage.addTag("Kim","Bell");
 // storage.addUser( "Kim", "123" );
 //std::cout << storage.authenticateUser("Ch","kehd");
 //auto users = storage.getUsers();
 // storage.isUserExist("Fgjh");
/*
  for(const auto& user : users) {
    std::cout<< "ID:" << std::get<0>(user)
    << " Name:" << std::get<1>(user)
    << " Password:" << std::get<2>(user)
    << "Tag:" << std::get<3>(user)
    << std::endl;

  }
*/
  return 0;
}
