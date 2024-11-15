#include <gtest/gtest.h>

#include "api/message.hpp"

TEST(MessageTest, TestConstructorFromTypeAndContentSimple) {
  const Message message(MessageType::ADD_USER, "content");
  ASSERT_EQ(message.getType(), MessageType::ADD_USER);
  ASSERT_EQ(message.getContent(), "content");
}

TEST(MessageTest, TestConstructorFromTypeAndContentComplex) {
  nlohmann::json content;
  content["key"] = "value";
  const Message message(MessageType::ADD_USER, content);
  ASSERT_EQ(message.getType(), MessageType::ADD_USER);
  ASSERT_EQ(message.getContent(), content);
}

TEST(MessageTest, TestConstructorFromJsonSimple) {
  nlohmann::json json;
  json["type"] = MessageType::ADD_USER;
  json["content"] = "content";
  const Message message(json);
  ASSERT_EQ(message.getType(), MessageType::ADD_USER);
  ASSERT_EQ(message.getContent(), "content");
}

TEST(MessageTest, TestConstructorFromJsonComplex) {
  nlohmann::json content;
  content["key"] = "value";
  nlohmann::json json;
  json["type"] = MessageType::ADD_USER;
  json["content"] = content;
  Message message(json);
  ASSERT_EQ(message.getType(), MessageType::ADD_USER);
  ASSERT_EQ(message.getContent(), content);
}

TEST(MessageTest, TestToJsonSimple) {
  const Message message(MessageType::ADD_USER, "content");
  nlohmann::json json = message.toJson();
  ASSERT_EQ(json["type"], MessageType::ADD_USER);
  ASSERT_EQ(json["content"], "content");
}

TEST(MessageTest, TestToJsonComplex) {
  nlohmann::json content;
  content["key"] = "value";
  const Message message(MessageType::ADD_USER, content);
  nlohmann::json json = message.toJson();
  ASSERT_EQ(json["type"], MessageType::ADD_USER);
  ASSERT_EQ(json["content"], content);
}

TEST(MessageTest, TestStringSimple) {
  constexpr auto type = MessageType::ADD_USER;
  const std::string content = "content";

  const Message original(type, content);

  const Message message(original.toString());

  ASSERT_EQ(message.getType(), type);
  ASSERT_EQ(message.getContent(), content);
}

TEST(MessageTest, TestStringComplex) {
  constexpr auto type = MessageType::ADD_USER;
  nlohmann::json content;
  content["key"] = "value";
  const Message original(type, content);

  const Message message(original.toString());

  ASSERT_EQ(message.getType(), type);
  ASSERT_EQ(message.getContent(), content);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
