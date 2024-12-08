#ifndef SERVER_HPP
#define SERVER_HPP

#include <atomic>
#include <chat.hpp>
#include <pair.hpp>
#include <storage.hpp>
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
  virtual ~Server();

  /**
   * @brief Starts the server on the specified port.
   * @return True if the server started successfully, false otherwise.
   */
  auto start() -> bool;

  /**
   * @brief Stops the server.
   * @return True if the server stopped successfully, false otherwise.
   */
  auto stop() -> bool;

  /**
   * @brief Gets the address the server is listening on.
   * @return The listen address as a string.
   */
  [[nodiscard]] auto getListenAddr() const -> std::string;

 private:
  std::string listenAddr_;  ///< The address the server listens on.
  zmq::context_t context_;  ///< The ZeroMQ context.
  zmq::socket_t socket_;    ///< The ZeroMQ socket.
  std::atomic_bool
      running_;  ///< Atomic flag indicating if the server is running.
  std::thread serverThread_;  ///< The thread running the server.

  Chat chat_;        ///< The Chat object.
  Pair pair_;        ///< The Pair object.
  Storage storage_;  ///< The Storage object.

  /**
   * @brief Runs the server.
   */
  void run_();

  /**
   * @brief Handles incoming requests.
   * @param request The incoming request message.
   * @return The response message.
   */
  [[nodiscard]] auto handleRequest_(const zmq::message_t& request)
      -> zmq::message_t;

  /**
   * @brief Adds a user to the server.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was added successfully, false otherwise.
   */
  virtual auto addUser_(const std::string& username,
                        const std::string& password) -> bool;

  /**
   * @brief Removes a user from the server.
   * @param username The username of the user.
   * @return True if the user was removed successfully, false otherwise.
   */
  virtual auto removeUser_(const std::string& username) -> bool;

  /**
   * @brief Checks if a user exists.
   * @param username The username to check.
   * @return True if the user exists, false otherwise.
   */
  [[nodiscard]] virtual auto isExistUser_(const std::string& username) -> bool;

  /**
   * @brief Lists all users.
   * @return A vector of usernames.
   */
  [[nodiscard]] virtual auto listAllUsers() -> std::vector<std::string>;

  /**
   * @brief Authenticates a user.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was authenticated successfully, false otherwise.
   */
  virtual auto authenticateUser_(const std::string& username,
                                 const std::string& password) -> bool;

  /**
   * @brief Adds a tag to a user.
   * @param username The username of the user.
   * @param tag The tag to add.
   * @return True if the tag was added successfully, false otherwise.
   */
  virtual auto addUserTag_(const std::string& username, const std::string& tag)
      -> bool;

  /**
   * @brief Removes a tag from a user.
   * @param username The username of the user.
   * @param tag The tag to remove.
   * @return True if the tag was removed successfully, false otherwise.
   */
  virtual auto removeUserTag_(const std::string& username,
                              const std::string& tag) -> bool;

  /**
   * @brief Gets the tags of a user.
   * @param username The username of the user.
   * @return A vector of tags.
   */
  [[nodiscard]] virtual auto getUserTags_(const std::string& username)
      -> std::vector<std::string>;

  /**
   * @brief Sends a message from one user to another.
   * @param from The sender's username.
   * @param to The recipient's username.
   * @param message The message content.
   * @return True if the message was sent successfully, false otherwise.
   */
  virtual auto sendMessage_(const std::string& from, const std::string& to,
                            const std::string& message) -> bool;

  /**
   * @brief Gets the sent messages of a user.
   * @param username The username of the user.
   * @return A vector of messages.
   */
  [[nodiscard]] virtual auto getSentMessages_(const std::string& username)
      -> std::vector<std::string>;

  /**
   * @brief Gets the received messages of a user.
   * @param username The username of the user.
   * @return A vector of messages.
   */
  [[nodiscard]] virtual auto getReceivedMessages_(const std::string& username)
      -> std::vector<std::string>;

  /**
   * @brief Gets the pairing information of a user.
   * @param username The username of the user needs to pair.
   * @return A vector of paired usernames.
   */
  [[nodiscard]] virtual auto getPair_(const std::string& username)
      -> std::vector<std::string>;
};

#endif  // SERVER_HPP
