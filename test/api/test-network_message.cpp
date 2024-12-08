#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <network_message.hpp>

TEST(MessageTest, TestConstructorFromType) {
  const NetworkMessage message(NetworkMessageType::ADD_USER);
  ASSERT_EQ(message.getType(), NetworkMessageType::ADD_USER);
}

TEST(MessageTest, TestConstructorFromString) {
  const NetworkMessage message(NetworkMessageType::ADD_USER);
  const NetworkMessage message2(message.toString());

  EXPECT_EQ(message.getType(), message2.getType());
}

TEST(MessageTest, TestSetGetUsername) {
  NetworkMessage message(NetworkMessageType::ADD_USER);
  message.setUsername("test");

  EXPECT_EQ(message.getUsername(), "test");
}

TEST(MessageTest, TestSetGetPassword) {
  NetworkMessage message(NetworkMessageType::ADD_USER);
  message.setPassword("password");

  EXPECT_EQ(message.getPassword(), "password");
}

TEST(MessageTest, TestSetGetTag) {
  NetworkMessage message(NetworkMessageType::ADD_USER);
  message.setTag("tag");

  EXPECT_EQ(message.getTag(), "tag");
}

TEST(MessageTest, TestSetGetFrom) {
  NetworkMessage message(NetworkMessageType::SEND_MESSAGE);
  message.setFrom("user");

  EXPECT_EQ(message.getFrom(), "user");
}

TEST(MessageTest, TestSetGetTo) {
  NetworkMessage message(NetworkMessageType::SEND_MESSAGE);
  message.setTo("user");

  EXPECT_EQ(message.getTo(), "user");
}

TEST(MessageTest, TestSetGetMessage) {
  NetworkMessage message(NetworkMessageType::SEND_MESSAGE);
  message.setMessage("message");

  EXPECT_EQ(message.getMessage(), "message");
}

TEST(MessageTest, TestSetGetVector) {
  NetworkMessage message(NetworkMessageType::LIST_ALL_USERS);
  message.setVector({"user1", "user2"});

  EXPECT_THAT(message.getVector(), testing::ElementsAre("user1", "user2"));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
