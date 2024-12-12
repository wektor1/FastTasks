#include "GardenGroups.hpp"
#include <algorithm>
#include <map>
#include <set>

namespace {
enum class SidesDirection { up, down, right, left };

bool isFenceUp(const std::vector<std::string> &input, char sign,
               std::pair<int, int> position) {
  return position.first == 0 or
         input[position.first - 1][position.second] != sign;
}

bool isFenceDown(const std::vector<std::string> &input, char sign,
                 std::pair<int, int> position) {
  return position.first == input.size() - 1 or
         input[position.first + 1][position.second] != sign;
}

bool isFenceRight(const std::vector<std::string> &input, char sign,
                  std::pair<int, int> position) {
  return position.second == input[position.first].size() - 1 or
         input[position.first][position.second + 1] != sign;
}

bool isFenceLeft(const std::vector<std::string> &input, char sign,
                 std::pair<int, int> position) {
  return position.second == 0 or
         input[position.first][position.second - 1] != sign;
}

unsigned long long
calculateSidesInLines(std::vector<std::pair<int, int>> &input) {
  unsigned long long sides{0};
  while (not input.empty()) {
    auto [line, row] = input.back();
    input.pop_back();
    std::set<int> rows{row + 1, row - 1};
    while (not rows.empty()) {
      input.erase(std::remove_if(
                      input.begin(), input.end(),
                      [line, row = rows.extract(rows.begin()).value(),
                       &rows](auto position) {
                        if (position.first == line and position.second == row) {
                          rows.insert(position.second + 1);
                          rows.insert(position.second - 1);
                          return true;
                        }
                        return false;
                      }),
                  input.end());
    }
    sides++;
  }
  return sides;
}

unsigned long long
calculateSidesInRows(std::vector<std::pair<int, int>> &input) {
  unsigned long long sides{0};
  while (not input.empty()) {
    auto [line, row] = input.back();
    input.pop_back();
    std::set<int> lines{line + 1, line - 1};
    while (not lines.empty()) {
      input.erase(std::remove_if(
                      input.begin(), input.end(),
                      [row, line = lines.extract(lines.begin()).value(),
                       &lines](auto position) {
                        if (position.first == line and position.second == row) {
                          lines.insert(position.first + 1);
                          lines.insert(position.first - 1);
                          return true;
                        }
                        return false;
                      }),
                  input.end());
    }
    sides++;
  }
  return sides;
}
} // namespace

unsigned long long GardenGroups::run(const std::vector<std::string> &input) {
  calculatedGardenMap.reserve(input.size());
  for (int i = 0; i < input.size(); i++) {
    calculatedGardenMap.push_back(std::vector<char>(input[i].size(), ' '));
  }

  unsigned long long result{0};
  for (int i = 0; i < calculatedGardenMap.size(); i++) {
    for (int j = 0; j < calculatedGardenMap[i].size(); j++) {
      if (calculatedGardenMap[i][j] == ' ') {
        result += processPosition(input, i, j);
      }
    }
  }
  return result;
}

unsigned long long
GardenGroups::processPosition(const std::vector<std::string> &input, int line,
                              int row) {
  auto sign = input[line][row];
  std::set<std::pair<int, int>> nextFields{{line, row}};
  unsigned long long size{0};
  std::map<SidesDirection, std::vector<std::pair<int, int>>>
      sidesDirectionWithPosition{};
  while (not nextFields.empty()) {
    auto position = nextFields.extract(nextFields.cbegin()).value();
    calculatedGardenMap[position.first][position.second] = sign;
    size++;
    if (isFenceUp(input, sign, position)) {
      sidesDirectionWithPosition[SidesDirection::up].emplace_back(position);
    } else if (input[position.first - 1][position.second] == sign and
               calculatedGardenMap[position.first - 1][position.second] ==
                   ' ') {
      nextFields.insert({position.first - 1, position.second});
    }

    if (isFenceDown(input, sign, position)) {
      sidesDirectionWithPosition[SidesDirection::down].emplace_back(position);
    } else if (input[position.first + 1][position.second] == sign and
               calculatedGardenMap[position.first + 1][position.second] ==
                   ' ') {
      nextFields.insert({position.first + 1, position.second});
    }

    if (isFenceRight(input, sign, position)) {
      sidesDirectionWithPosition[SidesDirection::right].emplace_back(position);
    } else if (input[position.first][position.second + 1] == sign and
               calculatedGardenMap[position.first][position.second + 1] ==
                   ' ') {
      nextFields.insert({position.first, position.second + 1});
    }

    if (isFenceLeft(input, sign, position)) {
      sidesDirectionWithPosition[SidesDirection::left].emplace_back(position);
    } else if (input[position.first][position.second - 1] == sign and
               calculatedGardenMap[position.first][position.second - 1] ==
                   ' ') {
      nextFields.insert({position.first, position.second - 1});
    }
  }
  unsigned long long sides{0};
  sides +=
      calculateSidesInRows(sidesDirectionWithPosition[SidesDirection::left]);
  sides +=
      calculateSidesInRows(sidesDirectionWithPosition[SidesDirection::right]);
  sides +=
      calculateSidesInLines(sidesDirectionWithPosition[SidesDirection::up]);
  sides +=
      calculateSidesInLines(sidesDirectionWithPosition[SidesDirection::down]);
  return sides * size;
}
