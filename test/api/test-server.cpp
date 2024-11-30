#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>
#include <zmq.hpp>

#include "api/message.hpp"
#include "api/server.hpp"

class MockClient {
 public:
  explicit MockClient(const std::string& address)
      : context_(1), socket_(context_, zmq::socket_type::req) {
    socket_.connect(address);
  }

  void sendRequestAndReceiveReply_(zmq::message_t& request,
                                   zmq::message_t& reply) {
    socket_.send(request, zmq::send_flags::none);
    if (const auto result = socket_.recv(reply, zmq::recv_flags::none);
        !result.has_value()) {
      throw std::runtime_error("Error receiving message");
    }
  }

 private:
  zmq::context_t context_;
  zmq::socket_t socket_;
};

class MockServer final : public Server {
 public:
  explicit MockServer(const std::string& listenAddr) : Server(listenAddr) {}

  MOCK_METHOD(bool, addUser_,
              (const std::string& username, const std::string& password),
              (override, noexcept));
  MOCK_METHOD(bool, removeUser_, (const std::string& username),
              (override, noexcept));
  MOCK_METHOD(bool, isExistUser_, (const std::string& username),
              (override, noexcept));
  MOCK_METHOD(std::vector<std::string>, listAllUsers, (), (override, noexcept));
  MOCK_METHOD(bool, authenticateUser_,
              (const std::string& username, const std::string& password),
              (override, noexcept));
  MOCK_METHOD(bool, addUserTag_,
              (const std::string& username, const std::string& tag),
              (override, noexcept));
  MOCK_METHOD(bool, removeUserTag_,
              (const std::string& username, const std::string& tag),
              (override, noexcept));
  MOCK_METHOD(std::vector<std::string>, getUserTags_,
              (const std::string& username), (override, noexcept));
  MOCK_METHOD(bool, sendMessage_,
              (const std::string& from, const std::string& to,
               const std::string& message),
              (override, noexcept));
  MOCK_METHOD(std::vector<std::string>, getSentMessages_,
              (const std::string& username), (override, noexcept));
  MOCK_METHOD(std::vector<std::string>, getReceivedMessages_,
              (const std::string& username), (override, noexcept));
  MOCK_METHOD(std::vector<std::string>, getPair_, (const std::string& username),
              (override, noexcept));
};

TEST(ServerTest, TestConstructor) {
  const Server server("tcp://localhost:57880");
  EXPECT_EQ(server.getListenAddr(), "tcp://localhost:57880");
}

TEST(ServerTest, TestStartAndStop) {
  Server server("tcp://localhost:57880");
  EXPECT_TRUE(server.start());
  EXPECT_TRUE(server.stop());
}

TEST(ServerTest, TestAddUserTrue) {
  MockServer server("tcp://localhost:57880");
  server.start();
  MockClient client("tcp://localhost:57880");

  Message request(MessageType::ADD_USER);
  request.setUsername("user");
  request.setPassword("password");

  EXPECT_CALL(server, addUser_("user", "password"))
      .WillOnce(testing::Return(true));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);

  server.stop();
}

TEST(ServerTest, TestAddUserFalse) {
  MockServer server("tcp://localhost:57880");
  server.start();
  MockClient client("tcp://localhost:57880");

  Message request(MessageType::ADD_USER);
  request.setUsername("user");
  request.setPassword("password");

  EXPECT_CALL(server, addUser_("user", "password"))
      .WillOnce(testing::Return(false));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::FAILURE);

  server.stop();
}

TEST(ServerTest, TestRemoveUserTrue) {
  MockServer server("tcp://localhost:57880");
  server.start();
  MockClient client("tcp://localhost:57880");

  Message request(MessageType::REMOVE_USER);
  request.setUsername("user");

  EXPECT_CALL(server, removeUser_("user")).WillOnce(testing::Return(true));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);

  server.stop();
}

TEST(ServerTest, TestRemoveUserFalse) {
  MockServer server("tcp://localhost:57880");
  server.start();
  MockClient client("tcp://localhost:57880");

  Message request(MessageType::REMOVE_USER);
  request.setUsername("user");

  EXPECT_CALL(server, removeUser_("user")).WillOnce(testing::Return(false));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::FAILURE);

  server.stop();
}

TEST(ServerTest, TestIsExistUserTrue) {
  MockServer server("tcp://localhost:57880");
  server.start();
  MockClient client("tcp://localhost:57880");

  Message request(MessageType::IS_EXIST_USER);
  request.setUsername("user");

  EXPECT_CALL(server, isExistUser_("user")).WillOnce(testing::Return(true));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);

  server.stop();
}

TEST(ServerTest, TestIsExistUserFalse) {
  MockServer server("tcp://localhost:57880");
  server.start();
  MockClient client("tcp://localhost:57880");

  Message request(MessageType::IS_EXIST_USER);
  request.setUsername("user");

  EXPECT_CALL(server, isExistUser_("user")).WillOnce(testing::Return(false));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::FAILURE);

  server.stop();
}

TEST(ServerTest, TestListAllUsersNonEmpty) {
  MockServer server("tcp://localhost:57880");
  server.start();
  MockClient client("tcp://localhost:57880");

  Message request(MessageType::LIST_ALL_USERS);

  EXPECT_CALL(server, listAllUsers())
      .WillOnce(testing::Return(std::vector<std::string>{"user1", "user2"}));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);
  EXPECT_THAT(replyMessage.getVector(), testing::ElementsAre("user1", "user2"));

  server.stop();
}

TEST(ServerTest, TestListAllUsersEmpty) {
  MockServer server("tcp://localhost:57880");
  server.start();
  MockClient client("tcp://localhost:57880");

  Message request(MessageType::LIST_ALL_USERS);

  EXPECT_CALL(server, listAllUsers())
      .WillOnce(testing::Return(std::vector<std::string>{}));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);
  EXPECT_THAT(replyMessage.getVector(), testing::ElementsAre());

  server.stop();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}