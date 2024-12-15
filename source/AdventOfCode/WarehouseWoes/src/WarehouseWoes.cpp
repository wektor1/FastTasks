#include "WarehouseWoes.hpp"
#include <vector>

namespace {
constexpr char up{'^'};
constexpr char down{'v'};
constexpr char left{'<'};
constexpr char right{'>'};
} // namespace

unsigned long long WarehouseWoes::run(const std::vector<std::string> &input) {
  bool isOperations{false};
  for (const auto &line : input) {
    if (line.empty()) {
      isOperations = true;
      continue;
    }
    if (not isOperations) {
      auto robot = line.find('@');
      std::vector<char> temp{};
      temp.reserve(line.size());
      temp.insert(temp.cend(), line.begin(), line.end());
      if (robot != std::string::npos) {
        temp[robot] = '.';
        startPos = {map.size(), robot};
      }
      map.push_back(std::move(temp));
    } else {
      operations.insert(operations.cend(), line.begin(), line.end());
    }
  }
  for (const auto operation : operations) {
    move(operation);
  }
  return calculateResultPart1();
}

void WarehouseWoes::move(const char direction, const int objectsToMove) {
  switch (direction) {
  case up:
    if (map[startPos.first - objectsToMove][startPos.second] == 'O') {
      move(up, objectsToMove + 1);
      return;
    }
    if (map[startPos.first - objectsToMove][startPos.second] == '.') {
      for (int i = 0; i < objectsToMove; i++) {
        map[startPos.first - objectsToMove + i][startPos.second] =
            map[startPos.first - objectsToMove + (i + 1)][startPos.second];
      }
      map[startPos.first][startPos.second] = '.';
      startPos.first--;
      return;
    }
    return;
  case down:
    if (map[startPos.first + objectsToMove][startPos.second] == 'O') {
      move(down, objectsToMove + 1);
      return;
    }
    if (map[startPos.first + objectsToMove][startPos.second] == '.') {
      for (int i = 0; i < objectsToMove; i++) {
        map[startPos.first + objectsToMove - i][startPos.second] =
            map[startPos.first + objectsToMove - (i + 1)][startPos.second];
      }
      map[startPos.first][startPos.second] = '.';
      startPos.first++;
      return;
    }
    return;
  case left:
    if (map[startPos.first][startPos.second - objectsToMove] == 'O') {
      move(left, objectsToMove + 1);
      return;
    }
    if (map[startPos.first][startPos.second - objectsToMove] == '.') {
      for (int i = 0; i < objectsToMove; i++) {
        map[startPos.first][startPos.second - objectsToMove + i] =
            map[startPos.first][startPos.second - objectsToMove + (i + 1)];
      }
      map[startPos.first][startPos.second] = '.';
      startPos.second--;
      return;
    }
    return;
  case right:
    if (map[startPos.first][startPos.second + objectsToMove] == 'O') {
      move(right, objectsToMove + 1);
      return;
    }
    if (map[startPos.first][startPos.second + objectsToMove] == '.') {
      for (int i = 0; i < objectsToMove; i++) {
        map[startPos.first][startPos.second + objectsToMove - i] =
            map[startPos.first][startPos.second + objectsToMove - (i + 1)];
      }
      map[startPos.first][startPos.second] = '.';
      startPos.second++;
      return;
    }
    return;
  default:
    return;
  }
}

unsigned long long WarehouseWoes::calculateResultPart1() {
  unsigned long long result{0};
  for (int line = 0; line < map.size(); line++) {
    for (int row = 0; row < map[line].size(); row++) {
      result += map[line][row] == 'O' ? 100 * line + row : 0;
    }
  }
  return result;
  ;
}
