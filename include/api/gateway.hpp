#ifndef GATEWAY_HPP
#define GATEWAY_HPP

#include <string>
#include <vector>

/**
 * @class Gateway
 * @brief A class to manage the API gateway operations.
 */
class Gateway {
 public:
  /**
   * @brief Constructor for the Gateway class.
   */
  Gateway();

  /**
   * @brief Destructor for the Gateway class.
   */
  ~Gateway();

  /**
   * @brief Starts the gateway.
   * @return True if the gateway started successfully, false otherwise.
   */
  bool start();

  /**
   * @brief Stops the gateway.
   * @return True if the gateway stopped successfully, false otherwise.
   */
  bool stop();

  /**
   * @brief Restarts the gateway.
   * @return True if the gateway restarted successfully, false otherwise.
   */
  bool restart();

  /**
   * @brief Adds a user to the system.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was added successfully, false otherwise.
   */
  bool addUser(std::string username, std::string password);

  /**
   * @brief Removes a user from the system.
   * @param username The username of the user to remove.
   * @return True if the user was removed successfully, false otherwise.
   */
  bool removeUser(std::string username);

  /**
   * @brief Checks if a user exists in the system.
   * @param username The username to check.
   * @return True if the user exists, false otherwise.
   */
  bool isExistUser(std::string username);

  /**
   * @brief Authenticates a user.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the authentication was successful, false otherwise.
   */
  bool authenticate(std::string username, std::string password);

  /**
   * @brief Adds a tag to a user.
   * @param username The username of the user.
   * @param tag The tag to add.
   * @return True if the tag was added successfully, false otherwise.
   */
  bool addUserTag(std::string username, std::string tag);

  /**
   * @brief Gets the tags of a user.
   * @param username The username of the user.
   * @return A string containing the tags of the user.
   */
  [[nodiscard]] std::string getUserTags(std::string username);

  /**
   * @brief Gets a list of all users.
   * @return A vector of usernames.
   */
  [[nodiscard]] std::vector<std::string> getAllUsers();

  /**
   * @brief Sends a message from one user to another.
   * @param from The username of the sender.
   * @param to The username of the receiver.
   * @param message The message to send.
   * @return True if the message was sent successfully, false otherwise.
   */
  bool sendMessage(std::string from, std::string to, std::string message);

  /**
   * @brief Gets all sent message of a user.
   *
   */
  std::vector<std::string> getSentMessages(std::string username);

  /**
   * @brief Gets the pair of a user.
   * @param username The username of the user.
   * @return A string containing the pair of the user.
   */
  std::string getPair(std::string username);
};

#endif  // GATEWAY_HPP