#include "HistorianHysteria.hpp"
#include "Utils/Parsers.hpp"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <string>

unsigned long HistorianHysteria::run(const std::vector<std::string> &input) {
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

void HistorianHysteria::copyNumbers(const std::vector<std::string> &input) {
  leftIds.reserve(input.size());
  rightIds.reserve(input.size());
  for (const auto line : input) {
    auto parsedNumbers = parsers::parseNumbersFromLine(line);
    leftIds.push_back(std::move(parsedNumbers[0]));
    rightIds.push_back(std::move(parsedNumbers[1]));
  }
}
