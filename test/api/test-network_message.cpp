#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include <network_message.hpp>

TEST(NetworkMessageTest, TestConstructorFromType) {
  const NetworkMessage message(NetworkMessageType::ADD_USER);
  ASSERT_EQ(message.getType(), NetworkMessageType::ADD_USER);
}

TEST(NetworkMessageTest, TestConstructorFromString) {
  const NetworkMessage message(NetworkMessageType::ADD_USER);
  const NetworkMessage message2(message.toString());

  ASSERT_EQ(message.getType(), message2.getType());
}

TEST(NetworkMessageTest, TestSetGetUsername) {
  NetworkMessage message(NetworkMessageType::ADD_USER);
  message.setUsername("test");

  ASSERT_EQ(message.getUsername(), "test");
}

TEST(NetworkMessageTest, TestSetGetPassword) {
  NetworkMessage message(NetworkMessageType::ADD_USER);
  message.setPassword("password");

  ASSERT_EQ(message.getPassword(), "password");
}

TEST(NetworkMessageTest, TestSetGetTag) {
  NetworkMessage message(NetworkMessageType::ADD_USER);
  message.setTag("tag");

  ASSERT_EQ(message.getTag(), "tag");
}

TEST(NetworkMessageTest, TestSetGetFrom) {
  NetworkMessage message(NetworkMessageType::SEND_MESSAGE);
  message.setFrom("user");

  ASSERT_EQ(message.getFrom(), "user");
}

TEST(NetworkMessageTest, TestSetGetTo) {
  NetworkMessage message(NetworkMessageType::SEND_MESSAGE);
  message.setTo("user");

  ASSERT_EQ(message.getTo(), "user");
}

TEST(NetworkMessageTest, TestSetGetMessage) {
  NetworkMessage message(NetworkMessageType::SEND_MESSAGE);
  message.setMessage("message");

  ASSERT_EQ(message.getMessage(), "message");
}

TEST(NetworkMessageTest, TestSetGetVector) {
  NetworkMessage message(NetworkMessageType::LIST_ALL_USERS);
  message.setVector({"user1", "user2"});

  ASSERT_THAT(message.getVector(), testing::ElementsAre("user1", "user2"));
}

auto main(int argc, char** argv) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
