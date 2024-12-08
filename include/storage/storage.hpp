#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <vector>
#include <tuple>

#include "sqlite3.h"
#include "storage.hpp"

/**
 * @class Storage
 * @brief A class to manage user data.
 */
class Storage {
 private:
  sqlite3 *db;
  std::string divide = "^^";//用来在tag里进行区隔的
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
   * @return A vector, whose element is the tuple for each user, including their name password and the tag is return as a vector whose element is string
   */
std::vector<std::tuple<int,std::string,std::string,std::vector<std::string>>> getUsers();

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
  /**
 * @brief delete tag for certain user
 * @param username The name of user
 * @param tag the tag wanna to remove
 * @return the bool value if successfully remove the tag
 */
  bool removeTag(std::string username, std::string tag);

};

#endif  // STORAGE_HPP