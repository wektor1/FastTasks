#pragma once

#include <set>
#include <string>
#include <vector>

class HistorianHysteria {
public:
  unsigned long run(std::vector<std::string>);

private:
  unsigned long calculateDistanceSum();
  void copyNumbers(std::vector<std::string>);
  std::vector<unsigned long> leftIds{};
  std::vector<unsigned long> rightIds{};
};