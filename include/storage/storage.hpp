#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <vector>
#include <tuple>
#include "sqlite3.h"
#include "storage/storage.hpp"
#include "user.hpp"

/**
 * @class Storage
 * @brief A class to manage user data.
 */
class Storage {
 private:
  sqlite3 *db;
 public:
  /**
   * @brief Constructor for the Storage class.
   */
  Storage();

  /**
   * @brief Destructor for the Storage class.
   */
  ~Storage();

  /**
   * @brief Adds a user to the storage.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was added successfully, false otherwise.
   */
  bool addUser(const std::string &username, const std::string &password);

  /**
   * @brief Removes a user from the storage.
   * @param username The username of the user to remove.
   * @return True if the user was removed successfully, false otherwise.
   */
  bool removeUser(std::string username);

  /**
   * @brief Checks if a user exists in the storage.
   * @param username The username to check.
   * @return True if the user exists, false otherwise.
   */
  bool isUserExist(std::string username);

  /**
   * @brief Gets a list of all users.
   * @return A vector of usernames.
   */
  std::vector<std::tuple<int,std::string,std::string,std::string>> getUsers();

  /**
   * @brief Authenticates a user.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the authentication was successful, false otherwise.
   */
  bool authenticateUser(const std::string& username, const std::string &password);

  /**
   * @brief Adds a tag to a user.
   * @param username The username of the user.
   * @param tag The tag to add.
   * @return True if the tag was added successfully, false otherwise.
   */
  bool addTag(std::string username, std::string tag);

  /**
   * @brief Gets a list of tags for a user.
   * @param username The username of the user.
   * @return A vector of tags.
   */
  std::vector<std::string> getTags(std::string username);
};

#endif  // STORAGE_HPP
