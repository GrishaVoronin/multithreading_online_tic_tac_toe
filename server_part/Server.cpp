#include "Server.hpp"
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>

void Server::StartServer() {
  if ((server_fd_ = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    std::cerr << "Socket creation failed";
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port_);

  if (bind(server_fd_, (struct sockaddr *)&address, sizeof(address)) < 0) {
    std::cerr << "Bind failed";
    close(server_fd_);
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd_, 3) < 0) {
    std::cerr << "Listen failed";
    close(server_fd_);
    exit(EXIT_FAILURE);
  }

  std::cout << "Server is listening on port " << port_ << "..." << std::endl;
}

void Server::ReceiveConnections() {
  while (true) {
    int addrlen = sizeof(address);
    int new_player_socket = accept(server_fd_, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    connector_.AddPlayer(new_player_socket);
  }
}
