#pragma once
#include <vector>

class Field {
public:
  Field();
  bool IsMovePossible(int position) const;
  void MakeMove(int position);
  bool IsWinning() const;
  bool IsEnd() const;
  std::string GetField() const;
private:
  enum Symbol {
    cross = 'X',
    nought = '0'
  };
  void ChangeSymbol();
  bool IsCombinationWins(const std::vector<int>& combination) const;

  std::vector<char> current_field = std::vector<char>(9);
  Symbol current_symbol = Symbol::cross;
  std::vector<std::vector<int>> winning_combinations;
};
