#include <iostream>

#include "api/gateway.hpp"

Gateway::Gateway() {
    std::cout << "Gateway created." << std::endl;
}

Gateway::~Gateway() {
    std::cout << "Gateway destroyed." << std::endl;
}
