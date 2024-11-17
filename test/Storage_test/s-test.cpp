#include <storage/sqlite3.h>

#include <iostream>
#include <ostream>

#include "storage/storage.hpp"
using namespace  std;
int main() {
  Storage storage;
  string name = "Tom";
  string password = "111111";
  storage.addUser( name, password );
  std::cout << storage.authenticateUser("Sam","111111");
}
