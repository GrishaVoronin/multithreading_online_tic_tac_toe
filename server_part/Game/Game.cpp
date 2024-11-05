#include "Game.hpp"

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <iostream>

Game::~Game() {
  close(players_sockets_[0]);
  close(players_sockets_[1]);
}

Game::PlayersNumber Game::GetNotPlayerMove() const {
  if (player_move_ == player1) {
    return player2;
  }
  return player1;
}


void Game::SendMessage(const char* message, int player_number) const {
  send(players_sockets_[player_number], message, strlen(message), 0);
}

void Game::ChangePlayerMove() {
  if (player_move_ == PlayersNumber::player1) {
    player_move_ = PlayersNumber::player2;
  } else {
    player_move_ = PlayersNumber::player1;
  }
}

std::string Game::GetField() const {
  return field_.GetField();
}

void Game::SendField() const {
  std::string message = "The board currently is:\n" + field_.GetField();
  SendMessage(message.c_str(), PlayersNumber::player1);
  SendMessage(message.c_str(), PlayersNumber::player2);
}

void Game::SendEndGameMessage() const {
  const char* message = "The server has disconnected.\n";
  SendMessage(message, PlayersNumber::player1);
  SendMessage(message, PlayersNumber::player2);
}

void Game::StartGame() {
  const char* player1_message = "Starting the game...\nYou are playing crosses (X). Good luck!\n";
  SendMessage(player1_message, PlayersNumber::player1);
  const char* player2_message = "Starting the game...\nYou are playing noughts (0). Good luck!\n";
  SendMessage(player2_message, PlayersNumber::player2);
  Step();
}

void Game::SendWinningMessage() const {
  const char* win_message = "Congratulations! You won!\n";
  const char* lose_message = "Sorry! You loose!\n";
  SendMessage(win_message, player_move_);
  SendMessage(lose_message, GetNotPlayerMove());
  SendEndGameMessage();
}

void Game::SendDrawMessage() const {
  const char* message = "Draw\n";
  SendMessage(message, player1);
  SendMessage(message, player2);
  SendEndGameMessage();
}


bool Game::IsFinished() const {
  if (field_.IsWinning()) {
    SendWinningMessage();
    return true;
  }
  if (field_.IsEnd()) {
    SendDrawMessage();
    return true;
  }
  return false;
}

void Game::Step() {
  SendField();
  if (IsFinished()) {
    return;
  }
  ChangePlayerMove();
  MakeMove();
  Step();
}

void Game::MakeMove() {
  const char* waiting_message = "Please wait for the other player's turn...\n";
  SendMessage(waiting_message, GetNotPlayerMove());

  const char* message = "Enter your turn:\n";
  SendMessage(message, player_move_);
  char buffer[1024];
  ssize_t valread = read(players_sockets_[player_move_], buffer, 1024);
  if (valread > 0) {
    int position = atoi(buffer);
    if (field_.IsMovePossible(position)) {
      field_.MakeMove(position);
      return;
    }
    const char* not_valid_pos = "Not valid position. Try again!\n";
    SendMessage(not_valid_pos, player_move_);
    MakeMove();
  }
}
