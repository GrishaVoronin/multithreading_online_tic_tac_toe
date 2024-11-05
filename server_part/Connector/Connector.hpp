#pragma once

class Connector {
public:
  Connector() = default;
  void AddPlayer(int socket);
private:
  bool CheckFirstPlayerConnection() const;
  void SetNewFirstPlayer(int socket);
  void StartNewGame(int second_player_socket);
  void SendMessageToFirstPlayer() const;
  void SendMessageToSecondPlayer(int socket) const;

  int first_player_socket_ = 0;
  bool is_first_player_waiting_ = false;
};
