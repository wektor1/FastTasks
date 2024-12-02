#include "RedNosedReports.hpp"
#include <algorithm>

namespace {
constexpr auto digits{"0123456789"};

std::vector<unsigned long> parseNumbersFromLine(std::string line) {
  std::vector<unsigned long> result{};
  auto endPosition{0};
  auto startPosition{0};
  do {
    endPosition = line.find_first_not_of(digits);
    auto number = std::stol(line.substr(startPosition, endPosition));
    result.push_back(std::move(number));
    line.erase(startPosition, endPosition + 1);
  } while (endPosition != std::string::npos);

  return result;
}

} // namespace

unsigned long RedNosedReports::run(const std::vector<std::string> &input) {
  unsigned long output{0};
  for (const auto &line : input) {
    const auto report{parseNumbersFromLine(line)};
    if (differenceValidator(getDifferences(report))) {
      output++;
    }
  }
  return output;
}

std::vector<int>
RedNosedReports::getDifferences(const std::vector<unsigned long> &report) {
  std::vector<int> result;
  result.reserve(report.size() - 1);
  for (int i = 1; i < report.size(); i++) {
    result.push_back(int(report[i - 1]) - int(report[i]));
  }
  return result;
}

bool RedNosedReports::differenceValidator(std::vector<int> differences) {
  const bool isInRange = std::ranges::all_of(differences, [](auto difference) {
    return (difference >= 1 and difference <= 3) or
           (difference >= -3 and difference <= -1);
  });
  const bool isDescending = std::ranges::all_of(
      differences, [](auto difference) { return difference > 0; });
  const bool isAscending = std::ranges::all_of(
      differences, [](auto difference) { return difference < 0; });

  return isInRange and (isAscending or isDescending);
}
