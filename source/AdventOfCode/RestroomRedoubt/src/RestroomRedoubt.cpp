#include "RestroomRedoubt.hpp"
#include "Utils/Parsers.hpp"
#include <algorithm>
#include <array>
#include <cstdio>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

namespace {
constexpr int wide = 101;
constexpr int tall = 103;

inline bool isInWide(int x) { return x < wide and x >= 0; }
inline int teleportWide(int x) { return x >= wide ? x - wide : wide + x; }

inline bool isInTall(int y) { return y < tall and y >= 0; }
inline int teleportTall(int y) { return y >= tall ? y - tall : tall + y; }
} // namespace

unsigned long long RestroomRedoubt::run(const std::vector<std::string> &input) {
  for (const auto &line : input) {
    auto parsed = parsers::parseNumbersFromLineWithNegative(line);
    robots.emplace_back(std::pair<int, int>{parsed[0], parsed[1]},
                        std::pair<int, int>{parsed[2], parsed[3]});
  }
  moveAllRobotsInTime();
  return getSafetyFactor();
}

void RestroomRedoubt::moveAllRobotsInTime() {
  int seconds{0};
  unsigned long long possibleWin = getSafetyFactor();
  while (seconds < 1000000) {
    seconds++;
    std::map<std::pair<int, int>, int> positionsCount{};
    for (auto &robot : robots) {
      moveSecond(robot);
      if (positionsCount.contains(robot.start)) {
        positionsCount[robot.start]++;
      } else {
        positionsCount[robot.start] = 0;
      }
    }
    unsigned long long newWin = getSafetyFactor();
    if (possibleWin >= newWin) {
      possibleWin = newWin;
      printRobotsPositions(seconds);
    }
  }
}

void RestroomRedoubt::moveSecond(Robot &robot) {
  auto x = robot.start.first + robot.velocity.first;
  robot.start.first = isInWide(x) ? x : teleportWide(x);
  auto y = robot.start.second + robot.velocity.second;
  robot.start.second = isInTall(y) ? y : teleportTall(y);
}

void RestroomRedoubt::printRobotsPositions(int seconds) {
  std::array<std::array<char, 101>, 103> map;
  std::array<char, 101> emptyLine;
  emptyLine.fill(' ');
  map.fill(emptyLine);
  for (const auto &robot : robots) {
    map[robot.start.second - 1][robot.start.first - 1] = 'X';
  }
  std::ostringstream stream;
  for (const auto &line : map) {
    for (const auto c : line) {
      stream << c;
    }
    stream << '\n';
  }
  stream << seconds << '\n';
  std::cout << stream.str();
}

unsigned long long RestroomRedoubt::getSafetyFactor() {
  auto first = getFactorFirstQ();
  auto second = getFactorSecondQ();
  auto third = getFactorThirdQ();
  auto fourth = getFactorFourthQ();

  return first * second * third * fourth;
}

unsigned long long RestroomRedoubt::getFactorFirstQ() {
  return std::ranges::count_if(robots, [](const auto &robot) {
    return robot.start.first < wide / 2 and robot.start.second < tall / 2;
  });
}

unsigned long long RestroomRedoubt::getFactorSecondQ() {
  return std::ranges::count_if(robots, [](const auto &robot) {
    return robot.start.first > wide / 2 and robot.start.second < tall / 2;
  });
}

unsigned long long RestroomRedoubt::getFactorThirdQ() {
  return std::ranges::count_if(robots, [](const auto &robot) {
    return robot.start.first < wide / 2 and robot.start.second > tall / 2;
  });
}

unsigned long long RestroomRedoubt::getFactorFourthQ() {
  return std::ranges::count_if(robots, [](const auto &robot) {
    return robot.start.first > wide / 2 and robot.start.second > tall / 2;
  });
}
