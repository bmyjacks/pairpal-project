#ifndef PAIR_HPP
#define PAIR_HPP

#include <string>
#include <vector>

#include "storage/storage.hpp"

/**
 * @class Pair
 * @brief A class to manage user pairs and their similarities.
 */
class Pair {
 public:
  /**
   * @brief Constructor for the Pair class.
   */
  Pair();

  /**
   * @brief Destructor for the Pair class.
   */
  virtual ~Pair();

  /**
   * @brief Sets the storage object.
   * @param storage The storage object to be set.
   */
  void setStorage(const Storage &storage);

  /**
   * @brief Gets a pair of usernames for the given username.
   * @param username The username for which to get the pair.
   * @return A vector of paired usernames.
   */
  [[nodiscard]] auto getPair(const std::string &username)
      -> std::vector<std::string>;

 private:
  friend class MockPair;  ///< Allows MockPair to access private members.

  Storage storage_;  ///< The storage object.

  /**
   * @brief Gets all usernames.
   * @return A vector of all usernames.
   */
  [[nodiscard]] virtual auto getAllUsernames_() -> std::vector<std::string>;

  /**
   * @brief Gets the tags for a given username.
   * @param username The username for which to get the tags.
   * @return A vector of tags for the given username.
   */
  [[nodiscard]] virtual auto getUserTags_(const std::string &username)
      -> std::vector<std::string>;

  /**
   * @brief Calculates the similarity between two usernames.
   * @param username1 The first username.
   * @param username2 The second username.
   * @return The similarity score between the two usernames.
   */
  [[nodiscard]] virtual auto getSimilarity_(const std::string &username1,
                                            const std::string &username2)
      -> float;
};

#endif  // PAIR_HPP
