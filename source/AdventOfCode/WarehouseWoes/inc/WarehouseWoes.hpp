#pragma once

#include <string>
#include <vector>
class WarehouseWoes {
public:
  unsigned long long run(const std::vector<std::string> &);

private:
  bool move(char, std::pair<int, int>, std::vector<std::pair<int, int>> &);
  unsigned long long calculateResultPart1();
  unsigned long long calculateResultPart2();

  std::vector<std::vector<char>> map;
  std::vector<char> operations;
  std::pair<int, int> startPos;
};