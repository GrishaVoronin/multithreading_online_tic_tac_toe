#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <thread>

#include "Game/Game.hpp"

#define PORT 1234

int main() {
  int server_fd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Bind failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  if (listen(server_fd, 3) < 0) {
    perror("Listen failed");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  std::cout << "Server is listening on port " << PORT << "..." << std::endl;

  int player1_socket;
  player1_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
  int player2_socket;
  player2_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
  Game new_game(player1_socket, player2_socket);
  new_game.StartGame();
}