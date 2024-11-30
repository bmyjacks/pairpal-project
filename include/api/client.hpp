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
  bool start() noexcept;

  /**
   * @brief Stops the client.
   * @return True if the client stopped successfully, false otherwise.
   */
  bool stop() noexcept;

  /**
   * @brief Restarts the client.
   * @return True if the client restarted successfully, false otherwise.
   */
  bool restart() noexcept;

  /**
   * @brief Adds a user to the system.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was added successfully, false otherwise.
   */
  bool addUser(const std::string& username, const std::string& password) noexcept;

  /**
   * @brief Removes a user from the system.
   * @param username The username of the user to remove.
   * @return True if the user was removed successfully, false otherwise.
   */
  bool removeUser(const std::string& username) noexcept;

  /**
   * @brief Checks if a user exists in the system.
   * @param username The username to check.
   * @return True if the user exists, false otherwise.
   */
  bool isExistUser(const std::string& username) noexcept;

  /**
   * @brief Gets a list of all users.
   * @return A vector of usernames.
   */
  [[nodiscard]] std::vector<std::string> listAllUsers() noexcept;

  /**
   * @brief Authenticates a user.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the authentication was successful, false otherwise.
   */
  bool authenticateUser(const std::string& username,
                        const std::string& password) noexcept;

  /**
   * @brief Adds a tag to a user.
   * @param username The username of the user.
   * @param tag The tag to add.
   * @return True if the tag was added successfully, false otherwise.
   */
  bool addUserTag(const std::string& username, const std::string& tag) noexcept;

  /**
   * @brief Removes a tag from a user.
   * @param username The username of the user.
   * @param tag The tag to remove.
   * @return True if the tag was removed successfully, false otherwise.
   */
  bool removeUserTag(const std::string& username, const std::string& tag) noexcept;

  /**
   * @brief Gets the tags of a user.
   * @param username The username of the user.
   * @return A vector of tags.
   */
  [[nodiscard]] std::vector<std::string> getUserTags(
      const std::string& username) noexcept;

  /**
   * @brief Sends a message from one user to another.
   * @param from The username of the sender.
   * @param to The username of the receiver.
   * @param message The message to send.
   * @return True if the message was sent successfully, false otherwise.
   */
  bool sendMessage(const std::string& from, const std::string& to,
                   const std::string& message) noexcept;

  /**
   * @brief Gets the messages sent by a user.
   * @param username The username of the user.
   * @return A vector of sent messages.
   */
  [[nodiscard]] std::vector<std::string> getSentMessages(
      const std::string& username) noexcept;

  /**
   * @brief Gets the messages received by a user.
   * @param username The username of the user.
   * @return A vector of received messages.
   */
  [[nodiscard]] std::vector<std::string> getReceivedMessages(
      const std::string& username) noexcept;

  /**
   * @brief Gets the pair of a user.
   * @param username The username of the user.
   * @return A vector containing the pair of the user.
   */
  [[nodiscard]] std::vector<std::string> getPair(const std::string& username) noexcept;

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
                                   zmq::message_t& reply) noexcept;
};

#endif  // CLIENT_HPP