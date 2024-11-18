#ifndef SERVER_HPP
#define SERVER_HPP

#include <atomic>
#include <thread>
#include <zmq.hpp>

/**
 * @class Server
 * @brief Represents a server that can be started, stopped, and restarted.
 */
class Server {
 public:
  /**
   * @brief Constructs a Server object.
   * @param listenAddr The address the server will listen on.
   */
  explicit Server(std::string listenAddr);

  /**
   * @brief Destroys the Server object.
   */
  ~Server();

  /**
   * @brief Starts the server on the specified port.
   * @return True if the server started successfully, false otherwise.
   */
  bool start();

  /**
   * @brief Stops the server.
   * @return True if the server stopped successfully, false otherwise.
   */
  bool stop();

  /**
   * @brief Restarts the server.
   * @return True if the server restarted successfully, false otherwise.
   */
  bool restart();

  /**
   * @brief Gets the address the server is listening on.
   * @return The listen address as a string.
   */
  [[nodiscard]] std::string getListenAddr() const;

 private:
  std::string listenAddr_;  ///< The address the server listens on.
  zmq::context_t context_;  ///< The ZeroMQ context.
  zmq::socket_t socket_;    ///< The ZeroMQ socket.
  std::atomic_bool
      running_;  ///< Atomic flag indicating if the server is running.
  std::thread serverThread_;  ///< The thread running the server.

  /**
   * @brief Runs the server.
   */
  void run_();

  /**
   * @brief Handles incoming requests.
   * @param request The incoming request message.
   * @return The response message.
   */
  [[nodiscard]] static zmq::message_t handleRequest_(
      const zmq::message_t& request);

  /**
   * @brief Adds a user to the server.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was added successfully, false otherwise.
   */
  static bool addUser_(const std::string& username,
                       const std::string& password);

  /**
   * @brief Removes a user from the server.
   * @param username The username of the user.
   * @return True if the user was removed successfully, false otherwise.
   */
  static bool removeUser_(const std::string& username);

  /**
   * @brief Checks if a user exists.
   * @param username The username to check.
   * @return True if the user exists, false otherwise.
   */
  [[nodiscard]] static bool isExistUser_(const std::string& username);

  /**
   * @brief Lists all users.
   * @return A vector of usernames.
   */
  [[nodiscard]] static std::vector<std::string> listAllUsers();

  /**
   * @brief Authenticates a user.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was authenticated successfully, false otherwise.
   */
  static bool authenticateUser_(const std::string& username,
                                const std::string& password);

  /**
   * @brief Adds a tag to a user.
   * @param username The username of the user.
   * @param tag The tag to add.
   * @return True if the tag was added successfully, false otherwise.
   */
  static bool addUserTag_(const std::string& username, const std::string& tag);

  /**
   * @brief Removes a tag from a user.
   * @param username The username of the user.
   * @param tag The tag to remove.
   * @return True if the tag was removed successfully, false otherwise.
   */
  static bool removeUserTag_(const std::string& username, const std::string& tag);

  /**
   * @brief Gets the tags of a user.
   * @param username The username of the user.
   * @return A vector of tags.
   */
  [[nodiscard]] static std::vector<std::string> getUserTags_(
      const std::string& username);

  /**
   * @brief Sends a message from one user to another.
   * @param from The sender's username.
   * @param to The recipient's username.
   * @param message The message content.
   * @return True if the message was sent successfully, false otherwise.
   */
  static bool sendMessage_(const std::string& from, const std::string& to,
                           const std::string& message);

  /**
   * @brief Gets the sent messages of a user.
   * @param username The username of the user.
   * @return A vector of messages.
   */
  [[nodiscard]] static std::vector<std::string> getSentMessages_(
      const std::string& username);

  /**
   * @brief Gets the received messages of a user.
   * @param username The username of the user.
   * @return A vector of messages.
   */
  [[nodiscard]] static std::vector<std::string> getReceivedMessages_(
      const std::string& username);

  /**
   * @brief Gets the pairing information of a user.
   * @param username The username of the user needs to pair.
   * @return A vector of paired usernames.
   */
  [[nodiscard]] static std::vector<std::string> getPair_(
      const std::string& username);
};

#endif  // SERVER_HPP