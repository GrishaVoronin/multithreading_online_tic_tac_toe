#include "Game.hpp"

#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <thread>

Game::~Game() {
  close(players_sockets_[0]);
  close(players_sockets_[1]);
}

Game::PlayersNumber Game::GetNotPlayerMove() {
  if (player_move_ == player1) {
    return player2;
  }
  return player1;
}


void Game::SendMessage(const char* message, int player_number) {
  send(players_sockets_[player_number], message, strlen(message), 0);
}

void Game::ChangePlayerMove() {
  if (player_move_ == PlayersNumber::player1) {
    player_move_ = PlayersNumber::player2;
  } else {
    player_move_ = PlayersNumber::player1;
  }
}

std::string Game::GetField() {
  return field_.GetField();
}

void Game::SendField() {
  std::string message = "The board currently is:\n" + field_.GetField();
  SendMessage(message.c_str(), PlayersNumber::player1);
  SendMessage(message.c_str(), PlayersNumber::player2);
}

void Game::SendEndGameMessage() {
  const char* message = "The server has disconnected.\n";
  SendMessage(message, PlayersNumber::player1);
  SendMessage(message, PlayersNumber::player2);
}

void Game::StartGame() {
  const char* player1_message = "Starting the game...\nYou are playing crosses (X). Good luck!\n";
  SendMessage(player1_message, PlayersNumber::player1);
  const char* player2_message = "Starting the game...\nYou are playing noughts (0). Good luck!\n";
  SendMessage(player2_message, PlayersNumber::player2);
}

void Game::SendWinningMessage() {
  const char* win_message = "Congratulations! You won!\n";
  const char* lose_message = "Sorry! You loose!\n";
  SendMessage(win_message, player_move_);
  SendMessage(lose_message, GetNotPlayerMove());
  SendEndGameMessage();
}

void Game::SendDrawMessage() {
  const char* message = "Draw\n";
  SendMessage(message, player1);
  SendMessage(message, player2);
  SendEndGameMessage();
}


bool Game::IsFinished() {
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

void Game::MakeMove() {
  SendField();
  if (IsFinished()) {
    return;
  }
  ChangePlayerMove();
  MoveMessages();
  MakeMove();
}

void Game::MoveMessages() {
  const char* message = "Please wait for the other player's turn...\n";
  SendMessage(message, GetNotPlayerMove());
  AskForMove();
}


void Game::AskForMove() {
  const char* message = "Enter your turn:\n";
  SendMessage(message, player_move_);
  char buffer[1];
  int valread = read(players_sockets_[player_move_], buffer, 1);
  if (valread > 0) {
    int position = buffer[0] - '0';
    if (field_.IsMovePossible(position)) {
      field_.MakeMove(position);
    } else {
      const char* not_valid_pos = "Not valid position. Try again!\n";
      SendMessage(not_valid_pos, player_move_);
      AskForMove();
    }
  }
}
