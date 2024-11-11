#include <iostream>

#include "api/client.hpp"

Client::Client() {
    std::cout << "Client created." << std::endl;
}

Client::~Client() {
    std::cout << "Client destroyed." << std::endl;
}
