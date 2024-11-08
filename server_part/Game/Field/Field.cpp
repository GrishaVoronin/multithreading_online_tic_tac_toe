#include "Field.hpp"

Field::Field() {
  for (char i = '1'; i <= '9'; ++i) {
    current_field[i - '0' - 1] = i;
  }
  winning_combinations.emplace_back(std::vector<int>{0, 1, 2});
  winning_combinations.emplace_back(std::vector<int>{3, 4, 5});
  winning_combinations.emplace_back(std::vector<int>{6, 7, 8});
  winning_combinations.emplace_back(std::vector<int>{0, 3, 6});
  winning_combinations.emplace_back(std::vector<int>{1, 4, 7});
  winning_combinations.emplace_back(std::vector<int>{2, 5, 8});
  winning_combinations.emplace_back(std::vector<int>{0, 4, 8});
  winning_combinations.emplace_back(std::vector<int>{2, 4, 6});
}

void Field::ChangeSymbol() {
  if (current_symbol == Symbol::cross) {
    current_symbol = Symbol::nought;
  } else {
    current_symbol = Symbol::cross;
  }
}


bool Field::IsMovePossible(int position) const {
  --position;
  if (position < 0 || position > 8) {
    return false;
  }
  return current_field[position] != Symbol::cross && current_field[position] != Symbol::nought;
}

void Field::MakeMove(int position) {
  --position;
  current_field[position] = current_symbol;
  ChangeSymbol();
}

bool Field::IsCombinationWins(const std::vector<int>& combination) const {
  if (current_field[combination[0]] != Symbol::cross && current_field[combination[0]] != Symbol::nought) {
    return false;
  }
  return current_field[combination[0]] == current_field[combination[1]] && current_field[combination[2]] == current_field[combination[1]];
}

bool Field::IsWinning() const {
  for (auto& combination: winning_combinations) {
    if (IsCombinationWins(combination)) {
      return true;
    }
  }
  return false;
}

bool Field::IsEnd() const {
  for (int i = 0; i < 9; ++i) {
    if (current_field[i] != Symbol::cross && current_field[i] != Symbol::nought) {
      return false;
    }
  }
  return true;
}

std::string Field::GetField() const {
  std::string field;
  for (size_t line = 0; line < 3; ++line) {
    for (size_t row = 0; row < 3; ++row) {
      field += current_field[line * 3 + row];
      field += ' ';
    }
    field += '\n';
  }
  return field;
}
