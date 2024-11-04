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
  if (current_symbol == 'X') {
    current_symbol = '0';
  } else {
    current_symbol = 'X';
  }
}


bool Field::IsMovePossible(int position) {
  --position;
  if (position < 0 || position > 8) {
    return false;
  }
  return current_field[position] != 'X' && current_field[position] != '0';
}

void Field::MakeMove(int position) {
  --position;
  current_field[position] = current_symbol;
  ChangeSymbol();
}

bool Field::IsCombinationWins(std::vector<int>& combination) {
  if (current_field[combination[0]] != 'X' && current_field[combination[0]] != '0') {
    return false;
  }
  return current_field[combination[0]] == current_field[combination[1]] && current_field[combination[2]] == current_field[combination[1]];
}

bool Field::IsWinning() {
  for (auto& combination: winning_combinations) {
    if (IsCombinationWins(combination)) {
      return true;
    }
  }
  return false;
}

bool Field::IsEnd() {
  for (int i = 0; i < 9; ++i) {
    if (current_field[i] != 'X' && current_field[i] != '0') {
      return false;
    }
  }
  return true;
}

std::string Field::GetField() {
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
