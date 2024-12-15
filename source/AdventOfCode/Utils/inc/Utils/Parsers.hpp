#pragma once

#include <string>
#include <vector>

namespace parsers {
constexpr auto digits{"0123456789"};
constexpr auto negativeDigits{"-0123456789"};

std::vector<unsigned long long> parseNumbersFromLine(std::string line);
std::vector<int> parseNumbersFromLineWithNegative(std::string line);
} // namespace parsers