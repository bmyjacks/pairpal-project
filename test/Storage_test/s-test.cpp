#include <storage/sqlite3.h>

#include <iostream>
#include <ostream>

#include "storage/storage.hpp"
using namespace  std;
int main() {
  Storage storage;
  string name = "Chloe";
  string password = "11181118";
  storage.addUser( name, password );
  std::cout << storage.authenticateUser("Chloe","11181118");
}
