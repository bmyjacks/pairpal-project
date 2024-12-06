#include <gtest/gtest.h>

#include "storage/storage.hpp"

TEST(StorageTest, TestConstructor) { Storage const storage; }

TEST(StorageTest, TestAddUser) {
  Storage storage;
  EXPECT_TRUE(storage.addUser("test", "test"));
}

TEST(StorageTest, TestRemoveUser) {
  Storage storage;

  EXPECT_FALSE(storage.removeUser("test"));

  storage.addUser("test", "test");
  EXPECT_TRUE(storage.removeUser("test"));
}

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}