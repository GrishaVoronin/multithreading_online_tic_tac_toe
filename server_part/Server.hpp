#pragma once
#include "Connector/Connector.hpp"
#include <unistd.h>
#include <netinet/in.h>

class Server {
public:
  explicit Server(int port) : port_(port), server_fd_(0) {}
 ~Server() { close(server_fd_); }
  void StartServer();
  void ReceiveConnections();
private:
  int port_;
  int server_fd_;
  Connector connector_;
  sockaddr_in address{};
};
