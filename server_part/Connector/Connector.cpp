#include "Connector.hpp"
#include "../Game/Game.hpp"

#include <sys/socket.h>
#include <thread>
#include <cerrno>
#include <iostream>

bool Connector::CheckFirstPlayerConnection() const {
  char buffer;
  ssize_t result = recv(first_player_socket_, &buffer, sizeof(buffer),
                        MSG_PEEK | MSG_DONTWAIT);

  if (result == 0) {
    // recv returns 0 if the client has disconnected gracefully
    std::cout << "First player has disconnected." << std::endl;
    return false;
  }
  if (result < 0) {
    if (errno == EWOULDBLOCK || errno == EAGAIN) {
      // No data available right now, but socket is still connected
      return true;
    }
    return false;
  }
  return true;
}

void Connector::SetNewFirstPlayer(int socket) {
  first_player_socket_ = socket;
  is_first_player_waiting_ = true;
  SendMessageToFirstPlayer();
}

void Connector::StartNewGame(int second_player_socket) {
  is_first_player_waiting_ = false;
  auto new_game = std::make_shared<Game>(first_player_socket_, second_player_socket);
  std::thread game_thread(&Game::StartGame, new_game);
  game_thread.detach();  // Detach to run independently
}

void Connector::SendMessageToFirstPlayer() const {
  const char* message =
      "Welcome to the TicTacToe server version 1.0.0!\nYou are the first "
      "player!\nPlease wait for the other player to connect...\n";
  send(first_player_socket_, message, strlen(message), 0);
}

void Connector::SendMessageToSecondPlayer(int socket) const {
  const char* message = "You are the second player!\n";
  send(socket, message, strlen(message), 0);
}


void Connector::AddPlayer(int socket) {
  if (!is_first_player_waiting_) {
    SetNewFirstPlayer(socket);
  } else {
    if (CheckFirstPlayerConnection()) {
      SendMessageToSecondPlayer(socket);
      StartNewGame(socket);
    } else {
      SetNewFirstPlayer(socket);
    }
  }
}
