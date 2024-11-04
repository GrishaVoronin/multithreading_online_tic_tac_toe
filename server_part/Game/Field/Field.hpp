#pragma once
#include <vector>

class Field {
public:
  Field();
  bool IsMovePossible(int position);
  void MakeMove(int position);
  bool IsWinning();
  bool IsEnd();
  std::string GetField();
private:
  void ChangeSymbol();
  bool IsCombinationWins(std::vector<int>& combination);

  std::vector<char> current_field = std::vector<char>(9);
  char current_symbol = 'X';
  std::vector<std::vector<int>> winning_combinations;
};
