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

 private:
  std::string listenAddr_;
  zmq::context_t context_;
  zmq::socket_t socket_;
};

#endif  // SERVER_HPP