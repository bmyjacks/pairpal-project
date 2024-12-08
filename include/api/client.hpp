#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <zmq.hpp>

namespace api {

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
   * @brief Copy constructor for the Client class.
   * @param other The other Client object to copy from.
   */
  Client(const Client& other);

  /**
   * @brief Move constructor for the Client class.
   * @param other The other Client object to move from.
   */
  Client(Client&& other) noexcept;

  /**
   * @brief Copy assignment operator for the Client class.
   * @param other The other Client object to copy from.
   * @return A reference to the assigned Client object.
   */
  auto operator=(const Client& other) -> Client&;

  /**
   * @brief Move assignment operator for the Client class.
   * @param other The other Client object to move from.
   * @return A reference to the assigned Client object.
   */
  auto operator=(Client&& other) noexcept -> Client&;

  /**
   * @brief Destructor for the Client class.
   */
  ~Client();

  /**
   * @brief Starts the client.
   * @return True if the client started successfully, false otherwise.
   */
  auto start() noexcept -> bool;

  /**
   * @brief Stops the client.
   * @return True if the client stopped successfully, false otherwise.
   */
  auto stop() noexcept -> bool;

  /**
   * @brief Restarts the client.
   * @return True if the client restarted successfully, false otherwise.
   */
  auto restart() noexcept -> bool;

  /**
   * @brief Adds a user to the system.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the user was added successfully, false otherwise.
   */
  auto addUser(const std::string& username,
               const std::string& password) noexcept -> bool;

  /**
   * @brief Removes a user from the system.
   * @param username The username of the user to remove.
   * @return True if the user was removed successfully, false otherwise.
   */
  auto removeUser(const std::string& username) noexcept -> bool;

  /**
   * @brief Checks if a user exists in the system.
   * @param username The username to check.
   * @return True if the user exists, false otherwise.
   */
  auto isExistUser(const std::string& username) noexcept -> bool;

  /**
   * @brief Gets a list of all users.
   * @return A vector of usernames.
   */
  [[nodiscard]] auto listAllUsers() -> std::vector<std::string>;

  /**
   * @brief Authenticates a user.
   * @param username The username of the user.
   * @param password The password of the user.
   * @return True if the authentication was successful, false otherwise.
   */
  auto authenticateUser(const std::string& username,
                        const std::string& password) noexcept -> bool;

  /**
   * @brief Adds a tag to a user.
   * @param username The username of the user.
   * @param tag The tag to add.
   * @return True if the tag was added successfully, false otherwise.
   */
  auto addUserTag(const std::string& username, const std::string& tag) noexcept
      -> bool;

  /**
   * @brief Removes a tag from a user.
   * @param username The username of the user.
   * @param tag The tag to remove.
   * @return True if the tag was removed successfully, false otherwise.
   */
  auto removeUserTag(const std::string& username,
                     const std::string& tag) noexcept -> bool;

  /**
   * @brief Gets the tags of a user.
   * @param username The username of the user.
   * @return A vector of tags.
   */
  [[nodiscard]] auto getUserTags(const std::string& username)
      -> std::vector<std::string>;

  /**
   * @brief Sends a message from one user to another.
   * @param from The username of the sender.
   * @param to The username of the receiver.
   * @param message The message to send.
   * @return True if the message was sent successfully, false otherwise.
   */
  auto sendMessage(const std::string& from, const std::string& to,
                   const std::string& message) noexcept -> bool;

  /**
   * @brief Gets the messages sent by a user.
   * @param username The username of the user.
   * @return A vector of sent messages.
   */
  [[nodiscard]] auto getSentMessages(const std::string& username)
      -> std::vector<std::string>;

  /**
   * @brief Gets the messages received by a user.
   * @param username The username of the user.
   * @return A vector of received messages.
   */
  [[nodiscard]] auto getReceivedMessages(const std::string& username)
      -> std::vector<std::string>;

  /**
   * @brief Gets the pair of a user.
   * @param username The username of the user.
   * @return A vector containing the pair of the user.
   */
  [[nodiscard]] auto getPair(const std::string& username)
      -> std::vector<std::string>;

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
  auto sendRequestAndReceiveReply_(zmq::message_t& request,
                                   zmq::message_t& reply) noexcept -> bool;
};

}  // namespace api

#endif  // CLIENT_HPP