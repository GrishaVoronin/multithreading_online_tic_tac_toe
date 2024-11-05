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
  enum Symbol {
    cross = 'X',
    nought = '0'
  };
  void ChangeSymbol();
  bool IsCombinationWins(std::vector<int>& combination);

  std::vector<char> current_field = std::vector<char>(9);
  Symbol current_symbol = Symbol::cross;
  std::vector<std::vector<int>> winning_combinations;
};
