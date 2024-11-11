#ifndef SERVER_HPP
#define SERVER_HPP

#include <cstdint>

/**
 * @class Server
 * @brief Represents a server that can be started, stopped, and restarted.
 */
class Server {
 public:
  /**
   * @brief Constructs a Server object.
   */
  Server();

  /**
   * @brief Destroys the Server object.
   */
  ~Server();

  /**
   * @brief Starts the server on the specified port.
   * @param listenPort The port number to listen on.
   * @return True if the server started successfully, false otherwise.
   */
  bool start(uint8_t listenPort);

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
};

#endif  // SERVER_HPP