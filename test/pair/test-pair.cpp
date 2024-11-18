#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "pair/pair.hpp"

class MockPair final : public Pair {
 public:
  MOCK_METHOD(std::vector<std::string>, getAllUsernames_, (), (override));
  MOCK_METHOD(std::vector<std::string>, getUserTags_,
              (const std::string &username), (override));

  std::vector<std::string> originalGetPair(const std::string &username) {
    return Pair::getPair(username);
  }

  float originalGetSimilarity(const std::string &username1,
                              const std::string &username2) {
    return Pair::getSimilarity_(username1, username2);
  }
};

TEST(PairTest, TestGetPairEmpty) {
  MockPair pair;

  EXPECT_CALL(pair, getAllUsernames_())
      .WillOnce(testing::Return(std::vector<std::string>{}));

  const auto result = pair.originalGetPair("username");

  EXPECT_TRUE(result.empty());
}

TEST(PairTest, TestGetPairNonEmpty) {
  MockPair pair;

  const std::vector<std::string> usernames{"user1", "user2", "user3", "user4"};
  const std::vector<std::string> user1Tags{"tag1", "tag2", "tag3", "tag4"};
  const std::vector<std::string> user2Tags{"tag1", "tag2", "tag3", "tag5"};
  const std::vector<std::string> user3Tags{"tag1", "tag2", "tag5", "tag6"};
  const std::vector<std::string> user4Tags{"tag5", "tag6", "tag7", "tag8"};

  EXPECT_CALL(pair, getAllUsernames_()).WillOnce(testing::Return(usernames));
  EXPECT_CALL(pair, getUserTags_("user1"))
      .WillRepeatedly(testing::Return(user1Tags));
  EXPECT_CALL(pair, getUserTags_("user2")).WillOnce(testing::Return(user2Tags));
  EXPECT_CALL(pair, getUserTags_("user3")).WillOnce(testing::Return(user3Tags));
  EXPECT_CALL(pair, getUserTags_("user4")).WillOnce(testing::Return(user4Tags));

  const auto result = pair.originalGetPair("user1");
  const std::vector<std::string> expected{"user2", "user3"};
  EXPECT_EQ(result, expected);
}

TEST(PairTest, TestGetSimilarityWithEmptyTags) {
  MockPair pair;

  const std::vector<std::string> user1Tags{};
  const std::vector<std::string> user2Tags{};

  EXPECT_CALL(pair, getUserTags_("user1")).WillOnce(testing::Return(user1Tags));
  EXPECT_CALL(pair, getUserTags_("user2")).WillOnce(testing::Return(user2Tags));

  const auto similarity = pair.originalGetSimilarity("user1", "user2");

  EXPECT_FLOAT_EQ(similarity, 0);
}

TEST(PairTest, TestGetSimilarityZero) {
  MockPair pair;

  const std::vector<std::string> user1Tags{"tag1", "tag2"};
  const std::vector<std::string> user2Tags{"tag3", "tag4"};

  EXPECT_CALL(pair, getUserTags_("user1")).WillOnce(testing::Return(user1Tags));
  EXPECT_CALL(pair, getUserTags_("user2")).WillOnce(testing::Return(user2Tags));

  const auto similarity = pair.originalGetSimilarity("user1", "user2");

  EXPECT_FLOAT_EQ(similarity, 0);
}

TEST(PairTest, TestGetSimilarityNonZero) {
  MockPair pair;

  const std::vector<std::string> user1Tags{"tag1", "tag2", "tag3"};
  const std::vector<std::string> user2Tags{"tag1", "tag4"};

  EXPECT_CALL(pair, getUserTags_("user1")).WillOnce(testing::Return(user1Tags));
  EXPECT_CALL(pair, getUserTags_("user2")).WillOnce(testing::Return(user2Tags));

  const auto similarity = pair.originalGetSimilarity("user1", "user2");

  EXPECT_FLOAT_EQ(similarity, 0.25);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}