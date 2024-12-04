#include "MullItOver.hpp"
#include "Utils/Parsers.hpp"

namespace {

std::vector<unsigned long long> getMatchedLines(std::string line,
                                                bool &isEnabled) {
  std::vector<unsigned long long> result{};
  auto endPosition{0};
  auto startPosition{0};
  do {
    auto nextEnabler = line.find("do()");
    auto nextDisabler = line.find("don't()");
    startPosition = line.find("mul(");
    if (nextEnabler != std::string::npos and startPosition > nextEnabler and
        (nextDisabler == std::string::npos or nextEnabler < nextDisabler)) {
      isEnabled = true;
      line.erase(0, nextEnabler + 4);
      continue;
    } else if (nextDisabler != std::string::npos and
               startPosition > nextDisabler and
               (nextEnabler == std::string::npos or
                nextEnabler > nextDisabler)) {
      isEnabled = false;
      line.erase(0, nextDisabler + 7);
      continue;
    }
    if (endPosition = line.find_first_of(")", startPosition);
        startPosition != std::string::npos and
        endPosition != std::string::npos) {
      startPosition += 4;
    } else {
      break;
    }
    if (startPosition != std::string::npos and
        endPosition != std::string::npos) {
      auto coma = line.find_first_not_of(parsers::digits, startPosition);
      if (line[coma] == ',' and coma > startPosition and
          coma + 1 < endPosition and
          endPosition == line.find_first_not_of(parsers::digits, coma + 1)) {

        auto firstNumber =
            std::stoul(line.substr(startPosition, coma - startPosition));
        auto secondNumber =
            std::stoul(line.substr(coma + 1, endPosition - coma - 1));
        if (firstNumber <= 999 and secondNumber <= 999 and isEnabled) {
          result.push_back(firstNumber * secondNumber);
        }
        startPosition = endPosition;
      }
      line.erase(0, startPosition);
    }
  } while (endPosition != std::string::npos);
  return result;
}

std::vector<unsigned long long>
getAllMultipliedFromStrings(const std::vector<std::string> &input) {
  std::vector<unsigned long long> result{};
  bool isEnabled{true};
  for (const auto &line : input) {
    auto fromLine = getMatchedLines(line, isEnabled);
    result.reserve(result.size() + fromLine.size());
    result.insert(result.end(), fromLine.begin(), fromLine.end());
  }
  return result;
}
} // namespace

unsigned long long MullItOver::run(const std::vector<std::string> &input) {
  auto multiplied = getAllMultipliedFromStrings(input);
  unsigned long long result{0};
  for (const auto &number : multiplied) {
    result += number;
  }
  return result;
}
