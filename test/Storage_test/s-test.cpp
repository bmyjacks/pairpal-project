#include <storage/sqlite3.h>

#include <iostream>
#include <ostream>

#include "storage/storage.hpp"
using namespace  std;
int main() {
  Storage storage;
  string name = "C";
  string password = "118";
  storage.removeUser("C");
 // storage.addUser( name, password );
//  std::cout << storage.authenticateUser("C","11181118");
 // auto users = storage.getUsers();
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
