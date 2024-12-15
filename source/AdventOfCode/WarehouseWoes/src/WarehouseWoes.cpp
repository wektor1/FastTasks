#include "WarehouseWoes.hpp"
#include <algorithm>
#include <map>
#include <utility>
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
      std::vector<char> temp{};
      temp.reserve(line.size() * 2);
      for (auto object : line) {
        if (object == '#' or object == '.') {
          temp.insert(temp.cend(), 2, object);
        } else if (object == 'O') {
          temp.push_back('[');
          temp.push_back(']');
        } else if (object == '@') {
          temp.push_back('@');
          temp.push_back('.');
        }
      }
      auto robot = std::ranges::find(temp, '@');
      if (robot != temp.end()) {
        *robot = '.';
        startPos = {map.size(), robot - temp.begin()};
      }
      map.push_back(std::move(temp));
    } else {
      operations.insert(operations.cend(), line.begin(), line.end());
    }
  }
  for (const auto operation : operations) {
    std::vector<decltype(startPos)> startinList{};
    move(operation, startPos, startinList);
  }
  return calculateResultPart2();
}

bool WarehouseWoes::move(const char direction,
                         std::pair<int, int> objectToCheck,
                         std::vector<std::pair<int, int>> &objectsToMove) {
  switch (direction) {
  case up:
    if (objectToCheck == startPos) {
      objectsToMove.push_back(objectToCheck);
      objectToCheck.first--;
      if (move(direction, objectToCheck, objectsToMove)) {
        std::map<std::pair<int, int>, char> temp{};
        for (const auto object : objectsToMove) {
          temp[object] = map[object.first][object.second];
        }
        for (auto tempObjMapped : temp) {
          map[tempObjMapped.first.first - 1][tempObjMapped.first.second] =
              tempObjMapped.second;
          if ((tempObjMapped.second == '[' or tempObjMapped.second == ']') and
              not temp.contains({tempObjMapped.first.first + 1,
                                 tempObjMapped.first.second})) {
            map[tempObjMapped.first.first][tempObjMapped.first.second] = '.';
          }
        }
        startPos.first--;
      }
      return true;
    }
    if (map[objectToCheck.first][objectToCheck.second] == '[') {
      objectsToMove.push_back(objectToCheck);
      std::pair<int, int> secondObjectToCheck = {objectToCheck.first,
                                                 objectToCheck.second + 1};
      objectsToMove.push_back(secondObjectToCheck);
      if (map[secondObjectToCheck.first + 1][secondObjectToCheck.second] ==
          '.') {
        objectsToMove.push_back(
            {secondObjectToCheck.first + 1, secondObjectToCheck.second});
      }
      objectToCheck.first--;
      secondObjectToCheck.first--;
      return move(up, objectToCheck, objectsToMove) and
             move(up, secondObjectToCheck, objectsToMove);
    }
    if (map[objectToCheck.first][objectToCheck.second] == ']') {
      objectsToMove.push_back(objectToCheck);
      std::pair<int, int> secondObjectToCheck = {objectToCheck.first,
                                                 objectToCheck.second - 1};
      objectsToMove.push_back(secondObjectToCheck);
      if (map[secondObjectToCheck.first + 1][secondObjectToCheck.second] ==
          '.') {
        objectsToMove.push_back(
            {secondObjectToCheck.first + 1, secondObjectToCheck.second});
      }
      objectToCheck.first--;
      secondObjectToCheck.first--;
      return move(up, objectToCheck, objectsToMove) and
             move(up, secondObjectToCheck, objectsToMove);
    }
    if (map[objectToCheck.first][objectToCheck.second] == '.') {
      return true;
    }
    return false;
  case down:
    if (objectToCheck == startPos) {
      objectsToMove.push_back(objectToCheck);
      objectToCheck.first++;
      if (move(direction, objectToCheck, objectsToMove)) {
        std::map<std::pair<int, int>, char> temp{};
        for (const auto object : objectsToMove) {
          temp[object] = map[object.first][object.second];
        }
        for (auto tempObjMapped : temp) {
          map[tempObjMapped.first.first + 1][tempObjMapped.first.second] =
              tempObjMapped.second;
          if ((tempObjMapped.second == '[' or tempObjMapped.second == ']') and
              not temp.contains({tempObjMapped.first.first - 1,
                                 tempObjMapped.first.second})) {
            map[tempObjMapped.first.first][tempObjMapped.first.second] = '.';
          }
        }
        startPos.first++;
      }
      return true;
    }
    if (map[objectToCheck.first][objectToCheck.second] == '[') {
      objectsToMove.push_back(objectToCheck);
      std::pair<int, int> secondObjectToCheck = {objectToCheck.first,
                                                 objectToCheck.second + 1};
      objectsToMove.push_back(secondObjectToCheck);
      if (map[secondObjectToCheck.first - 1][secondObjectToCheck.second] ==
          '.') {
        objectsToMove.push_back(
            {secondObjectToCheck.first - 1, secondObjectToCheck.second});
      }
      objectToCheck.first++;
      secondObjectToCheck.first++;
      return move(direction, objectToCheck, objectsToMove) and
             move(direction, secondObjectToCheck, objectsToMove);
    }
    if (map[objectToCheck.first][objectToCheck.second] == ']') {
      objectsToMove.push_back(objectToCheck);
      std::pair<int, int> secondObjectToCheck = {objectToCheck.first,
                                                 objectToCheck.second - 1};
      objectsToMove.push_back(secondObjectToCheck);
      if (map[secondObjectToCheck.first - 1][secondObjectToCheck.second] ==
          '.') {
        objectsToMove.push_back(
            {secondObjectToCheck.first - 1, secondObjectToCheck.second});
      }
      objectToCheck.first++;
      secondObjectToCheck.first++;
      return move(direction, objectToCheck, objectsToMove) and
             move(direction, secondObjectToCheck, objectsToMove);
    }
    if (map[objectToCheck.first][objectToCheck.second] == '.') {
      return true;
    }
    return false;
  case left:
    if (objectToCheck == startPos) {
      objectsToMove.push_back(objectToCheck);
      objectToCheck.second--;
      if (move(direction, objectToCheck, objectsToMove)) {
        for (int i = objectsToMove.size() - 1; i >= 0; i--) {
          auto object = objectsToMove[i];
          map[object.first][object.second - 1] =
              map[object.first][object.second];
        }
        startPos.second--;
      }
      return true;
    }
    if (map[objectToCheck.first][objectToCheck.second] == '[' or
        map[objectToCheck.first][objectToCheck.second] == ']') {

      objectsToMove.push_back(objectToCheck);
      objectToCheck.second--;
      return move(direction, objectToCheck, objectsToMove);
    }
    if (map[objectToCheck.first][objectToCheck.second] == '.') {
      return true;
    }
    return false;
  case right:
    if (objectToCheck == startPos) {
      objectsToMove.push_back(objectToCheck);
      objectToCheck.second++;
      if (move(direction, objectToCheck, objectsToMove)) {
        for (int i = objectsToMove.size() - 1; i >= 0; i--) {
          auto object = objectsToMove[i];
          map[object.first][object.second + 1] =
              map[object.first][object.second];
        }
        startPos.second++;
      }
      return true;
    }
    if (map[objectToCheck.first][objectToCheck.second] == '[' or
        map[objectToCheck.first][objectToCheck.second] == ']') {

      objectsToMove.push_back(objectToCheck);
      objectToCheck.second++;
      return move(direction, objectToCheck, objectsToMove);
    }
    if (map[objectToCheck.first][objectToCheck.second] == '.') {
      return true;
    }
    return false;
  default:
    return false;
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
}

unsigned long long WarehouseWoes::calculateResultPart2() {
  unsigned long long result{0};
  for (int line = 0; line < map.size(); line++) {
    for (int row = 0; row < map[line].size(); row++) {
      result += map[line][row] == '[' ? 100 * line + row : 0;
    }
  }
  return result;
}
