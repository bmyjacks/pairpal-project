#include <gtest/gtest.h>

#include <chat.hpp>

TEST(ChatTest, TestChat) {
  Chat chat;

  EXPECT_TRUE(chat.sendMessage("user1", "user2", "message1"));
  EXPECT_TRUE(chat.sendMessage("user1", "user3", "message2"));
  EXPECT_TRUE(chat.sendMessage("user2", "user1", "message3"));
  EXPECT_TRUE(chat.sendMessage("user2", "user3", "message4"));
  EXPECT_TRUE(chat.sendMessage("user3", "user1", "message5"));
  EXPECT_TRUE(chat.sendMessage("user3", "user2", "message6"));

  EXPECT_EQ(chat.getSentMessages("user1").size(), 2);
  EXPECT_EQ(chat.getReceivedMessages("user1").size(), 2);
  EXPECT_EQ(chat.getSentMessages("user2").size(), 2);
  EXPECT_EQ(chat.getReceivedMessages("user2").size(), 2);
  EXPECT_EQ(chat.getSentMessages("user3").size(), 2);
  EXPECT_EQ(chat.getReceivedMessages("user3").size(), 2);

  EXPECT_EQ(chat.getSentMessages("user1")[0].toString(),
            "From: user1\nTo: user2\nMessage: message1");
  EXPECT_EQ(chat.getSentMessages("user1")[1].toString(),
            "From: user1\nTo: user3\nMessage: message2");
  EXPECT_EQ(chat.getReceivedMessages("user1")[0].toString(),
            "From: user2\nTo: user1\nMessage: message3");
  EXPECT_EQ(chat.getReceivedMessages("user1")[1].toString(),
            "From: user3\nTo: user1\nMessage: message5");

  EXPECT_EQ(chat.getSentMessages("user2")[0].toString(),
            "From: user2\nTo: user1\nMessage: message3");
  EXPECT_EQ(chat.getSentMessages("user2")[1].toString(),
            "From: user2\nTo: user3\nMessage: message4");
  EXPECT_EQ(chat.getReceivedMessages("user2")[0].toString(),
            "From: user1\nTo: user2\nMessage: message1");
  EXPECT_EQ(chat.getReceivedMessages("user2")[1].toString(),
            "From: user3\nTo: user2\nMessage: message6");

  EXPECT_EQ(chat.getSentMessages("user3")[0].toString(),
            "From: user3\nTo: user1\nMessage: message5");
  EXPECT_EQ(chat.getSentMessages("user3")[1].toString(),
            "From: user3\nTo: user2\nMessage: message6");
  EXPECT_EQ(chat.getReceivedMessages("user3")[0].toString(),
            "From: user1\nTo: user3\nMessage: message2");
  EXPECT_EQ(chat.getReceivedMessages("user3")[1].toString(),
            "From: user2\nTo: user3\nMessage: message4");
}

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}