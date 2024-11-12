#include <gtest/gtest.h>
#include "api/message.hpp"

TEST(MessageTest, TestConstructorFromTypeAndContentSimple) {
    Message message(MessageType::ADD_USER, "content");
    ASSERT_EQ(message.getType(), MessageType::ADD_USER);
    ASSERT_EQ(message.getContent(), "content");
}

TEST(MessageTest, TestConstructorFromTypeAndContentComplex) {
    nlohmann::json content;
    content["key"] = "value";
    Message message(MessageType::ADD_USER, content);
    ASSERT_EQ(message.getType(), MessageType::ADD_USER);
    ASSERT_EQ(message.getContent(), content);
}

TEST(MessageTest, TestConstructorFromJsonSimple) {
    nlohmann::json json;
    json["type"] = MessageType::ADD_USER;
    json["content"] = "content";
    Message message(json);
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
    Message message(MessageType::ADD_USER, "content");
    nlohmann::json json = message.toJson();
    ASSERT_EQ(json["type"], MessageType::ADD_USER);
    ASSERT_EQ(json["content"], "content");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
