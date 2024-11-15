#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdint>
#include <zmq.hpp>

/**
 * @class Server
 * @brief Represents a server that can be started, stopped, and restarted.
 */
class Server {
 public:
  /**
   * @brief Constructs a Server object.
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

  [[nodiscard]] std::string getListenAddr() const;

 private:
  std::string listenAddr_;
  zmq::context_t context_;
  zmq::socket_t socket_;

  [[nodiscard]] bool handleRequest_(const zmq::message_t& request);
  [[nodiscard]] static bool addUser_(const std::string& username,
                                     const std::string& password);
  [[nodiscard]] static bool removeUser_(const std::string& username);
  [[nodiscard]] static bool authenticateUser_(const std::string& username,
                                       const std::string& password);
  [[nodiscard]] bool isExistUser_(const std::string& username);
  [[nodiscard]] std::vector<std::string> listUsers();
  [[nodiscard]] bool sendMessage_(const std::string& from,
                                  const std::string& to,
                                  const std::string& message);
  [[nodiscard]] bool addUserTag_(const std::string& username,
                                 const std::string& tag);
  [[nodiscard]] std::vector<std::string> getUserTags_(
      const std::string& username);
  [[nodiscard]] std::vector<std::string> getSentMessages_(
      const std::string& username);
  [[nodiscard]] std::vector<std::string> getPair_(const std::string& username);
};

#endif  // SERVER_HPP