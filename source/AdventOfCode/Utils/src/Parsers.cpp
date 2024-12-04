#include "Utils/Parsers.hpp"

namespace parsers {

std::vector<unsigned long> parseNumbersFromLine(std::string line) {
  std::vector<unsigned long> result{};
  auto endPosition{0};
  auto startPosition{0};
  do {
    startPosition = line.find_first_of(digits);
    endPosition = line.find_first_not_of(digits, startPosition);
    auto number =
        std::stol(line.substr(startPosition, endPosition - startPosition));
    result.push_back(std::move(number));
    line.erase(startPosition, endPosition + 1);
  } while (endPosition != std::string::npos);

  return result;
}
} // namespace parsers