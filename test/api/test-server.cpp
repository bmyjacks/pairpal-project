#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
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

const std::string kTestAddress = "tcp://localhost:57880";

TEST(ServerTest, TestConstructor) {
  const Server server(kTestAddress);
  EXPECT_EQ(server.getListenAddr(), kTestAddress);
}

TEST(ServerTest, TestStartAndStop) {
  Server server(kTestAddress);
  EXPECT_TRUE(server.start());
  EXPECT_TRUE(server.stop());
}

TEST(ServerTest, TestStartTwiceThenStop) {
  Server server(kTestAddress);
  EXPECT_TRUE(server.start());
  EXPECT_FALSE(server.start());
  EXPECT_TRUE(server.stop());
}

TEST(ServerTest, TestStopWithoutStart) {
  Server server(kTestAddress);
  EXPECT_FALSE(server.stop());
}

TEST(ServerTest, TestAddUserTrue) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

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
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

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
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

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
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

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
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

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
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

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
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

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
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

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

TEST(ServerTest, TestAuthenticateUserTrue) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::AUTHENTICATE_USER);
  request.setUsername("user");
  request.setPassword("password");

  EXPECT_CALL(server, authenticateUser_("user", "password"))
      .WillOnce(testing::Return(true));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);

  server.stop();
}

TEST(ServerTest, TestAuthenticateUserFalse) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::AUTHENTICATE_USER);
  request.setUsername("user");
  request.setPassword("password");

  EXPECT_CALL(server, authenticateUser_("user", "password"))
      .WillOnce(testing::Return(false));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::FAILURE);

  server.stop();
}

TEST(ServerTest, TestAddUserTagTrue) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::ADD_USER_TAG);
  request.setUsername("user");
  request.setTag("tag");

  EXPECT_CALL(server, addUserTag_("user", "tag"))
      .WillOnce(testing::Return(true));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);

  server.stop();
}

TEST(ServerTest, TestAddUserTagFalse) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::ADD_USER_TAG);
  request.setUsername("user");
  request.setTag("tag");

  EXPECT_CALL(server, addUserTag_("user", "tag"))
      .WillOnce(testing::Return(false));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::FAILURE);

  server.stop();
}

TEST(ServerTest, TestRemoveUserTagTrue) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::REMOVE_USER_TAG);
  request.setUsername("user");
  request.setTag("tag");

  EXPECT_CALL(server, removeUserTag_("user", "tag"))
      .WillOnce(testing::Return(true));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);

  server.stop();
}

TEST(ServerTest, TestRemoveUserTagFalse) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::REMOVE_USER_TAG);
  request.setUsername("user");
  request.setTag("tag");

  EXPECT_CALL(server, removeUserTag_("user", "tag"))
      .WillOnce(testing::Return(false));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::FAILURE);

  server.stop();
}

TEST(ServerTest, TestGetUserTagsNonEmpty) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::GET_USER_TAGS);
  request.setUsername("user");

  EXPECT_CALL(server, getUserTags_("user"))
      .WillOnce(testing::Return(std::vector<std::string>{"tag1", "tag2"}));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);
  EXPECT_THAT(replyMessage.getVector(), testing::ElementsAre("tag1", "tag2"));

  server.stop();
}

TEST(ServerTest, TestGetUserTagsEmpty) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::GET_USER_TAGS);
  request.setUsername("user");

  EXPECT_CALL(server, getUserTags_("user"))
      .WillOnce(testing::Return(std::vector<std::string>{}));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);
  EXPECT_THAT(replyMessage.getVector(), testing::ElementsAre());

  server.stop();
}

TEST(ServerTest, TestSendMessageTrue) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::SEND_MESSAGE);
  request.setFrom("from");
  request.setTo("to");
  request.setMessage("message");

  EXPECT_CALL(server, sendMessage_("from", "to", "message"))
      .WillOnce(testing::Return(true));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);

  server.stop();
}

TEST(ServerTest, TestSendMessageFalse) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::SEND_MESSAGE);
  request.setFrom("from");
  request.setTo("to");
  request.setMessage("message");

  EXPECT_CALL(server, sendMessage_("from", "to", "message"))
      .WillOnce(testing::Return(false));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::FAILURE);

  server.stop();
}

TEST(ServerTest, TestGetSentMessagesNonEmpty) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::GET_SENT_MESSAGES);
  request.setUsername("user");

  EXPECT_CALL(server, getSentMessages_("user"))
      .WillOnce(
          testing::Return(std::vector<std::string>{"message1", "message2"}));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);
  EXPECT_THAT(replyMessage.getVector(),
              testing::ElementsAre("message1", "message2"));

  server.stop();
}

TEST(ServerTest, TestGetSentMessagesEmpty) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::GET_SENT_MESSAGES);
  request.setUsername("user");

  EXPECT_CALL(server, getSentMessages_("user"))
      .WillOnce(testing::Return(std::vector<std::string>{}));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);
  EXPECT_THAT(replyMessage.getVector(), testing::ElementsAre());

  server.stop();
}

TEST(ServerTest, TestGetReceivedMessagesNonEmpty) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::GET_RECEIVED_MESSAGES);
  request.setUsername("user");

  EXPECT_CALL(server, getReceivedMessages_("user"))
      .WillOnce(
          testing::Return(std::vector<std::string>{"message1", "message2"}));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);
  EXPECT_THAT(replyMessage.getVector(),
              testing::ElementsAre("message1", "message2"));

  server.stop();
}

TEST(ServerTest, TestGetReceivedMessagesEmpty) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::GET_RECEIVED_MESSAGES);
  request.setUsername("user");

  EXPECT_CALL(server, getReceivedMessages_("user"))
      .WillOnce(testing::Return(std::vector<std::string>{}));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);
  EXPECT_THAT(replyMessage.getVector(), testing::ElementsAre());

  server.stop();
}

TEST(ServerTest, TestGetPairNonEmpty) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::GET_PAIR);
  request.setUsername("user");

  EXPECT_CALL(server, getPair_("user"))
      .WillOnce(testing::Return(std::vector<std::string>{"user1", "user2"}));

  zmq::message_t reply;
  client.sendRequestAndReceiveReply_(*request.toZmqMessage(), reply);
  const Message replyMessage(reply.to_string());
  EXPECT_EQ(replyMessage.getType(), MessageType::SUCCESS);
  EXPECT_THAT(replyMessage.getVector(), testing::ElementsAre("user1", "user2"));

  server.stop();
}

TEST(ServerTest, TestGetPairEmpty) {
  MockServer server(kTestAddress);
  server.start();
  MockClient client(kTestAddress);

  Message request(MessageType::GET_PAIR);
  request.setUsername("user");

  EXPECT_CALL(server, getPair_("user"))
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