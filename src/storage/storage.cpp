#include "storage/storage.hpp"

#include <iostream>

#include <storage/sqlite3.h>
Storage::Storage() { std::cout << "Storage constructor" << std::endl; }

Storage::~Storage() { std::cout << "Storage destructor" << std::endl; }