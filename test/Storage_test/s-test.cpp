#include <storage/sqlite3.h>

#include <iostream>
#include <ostream>

#include "storage/storage.hpp"
using namespace  std;
int main() {
  Storage storage;
  storage.addUser("Adam","12345");
  storage.addUser("Jim","12345");
  storage.addUser("Timmy","12345");
  storage.addTag("Jim","football");
  storage.addTag("Jim","baseball");
  storage.addTag("Adam","baseball");


 auto users = storage.getUsers();
  for(const auto& user : users) {
    std::cout<< "ID:" << std::get<0>(user)
    << " Name:" << std::get<1>(user)
    << " Password:" << std::get<2>(user)
    << "Tag:" ;
    for(std::string tag : std::get<3>(user)) {
      std::cout << tag << "  ";
    }
    std::cout << std::endl;
  }
  return 0;
}
