#include <gtest/gtest.h>
#include "api/message.hpp"


TEST(MessageTest, TestConstructor) {
    nlohmann::json json;
    json["type"] = MessageType::ADD_USER;
    json["content"] = "content";
    Message message(json);
    ASSERT_EQ(message.getType(), MessageType::ADD_USER);
    ASSERT_EQ(message.getContent(), "content");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
