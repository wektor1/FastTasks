#pragma once

#include <string>
#include <vector>
class WarehouseWoes {
public:
  unsigned long long run(const std::vector<std::string> &);

private:
  void move(char, int = 1);
  unsigned long long calculateResultPart1();

  std::vector<std::vector<char>> map;
  std::vector<char> operations;
  std::pair<int, int> startPos;
};