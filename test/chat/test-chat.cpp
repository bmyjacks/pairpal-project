#include <gtest/gtest.h>

#include <chat.hpp>

TEST(ChatTest, TestChat) {
  Chat chat;

  EXPECT_TRUE(chat.sendMessage("user1", "user2", "message1"));
  EXPECT_TRUE(chat.sendMessage("user1", "user2", "message2"));
  EXPECT_TRUE(chat.sendMessage("user2", "user1", "message3"));
  EXPECT_TRUE(chat.sendMessage("user2", "user1", "message4"));

  EXPECT_EQ(chat.getSentMessages("user1").size(), 2);
  EXPECT_EQ(chat.getReceivedMessages("user1").size(), 2);
  EXPECT_EQ(chat.getSentMessages("user2").size(), 2);
  EXPECT_EQ(chat.getReceivedMessages("user2").size(), 2);
}

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}