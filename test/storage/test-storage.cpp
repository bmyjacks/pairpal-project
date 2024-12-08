#include <gtest/gtest.h>

#include <chrono>
#include <storage.hpp>

TEST(StorageTest, TestStorage) {
  Storage::reset();

  Storage storage;

  ASSERT_EQ(storage.getUsers().size(), 0);
  ASSERT_FALSE(storage.isUserExist("user1"));
  ASSERT_FALSE(storage.authenticateUser("user1", "password1"));
  ASSERT_FALSE(storage.removeUser("user1"));

  ASSERT_TRUE(storage.addUser("user1", "password1"));
  ASSERT_EQ(storage.getUsers().size(), 1);
  ASSERT_TRUE(storage.isUserExist("user1"));
  ASSERT_TRUE(storage.authenticateUser("user1", "password1"));
  ASSERT_TRUE(storage.removeUser("user1"));
  ASSERT_FALSE(storage.isUserExist("user1"));
  ASSERT_EQ(storage.getUsers().size(), 0);

  ASSERT_TRUE(storage.addUser("user1", "password1"));
  ASSERT_TRUE(storage.addUser("user2", "password2"));
  ASSERT_TRUE(storage.addUser("user3", "password3"));
  ASSERT_EQ(storage.getUsers().size(), 3);
  ASSERT_EQ(std::get<1>(storage.getUsers()[0]), "user1");
  ASSERT_EQ(std::get<1>(storage.getUsers()[1]), "user2");
  ASSERT_EQ(std::get<1>(storage.getUsers()[2]), "user3");

  ASSERT_TRUE(storage.addTag("user1", "tag1"));
  ASSERT_TRUE(storage.addTag("user1", "tag2"));
  ASSERT_TRUE(storage.addTag("user1", "tag3"));
  ASSERT_EQ(storage.getTags("user1").size(), 3);
  ASSERT_EQ(storage.getTags("user1")[0], "tag1");
  ASSERT_EQ(storage.getTags("user1")[1], "tag2");
  ASSERT_EQ(storage.getTags("user1")[2], "tag3");
}

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}