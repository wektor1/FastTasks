#pragma once

#include <string>
#include <vector>

class Machine {
public:
  std::pair<long double, long double> buttonA;
  std::pair<long double, long double> buttonB;
  std::pair<long double, long double> prize;
};

class ClawContraption {
public:
  unsigned long long run(const std::vector<std::string> &);

private:
  unsigned long long getResult(std::pair<long double, long double>,
                               std::pair<long double, long double>,
                               std::pair<long double, long double>,
                               std::pair<long double, long double>);
  unsigned long long getTokensIfPossibleWin(const Machine &);
  std::vector<Machine> machines;
};