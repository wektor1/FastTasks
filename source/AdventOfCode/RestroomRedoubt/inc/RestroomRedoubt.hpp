#pragma once

#include <string>
#include <vector>

struct Robot {
  std::pair<int, int> start;
  std::pair<int, int> velocity;
};

class RestroomRedoubt {
public:
  unsigned long long run(const std::vector<std::string> &);

private:
  void moveAllRobotsInTime();
  void moveSecond(Robot &);
  void printRobotsPositions(int);
  unsigned long long getSafetyFactor();
  unsigned long long getFactorFirstQ();
  unsigned long long getFactorSecondQ();
  unsigned long long getFactorThirdQ();
  unsigned long long getFactorFourthQ();

  std::vector<Robot> robots{};
};