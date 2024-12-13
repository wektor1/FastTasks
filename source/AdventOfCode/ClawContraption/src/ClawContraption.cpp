#include "ClawContraption.hpp"
#include "Utils/Parsers.hpp"
#include <utility>

unsigned long long ClawContraption::run(const std::vector<std::string> &input) {
  for (int i = 0; i < input.size(); i++) {
    Machine temp{};
    auto line = parsers::parseNumbersFromLine(input[i++]);
    temp.buttonA = {line[0], line[1]};
    line = parsers::parseNumbersFromLine(input[i++]);
    temp.buttonB = {line[0], line[1]};
    line = parsers::parseNumbersFromLine(input[i++]);
    temp.prize = {line[0] + 10000000000000, line[1] + 10000000000000};
    machines.push_back(std::move(temp));
  }

  unsigned long long result{0};
  for (const auto &machine : machines) {
    result += getTokensIfPossibleWin(machine);
  }

  return result;
}

unsigned long long
ClawContraption::getResult(std::pair<long double, long double> aButton,
                           std::pair<long double, long double> bButton,
                           std::pair<long double, long double> prize,
                           std::pair<long double, long double> tokensCost) {
  long long a;
  long long b;
  a = (prize.first * bButton.second - prize.second * bButton.first) /
      (aButton.first * bButton.second - aButton.second * bButton.first);
  b = (aButton.first * prize.second - aButton.second * prize.first) /
      (aButton.first * bButton.second - aButton.second * bButton.first);

  if (a * aButton.first + b * bButton.first == prize.first and
      a * aButton.second + b * bButton.second == prize.second and a >= 0 and
      b >= 0) {
    return tokensCost.first * a + tokensCost.second * b;
  } else {
    return 0;
  }
}

unsigned long long
ClawContraption::getTokensIfPossibleWin(const Machine &machine) {
  return getResult(machine.buttonA, machine.buttonB, machine.prize, {3, 1});
}