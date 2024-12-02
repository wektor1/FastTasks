#pragma once

#include <string>
#include <vector>

class HistorianHysteria {
public:
  unsigned long run(const std::vector<std::string> &);

private:
  unsigned long calculateRepetitionsSum();
  void copyNumbers(const std::vector<std::string> &);
  std::vector<unsigned long> leftIds{};
  std::vector<unsigned long> rightIds{};
};