#include "PlutonianPebbles.hpp"
#include "Utils/Parsers.hpp"
#include <map>
#include <string>
#include <vector>

namespace {
void howManyRocksFromThisOne(
    unsigned long long rockNumber, unsigned long long count,
    std::map<unsigned long long, unsigned long long> &pebblesCount) {
  if (rockNumber == 0) {
    pebblesCount[1] += count;
    return;
  }
  if (auto number = std::to_string(rockNumber); number.size() % 2 == 0) {

    auto rockOne = std::stoull(number.substr(0, number.size() / 2));
    auto rockTwo =
        std::stoull(number.substr(number.size() / 2, number.size() / 2));
    pebblesCount[rockOne] += count;
    pebblesCount[rockTwo] += count;
    return;
  }
  pebblesCount[rockNumber * 2024] += count;
}
} // namespace

unsigned long long
PlutonianPebbles::run(const std::vector<std::string> &input) {
  auto pebbles = parsers::parseNumbersFromLine(input[0]);
  std::map<unsigned long long, unsigned long long> allPebblesCount{};
  for (auto rock : pebbles) {
    allPebblesCount[rock] = 1;
  }
  for (int i = 0; i < 75; i++) {
    decltype(allPebblesCount) thisIterPebbles{};
    thisIterPebbles.swap(allPebblesCount);
    for (auto &[rock, count] : thisIterPebbles) {
      howManyRocksFromThisOne(rock, count, allPebblesCount);
    }
  }
  unsigned long long result{0};
  for (auto [_, count] : allPebblesCount) {
    result += count;
  }
  return result;
}
