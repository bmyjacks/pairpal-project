#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <string>
#include <vector>
#include "User.hpp"

/**
 * @class Storage
 * @brief A class to manage user data.
 */
class Storage {
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
    bool addUser(std::string username, std::string password);

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
    bool userExists(std::string username);

    /**
     * @brief Gets a list of all users.
     * @return A vector of usernames.
     */
    std::vector<User> getUsers();

    /**
     * @brief Authenticates a user.
     * @param username The username of the user.
     * @param password The password of the user.
     * @return True if the authentication was successful, false otherwise.
     */
    bool authenticateUser(std::string username, std::string password);

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

#endif // STORAGE_HPP
