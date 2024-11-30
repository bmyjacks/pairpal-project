#ifndef SERVER_HPP
#define SERVER_HPP

#include <atomic>
#include <thread>
#include <zmq.hpp>

#include "pair/pair.hpp"
#include "storage/storage.hpp"

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
  explicit Server(std::string listenAddr) noexcept;

  /**
   * @brief Destroys the Server object.
   */
  virtual ~Server() noexcept;

  /**
   * @brief Starts the server on the specified port.
   * @return True if the server started successfully, false otherwise.
   */
  bool start() noexcept;

  /**
   * @brief Stops the server.
   * @return True if the server stopped successfully, false otherwise.
   */
  bool stop() noexcept;

  /**
   * @brief Restarts the server.
   * @return True if the server restarted successfully, false otherwise.
   */
  bool restart() noexcept;

  /**
   * @brief Gets the address the server is listening on.
   * @return The listen address as a string.
   */
  [[nodiscard]] std::string getListenAddr() const noexcept;

 private:
  std::string listenAddr_;  ///< The address the server listens on.
  zmq::context_t context_;  ///< The ZeroMQ context.
  zmq::socket_t socket_;    ///< The ZeroMQ socket.
  std::atomic_bool
      running_;  ///< Atomic flag indicating if the server is running.
  std::thread serverThread_;  ///< The thread running the server.

  Pair pair_;        ///< The Pair object.
  Storage storage_;  ///< The Storage object.

  /**
   * @brief Runs the server.
   */
  void run_() noexcept;

  /**
   * @brief Handles incoming requests.
   * @param request The incoming request message.
   * @return The response message.
   */
  [[nodiscard]] zmq::message_t handleRequest_(
      const zmq::message_t& request) noexcept;

  /**
   * @brief Adds a user to the server.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was added successfully, false otherwise.
   */
  virtual bool addUser_(const std::string& username,
                        const std::string& password) noexcept;

  /**
   * @brief Removes a user from the server.
   * @param username The username of the user.
   * @return True if the user was removed successfully, false otherwise.
   */
  virtual bool removeUser_(const std::string& username) noexcept;

  /**
   * @brief Checks if a user exists.
   * @param username The username to check.
   * @return True if the user exists, false otherwise.
   */
  [[nodiscard]] virtual bool isExistUser_(const std::string& username) noexcept;

  /**
   * @brief Lists all users.
   * @return A vector of usernames.
   */
  [[nodiscard]] virtual std::vector<std::string> listAllUsers() noexcept;

  /**
   * @brief Authenticates a user.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was authenticated successfully, false otherwise.
   */
  virtual bool authenticateUser_(const std::string& username,
                                 const std::string& password) noexcept;

  /**
   * @brief Adds a tag to a user.
   * @param username The username of the user.
   * @param tag The tag to add.
   * @return True if the tag was added successfully, false otherwise.
   */
  virtual bool addUserTag_(const std::string& username,
                           const std::string& tag) noexcept;

  /**
   * @brief Removes a tag from a user.
   * @param username The username of the user.
   * @param tag The tag to remove.
   * @return True if the tag was removed successfully, false otherwise.
   */
  virtual bool removeUserTag_(const std::string& username,
                              const std::string& tag) noexcept;

  /**
   * @brief Gets the tags of a user.
   * @param username The username of the user.
   * @return A vector of tags.
   */
  [[nodiscard]] virtual std::vector<std::string> getUserTags_(
      const std::string& username) noexcept;

  /**
   * @brief Sends a message from one user to another.
   * @param from The sender's username.
   * @param to The recipient's username.
   * @param message The message content.
   * @return True if the message was sent successfully, false otherwise.
   */
  virtual bool sendMessage_(const std::string& from, const std::string& to,
                            const std::string& message) noexcept;

  /**
   * @brief Gets the sent messages of a user.
   * @param username The username of the user.
   * @return A vector of messages.
   */
  [[nodiscard]] virtual std::vector<std::string> getSentMessages_(
      const std::string& username) noexcept;

  /**
   * @brief Gets the received messages of a user.
   * @param username The username of the user.
   * @return A vector of messages.
   */
  [[nodiscard]] virtual std::vector<std::string> getReceivedMessages_(
      const std::string& username) noexcept;

  /**
   * @brief Gets the pairing information of a user.
   * @param username The username of the user needs to pair.
   * @return A vector of paired usernames.
   */
  [[nodiscard]] virtual std::vector<std::string> getPair_(
      const std::string& username) noexcept;
};

#endif  // SERVER_HPP