#include <storage/sqlite3.h>

#include <iostream>
#include <ostream>

#include "storage/storage.hpp"
using namespace  std;
int main() {
  Storage storage;
  storage.removeTag("Jim","baseball");
/*
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

  std::vector<std::string> tag = storage.getTags("Jim");
  for(const std::string& t : tag) {
    std::cout << t << " ";
  }
  std::cout << std::endl;
*/
  return 0;
}
