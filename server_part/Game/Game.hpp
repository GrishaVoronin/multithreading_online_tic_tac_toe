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
  PlayersNumber GetNotPlayerMove() const;
  void ChangePlayerMove();
  std::string GetField() const;
  void SendMessage(const char* message, int player_number) const;
  void SendField() const;
  void SendEndGameMessage() const;
  bool IsFinished() const;
  void SendWinningMessage() const;
  void SendDrawMessage() const;
  void Step();
  void MakeMove();

  std::vector<int> players_sockets_;
  PlayersNumber player_move_ = PlayersNumber::player2;
  Field field_;
};
