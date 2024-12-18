#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <client.hpp>
#include <network_message.hpp>
#include <thread>
#include <zmq.hpp>

class MockServer {
 public:
  explicit MockServer(const std::string& address)
      : context_(1), socket_(context_, zmq::socket_type::rep), running_(false) {
    socket_.bind(address);
  }

  void startReturnTrue() {
    running_ = true;
    serverThread_ = std::thread([this]() {
      while (running_) {
        zmq::message_t request;
        const auto result = socket_.recv(request, zmq::recv_flags::dontwait);

        if (result.has_value()) {
          const NetworkMessage message(NetworkMessageType::SUCCESS);
          socket_.send(*message.toZmqMessage(), zmq::send_flags::none);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
    });
  }

  void startReturnVector() {
    running_ = true;
    serverThread_ = std::thread([this]() {
      while (running_) {
        zmq::message_t request;
        const zmq::recv_result_t result =
            socket_.recv(request, zmq::recv_flags::dontwait);

        if (result.has_value()) {
          NetworkMessage message(NetworkMessageType::SUCCESS);
          message.setVector({"item1", "item2"});

          socket_.send(*message.toZmqMessage(), zmq::send_flags::none);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
    });
  }

  void startReturnFalse() {
    running_ = true;
    serverThread_ = std::thread([this]() {
      while (running_) {
        zmq::message_t request;
        const zmq::recv_result_t result =
            socket_.recv(request, zmq::recv_flags::dontwait);

        if (result.has_value()) {
          const NetworkMessage message(NetworkMessageType::FAILURE);
          socket_.send(*message.toZmqMessage(), zmq::send_flags::none);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
  Client client("tcp://localhost:57880");
  EXPECT_TRUE(client.start());
}

TEST(ClientTest, TestCopyConstructor) {
  const Client client("tcp://localhost:57880");
  Client client2 = client;
  EXPECT_TRUE(client2.start());
}

TEST(ClientTest, TestAddUserTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnTrue();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_TRUE(client.addUser("username", "password"));

  server.stop();
}

TEST(ClientTest, TestAddUserFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_FALSE(client.addUser("username", "password"));

  server.stop();
}

TEST(ClientTest, TestRemoveUserTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnTrue();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_TRUE(client.removeUser("username"));

  server.stop();
}

TEST(ClientTest, TestRemoveUserFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_FALSE(client.removeUser("username"));

  server.stop();
}

TEST(ClientTest, TestIsExistUserTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnTrue();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_TRUE(client.isExistUser("username"));

  server.stop();
}

TEST(ClientTest, TestIsExistUserFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_FALSE(client.isExistUser("username"));

  server.stop();
}

TEST(ClientTest, TestListAllUsersTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnVector();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.listAllUsers();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.at(0), "item1");
  EXPECT_EQ(vec.at(1), "item2");

  server.stop();
}

TEST(ClientTest, TestListAllUsersFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.listAllUsers();
  EXPECT_EQ(vec.size(), 0);

  server.stop();
}

TEST(ClientTest, TestAuthenticateUserTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnTrue();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_TRUE(client.authenticateUser("username", "password"));

  server.stop();
}

TEST(ClientTest, TestAuthenticateUserFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_FALSE(client.authenticateUser("username", "password"));

  server.stop();
}

TEST(ClientTest, TestAddUserTagTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnTrue();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_TRUE(client.addUserTag("username", "tag"));

  server.stop();
}

TEST(ClientTest, TestAddUserTagFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_FALSE(client.addUserTag("username", "tag"));

  server.stop();
}

TEST(ClientTest, TestRemoveUserTagTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnTrue();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_TRUE(client.removeUserTag("username", "tag"));

  server.stop();
}

TEST(ClientTest, TestRemoveUserTagFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_FALSE(client.removeUserTag("username", "tag"));

  server.stop();
}

TEST(ClientTest, TestGetUserTagsTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnVector();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.getUserTags("username");
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.at(0), "item1");
  EXPECT_EQ(vec.at(1), "item2");

  server.stop();
}

TEST(ClientTest, TestGetUserTagsFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.getUserTags("username");
  EXPECT_EQ(vec.size(), 0);

  server.stop();
}

TEST(ClientTest, TestSendMessageTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnTrue();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_TRUE(client.sendMessage("from", "to", "msg"));

  server.stop();
}

TEST(ClientTest, TestSendMessageFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  EXPECT_FALSE(client.sendMessage("from", "to", "msg"));

  server.stop();
}

TEST(ClientTest, TestGetSentMessagesTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnVector();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.getSentMessages("username");
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.at(0), "item1");
  EXPECT_EQ(vec.at(1), "item2");

  server.stop();
}

TEST(ClientTest, TestGetSentMessagesFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.getSentMessages("username");
  EXPECT_EQ(vec.size(), 0);

  server.stop();
}

TEST(ClientTest, TestGetReceiveMessagesTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnVector();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.getReceivedMessages("username");
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.at(0), "item1");
  EXPECT_EQ(vec.at(1), "item2");

  server.stop();
}

TEST(ClientTest, TestGetReceiveMessagesFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.getReceivedMessages("username");
  EXPECT_EQ(vec.size(), 0);

  server.stop();
}

TEST(ClientTest, TestGetPairTrue) {
  MockServer server("tcp://localhost:57880");
  server.startReturnVector();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.getPair("username");
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.at(0), "item1");
  EXPECT_EQ(vec.at(1), "item2");

  server.stop();
}

TEST(ClientTest, TestGetPairFalse) {
  MockServer server("tcp://localhost:57880");
  server.startReturnFalse();

  Client client("tcp://localhost:57880");
  client.start();

  const std::vector<std::string> vec = client.getPair("username");
  EXPECT_EQ(vec.size(), 0);

  server.stop();
}

auto main(int argc, char** argv) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}