#include "api/client.hpp"

#include <iostream>
#include <utility>
#include <zmq.hpp>

Client::Client(std::string serverAddr)
    : serverAddr_(std::move(serverAddr)),
      context_(1),
      socket_(context_, zmq::socket_type::req) {}

Client::~Client() = default;

bool Client::start() {
  socket_.connect(serverAddr_);

  const std::string data{"Hello6"};

  for (auto request_num = 0; request_num < 10; ++request_num) {
    // send the request message
    std::cout << "Sending Hello " << request_num << "..." << std::endl;
    socket_.send(zmq::buffer(data), zmq::send_flags::none);

    // wait for reply from server
    zmq::message_t reply{};
    socket_.recv(reply, zmq::recv_flags::none);

    std::cout << "Received " << reply.to_string();
    std::cout << " (" << request_num << ")";
    std::cout << std::endl;
  }

  return true;
}

bool Client::stop() {
  try {
    socket_.disconnect(serverAddr_);
  } catch (const zmq::error_t& e) {
    std::cerr << "Error stopping client: " << e.what() << std::endl;
    return false;
  }
  return true;
}

bool Client::restart() {
  if (!stop()) {
    return false;
  }

  return start();
}
