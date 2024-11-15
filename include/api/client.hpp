#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <zmq.hpp>

/**
 * @class Client
 * @brief A class to manage the API gateway operations.
 */
class Client {
 public:
  /**
   * @brief Constructor for the Client class.
   * @param serverAddr The address of the server to connect to.
   */
  explicit Client(std::string serverAddr);

  /**
   * @brief Destructor for the Client class.
   */
  ~Client();

  /**
   * @brief Starts the client.
   * @return True if the client started successfully, false otherwise.
   */
  bool start();

  /**
   * @brief Stops the client.
   * @return True if the client stopped successfully, false otherwise.
   */
  bool stop();

  /**
   * @brief Restarts the client.
   * @return True if the client restarted successfully, false otherwise.
   */
  bool restart();

  /**
   * @brief Adds a user to the system.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was added successfully, false otherwise.
   */
  bool addUser(const std::string& username, const std::string& password);

  /**
   * @brief Removes a user from the system.
   * @param username The username of the user to remove.
   * @return True if the user was removed successfully, false otherwise.
   */
  bool removeUser(const std::string& username);

  /**
   * @brief Checks if a user exists in the system.
   * @param username The username to check.
   * @return True if the user exists, false otherwise.
   */
  bool isExistUser(const std::string& username);

  /**
   * @brief Authenticates a user.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the authentication was successful, false otherwise.
   */
  bool authenticate(const std::string& username, const std::string& password);

  /**
   * @brief Adds a tag to a user.
   * @param username The username of the user.
   * @param tag The tag to add.
   * @return True if the tag was added successfully, false otherwise.
   */
  bool addUserTag(const std::string& username, const std::string& tag);

  /**
   * @brief Gets the tags of a user.
   * @param username The username of the user.
   * @return A string containing the tags of the user.
   */
  [[nodiscard]] std::string getUserTags(const std::string& username);

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
  bool sendMessage(const std::string& from, const std::string& to,
                   const std::string& message);

  /**
   * @brief Gets all sent messages of a user.
   * @param from The username of the sender.
   * @param to The username of the receiver.
   * @return A vector of messages.
   */
  [[nodiscard]] std::vector<std::string> getSentMessages(
      const std::string& from, const std::string& to);

  /**
   * @brief Gets the pair of a user.
   * @param username The username of the user.
   * @return A vector containing the pair of the user.
   */
  [[nodiscard]] std::vector<std::string> getPair(std::string& username);

 private:
  std::string serverAddr_;  ///< The address of the server.
  zmq::context_t context_;  ///< The ZeroMQ context.
  zmq::socket_t socket_;    ///< The ZeroMQ socket.

  /**
   * @brief Sends a request and receives a reply.
   * @param request The request message to send.
   * @param reply The reply message to receive.
   * @return True if the request was sent and the reply was received
   * successfully, false otherwise.
   */
  bool sendRequestAndReceiveReply_(zmq::message_t& request,
                                   zmq::message_t& reply);
};

#endif  // CLIENT_HPP