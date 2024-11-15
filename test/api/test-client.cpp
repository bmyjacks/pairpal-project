#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>
#include <zmq.hpp>

#include "api/client.hpp"
#include "api/message.hpp"

class MockServer {
 public:
  explicit MockServer(const std::string& address)
      : context_(1), socket_(context_, zmq::socket_type::rep) {
    socket_.bind(address);
    running_ = false;
  }

  void startTrue() {
    running_ = true;
    serverThread_ = std::thread([this]() {
      while (running_) {
        zmq::message_t request;
        zmq::recv_result_t result =
            socket_.recv(request, zmq::recv_flags::dontwait);

        if (result.has_value()) {
          Message message(MessageType::SUCCESS, "SUCCESS");
          const std::string serializedMessage = message.toString();
          zmq::message_t reply(serializedMessage);
          socket_.send(reply, zmq::send_flags::none);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    });
  }

  void startFailure() {
    running_ = true;
    serverThread_ = std::thread([this]() {
      while (running_) {
        zmq::message_t request;
        zmq::recv_result_t result =
            socket_.recv(request, zmq::recv_flags::dontwait);

        if (result.has_value()) {
          Message message(MessageType::FAILURE, "FAILURE");
          const std::string serializedMessage = message.toString();
          zmq::message_t reply(serializedMessage);
          socket_.send(reply, zmq::send_flags::none);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    });
  }

  void stop() {
    running_ = false;
    serverThread_.join();
  }

 private:
  zmq::context_t context_;
  zmq::socket_t socket_;
  std::atomic_bool running_;
  std::thread serverThread_;
};

TEST(ClientTest, TestStart) {
  MockServer server("tcp://localhost:57880");
  server.startTrue();

  Client client("tcp://localhost:57880");
  EXPECT_TRUE(client.start());

  server.stop();
}

TEST(ClientTest, TestAddUserTrue) {
  MockServer server("tcp://localhost:57880");
  server.startTrue();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_TRUE(client.addUser("username", "password"));

  server.stop();
}

TEST(ClientTest, TestAddUserFalse) {
  MockServer server("tcp://localhost:57880");
  server.startFailure();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_FALSE(client.addUser("username", "password"));

  server.stop();
}

TEST(ClientTest, TestRemoveUserTrue) {
  MockServer server("tcp://localhost:57880");
  server.startTrue();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_TRUE(client.removeUser("username"));

  server.stop();
}

TEST(ClientTest, TestRemoveUserFalse) {
  MockServer server("tcp://localhost:57880");
  server.startFailure();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_FALSE(client.removeUser("username"));

  server.stop();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}