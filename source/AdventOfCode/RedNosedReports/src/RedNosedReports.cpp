#include "RedNosedReports.hpp"
#include "Utils/Parsers.hpp"
#include <algorithm>

namespace {
auto higherOrLowerPositive = [](auto difference) {
  return difference > 3 or difference < 1;
};

auto higherOrLowerNegative = [](auto difference) {
  return difference > -1 or difference < -3;
};
} // namespace

unsigned long RedNosedReports::run(const std::vector<std::string> &input) {
  unsigned long output{0};
  for (const auto &line : input) {
    const auto report{parsers::parseNumbersFromLine(line)};
    auto differences{getDifferences(report)};
    if (differenceValidator(differences)) {
      output++;
    } else {
      const auto mistakesPositive =
          std::ranges::count_if(differences, higherOrLowerPositive);
      const auto mistakesNegative =
          std::ranges::count_if(differences, higherOrLowerNegative);
      if (mistakesPositive <= 2) {
        recheckOnMistake(higherOrLowerPositive, differences, report, output);
      } else if (mistakesNegative <= 2) {
        recheckOnMistake(higherOrLowerNegative, differences, report, output);
      }
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

bool RedNosedReports::differenceValidator(const std::vector<int> &differences) {
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

void RedNosedReports::recheckOnMistake(std::function<bool(int)> isMistake,
                                       const std::vector<int> &differences,
                                       const std::vector<unsigned long> &report,
                                       unsigned long &result) {
  for (int i = 0; i < differences.size(); i++) {
    if (isMistake(differences[i])) {
      auto reportRemoveBefore = report;
      reportRemoveBefore.erase(reportRemoveBefore.begin() + i);
      auto differencesBefore{getDifferences(reportRemoveBefore)};
      auto reportRemoveAfter = report;
      reportRemoveAfter.erase(reportRemoveAfter.begin() + i + 1);
      auto differencesAfter{getDifferences(reportRemoveAfter)};
      if (differenceValidator(differencesBefore) or
          differenceValidator(differencesAfter)) {
        result++;
      }
      break;
    }
  }
}
