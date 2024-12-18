#include "pair.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_set>

Pair::Pair() = default;
Pair::~Pair() = default;

void Pair::setStorage(const Storage &storage) { storage_ = storage; }

auto Pair::getPair(const std::string &username) -> std::vector<std::string> {
  const auto allUsernames = getAllUsernames_();

  std::cerr << "size: " << allUsernames.size() << std::endl;

  std::vector<std::pair<std::string, float>> similarities;

  for (const auto &i : allUsernames) {
    if (i == username) {
      continue;
    }

    similarities.emplace_back(i, getSimilarity_(username, i));
  }

  std::ranges::sort(similarities, [](const auto &a, const auto &b) {
    return a.second > b.second;
  });

  std::vector<std::string> result;

  for (auto &[username, similarity] : similarities) {
    if (similarity > 0.0) {
      result.push_back(username);
    }
  }

  return result;
}

auto Pair::getAllUsernames_() -> std::vector<std::string> {
  const auto users = storage_.getUsers();

  std::vector<std::string> result;
  for (const auto &user : users) {
    result.push_back(std::get<1>(user));
  }

  return result;
}

auto Pair::getUserTags_(const std::string &username)
    -> std::vector<std::string> {
  return storage_.getTags(username);
}

auto Pair::getSimilarity_(const std::string &username1,
                          const std::string &username2) -> float {
  const auto user1Tags = getUserTags_(username1);
  const auto user2Tags = getUserTags_(username2);

  std::unordered_set<std::string> intersectionSet;
  for (const auto &tag : user1Tags) {
    if (std::ranges::find(user2Tags, tag) != user2Tags.end()) {
      intersectionSet.insert(tag);
    }
  }

  std::unordered_set<std::string> unionSet;
  for (const auto &tag : user1Tags) {
    unionSet.insert(tag);
  }
  for (const auto &tag : user2Tags) {
    unionSet.insert(tag);
  }

  if (unionSet.empty()) {
    return 0;
  }

  return static_cast<float>(intersectionSet.size()) /
         static_cast<float>(unionSet.size());
}