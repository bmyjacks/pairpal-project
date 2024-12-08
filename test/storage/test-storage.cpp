#include <gtest/gtest.h>

#include <chrono>
#include <storage.hpp>

TEST(StorageTest, TestConstructor) { Storage const storage; }

TEST(StorageTest, TestReset) {
  Storage storage;
  storage.reset();

  ASSERT_TRUE(storage.addUser("user", "password"));
  storage.reset();
  ASSERT_FALSE(storage.isUserExist("user"));
}

TEST(StorageTest, TestAddUser) {
  Storage storage;
  storage.reset();

  ASSERT_TRUE(storage.addUser("user", "password"));
}

TEST(StorageTest, TestRemoveUser) {
  Storage storage;
  storage.reset();

  ASSERT_FALSE(storage.removeUser("user"));
  ASSERT_TRUE(storage.addUser("user", "password"));
  ASSERT_TRUE(storage.removeUser("user"));
}

TEST(StorageTest, TestIsUserExist) {
  Storage storage;
  storage.reset();

  ASSERT_FALSE(storage.isUserExist("user"));
  ASSERT_TRUE(storage.addUser("user", "password"));
  ASSERT_TRUE(storage.isUserExist("user"));
}

TEST(StorageTest, TestGetUsers) {
  Storage storage;
  storage.reset();

  auto users = storage.getUsers();
  ASSERT_EQ(users.size(), 0);

  storage.addUser("user", "password");
  users = storage.getUsers();
  ASSERT_EQ(users.size(), 1);
  ASSERT_EQ(std::get<1>(users[0]), "user");
  ASSERT_EQ(std::get<2>(users[0]), "password");
}

TEST(StorageTest, TestAuthenticateUser) {
  Storage storage;
  storage.reset();

  ASSERT_FALSE(storage.authenticateUser("user", "password"));
  ASSERT_TRUE(storage.addUser("user", "password"));
  ASSERT_TRUE(storage.authenticateUser("user", "password"));
}

TEST(StorageTest, TestAddTag) {
  Storage storage;
  storage.reset();

  ASSERT_FALSE(storage.addTag("user", "tag"));
  ASSERT_TRUE(storage.addUser("user", "password"));
  ASSERT_TRUE(storage.addTag("user", "tag"));
}

TEST(StorageTest, TestGetTags) {
  Storage storage;
  storage.reset();

  ASSERT_EQ(storage.getTags("user").size(), 0);
}

TEST(StorageTest, TestRemoveTag) {
  Storage storage;
  storage.reset();

  ASSERT_TRUE(storage.addUser("user", "password"));
  ASSERT_TRUE(storage.addTag("user", "tag"));
  ASSERT_TRUE(storage.removeTag("user", "tag"));
  ASSERT_EQ(storage.getTags("user").size(), 0);
}

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}