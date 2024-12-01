#include "HistorianHysteria.hpp"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <string>

namespace {
constexpr auto digits{"0123456789"};
}
unsigned long HistorianHysteria::run(std::vector<std::string> input) {
  copyNumbers(input);
  std::sort(leftIds.begin(), leftIds.end());
  std::sort(rightIds.begin(), rightIds.end());

  return calculateRepetitionsSum();
}

unsigned long HistorianHysteria::calculateRepetitionsSum() {
  unsigned long reps{0};
  assert(leftIds.size() == rightIds.size());
  for (const auto &number : leftIds) {
    reps += number * std::ranges::count(rightIds, number);
  }
  return reps;
}

void HistorianHysteria::copyNumbers(std::vector<std::string> input) {
  leftIds.reserve(input.size());
  rightIds.reserve(input.size());
  for (const auto line : input) {
    auto endOfFirstNumber = line.find_first_not_of(digits);
    auto firstNumber = std::stol(line.substr(0, endOfFirstNumber));
    auto secondNumber = std::stol(line.substr(endOfFirstNumber));
    leftIds.push_back(std::move(firstNumber));
    rightIds.push_back(std::move(secondNumber));
  }
}
