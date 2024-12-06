#include "GuardGallivant.hpp"
#include <set>

int GuardGallivant::run(const std::vector<std::string> &input) {
  map = input;
  startPatrol(findStartPosition());

  return possibleLoopTriggers;
}

std::pair<int, int> GuardGallivant::findStartPosition() {
  for (int line = 0; line < map.size(); line++) {
    for (int position = 0; position < map[line].size(); position++) {
      if (map[line][position] == '^') {
        return {line, position};
      }
    }
  }
  return {0, 0};
}

void GuardGallivant::startPatrol(std::pair<int, int> startingPoint) {
  map[startingPoint.first][startingPoint.second] = 'X';
  goUp(startingPoint);
}

void GuardGallivant::goUp(std::pair<int, int> position) {
  if (position.first != 0) {
    if (map[position.first - 1][position.second] != '#') {
      if (map[position.first - 1][position.second] != 'X') {
        map[position.first - 1][position.second] = '#';
        possibleLoopTriggers += isLoop(position, '>') ? 1 : 0;
      }
      map[--position.first][position.second] = 'X';
      goUp(position);
    } else {
      goRight(position);
    }
  }
}

void GuardGallivant::goRight(std::pair<int, int> position) {
  if (position.second != map[0].size() - 1) {
    if (map[position.first][position.second + 1] != '#') {
      if (map[position.first][position.second + 1] != 'X') {
        map[position.first][position.second + 1] = '#';
        possibleLoopTriggers += isLoop(position, 'v') ? 1 : 0;
      }
      map[position.first][++position.second] = 'X';
      goRight(position);
    } else {
      goDown(position);
    }
  }
}

void GuardGallivant::goDown(std::pair<int, int> position) {
  if (position.first != map.size() - 1) {
    if (map[position.first + 1][position.second] != '#') {
      if (map[position.first + 1][position.second] != 'X') {
        map[position.first + 1][position.second] = '#';
        possibleLoopTriggers += isLoop(position, '<') ? 1 : 0;
      }
      map[++position.first][position.second] = 'X';
      goDown(position);
    } else {
      goLeft(position);
    }
  }
}

void GuardGallivant::goLeft(std::pair<int, int> position) {
  if (position.second != 0) {
    if (map[position.first][position.second - 1] != '#') {
      if (map[position.first][position.second - 1] != 'X') {
        map[position.first][position.second - 1] = '#';
        possibleLoopTriggers += isLoop(position, '^') ? 1 : 0;
      }
      map[position.first][--position.second] = 'X';
      goLeft(position);
    } else {
      goUp(position);
    }
  }
}

int GuardGallivant::countRoute() {
  int result{0};
  for (const auto &line : map) {
    for (const auto position : line) {
      result += position == 'X' ? 1 : 0;
    }
  }
  return result;
}

std::pair<int, int> GuardGallivant::loopUp(std::pair<int, int> position) {
  if (position == std::pair<int, int>{-1, -1}) {
    return position;
  }
  while (position.first > 0) {
    if (map[position.first - 1][position.second] == '#') {
      return position;
    }
    position.first--;
  }
  return {-1, -1};
}

std::pair<int, int> GuardGallivant::loopRight(std::pair<int, int> position) {
  if (position == std::pair<int, int>{-1, -1}) {
    return position;
  }
  while (position.second < map[0].size() - 1) {
    if (map[position.first][position.second + 1] == '#') {
      return position;
    }
    position.second++;
  }
  return {-1, -1};
}

std::pair<int, int> GuardGallivant::loopLeft(std::pair<int, int> position) {
  if (position == std::pair<int, int>{-1, -1}) {
    return position;
  }
  while (position.second > 0) {
    if (map[position.first][position.second - 1] == '#') {
      return position;
    }
    position.second--;
  }
  return {-1, -1};
}

std::pair<int, int> GuardGallivant::loopDown(std::pair<int, int> position) {
  if (position == std::pair<int, int>{-1, -1}) {
    return position;
  }
  while (position.first < map.size() - 1) {
    if (map[position.first + 1][position.second] == '#') {
      return position;
    }
    position.first++;
  }
  return {-1, -1};
}

bool GuardGallivant::isLoop(std::pair<int, int> loopStart,
                            const char direction) {

  std::set<std::pair<int, int>> positionsUp{};
  std::set<std::pair<int, int>> positionsRight{};
  std::set<std::pair<int, int>> positionsDown{};
  std::set<std::pair<int, int>> positionsLeft{};

  switch (direction) {
  case '^':
    while (loopStart != std::pair<int, int>{-1, -1}) {
      loopStart = loopUp(loopStart);
      if (positionsUp.contains(loopStart)) {
        return true;
      }
      positionsUp.insert(loopStart);
      loopStart = loopRight(loopStart);
      if (positionsRight.contains(loopStart)) {
        return true;
      }
      positionsRight.insert(loopStart);
      loopStart = loopDown(loopStart);
      if (positionsDown.contains(loopStart)) {
        return true;
      }
      positionsDown.insert(loopStart);
      loopStart = loopLeft(loopStart);
      if (positionsLeft.contains(loopStart)) {
        return true;
      }
      positionsLeft.insert(loopStart);
    }
    break;
  case '>':
    while (loopStart != std::pair<int, int>{-1, -1}) {
      loopStart = loopRight(loopStart);
      if (positionsRight.contains(loopStart)) {
        return true;
      }
      positionsRight.insert(loopStart);
      loopStart = loopDown(loopStart);
      if (positionsDown.contains(loopStart)) {
        return true;
      }
      positionsDown.insert(loopStart);
      loopStart = loopLeft(loopStart);
      if (positionsLeft.contains(loopStart)) {
        return true;
      }
      positionsLeft.insert(loopStart);
      loopStart = loopUp(loopStart);
      if (positionsUp.contains(loopStart)) {
        return true;
      }
      positionsUp.insert(loopStart);
    }
    break;
  case 'v':
    while (loopStart != std::pair<int, int>{-1, -1}) {
      loopStart = loopDown(loopStart);
      if (positionsDown.contains(loopStart)) {
        return true;
      }
      positionsDown.insert(loopStart);
      loopStart = loopLeft(loopStart);
      if (positionsLeft.contains(loopStart)) {
        return true;
      }
      positionsLeft.insert(loopStart);
      loopStart = loopUp(loopStart);
      if (positionsUp.contains(loopStart)) {
        return true;
      }
      positionsUp.insert(loopStart);
      loopStart = loopRight(loopStart);
      if (positionsRight.contains(loopStart)) {
        return true;
      }
      positionsRight.insert(loopStart);
    }
    break;
  case '<':
    while (loopStart != std::pair<int, int>{-1, -1}) {

      loopStart = loopLeft(loopStart);
      if (positionsLeft.contains(loopStart)) {
        return true;
      }
      positionsLeft.insert(loopStart);
      loopStart = loopUp(loopStart);
      if (positionsUp.contains(loopStart)) {
        return true;
      }
      positionsUp.insert(loopStart);
      loopStart = loopRight(loopStart);
      if (positionsRight.contains(loopStart)) {
        return true;
      }
      positionsRight.insert(loopStart);
      loopStart = loopDown(loopStart);
      if (positionsDown.contains(loopStart)) {
        return true;
      }
      positionsDown.insert(loopStart);
    }
    break;
  }
  return false;
}
