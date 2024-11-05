#pragma once
#include <vector>
#include "Field/Field.hpp"

class Game {
public:
  Game(int player1_socket, int player2_socket) : players_sockets_({player1_socket, player2_socket}), field_(Field()) {}
  ~Game();
  void StartGame();

private:
  enum PlayersNumber {
    player1 = 0,
    player2 = 1
  };
  PlayersNumber GetNotPlayerMove();
  void ChangePlayerMove();
  std::string GetField();
  void SendMessage(const char* message, int player_number);
  void SendField();
  void SendEndGameMessage();
  bool IsFinished();
  void SendWinningMessage();
  void SendDrawMessage();
  void MakeMove();
  void MoveMessages();
  void AskForMove();

  std::vector<int> players_sockets_;
  PlayersNumber player_move_ = PlayersNumber::player2;
  Field field_;
};
