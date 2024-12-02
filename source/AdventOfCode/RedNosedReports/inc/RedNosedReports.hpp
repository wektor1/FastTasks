#pragma once

#include <string>
#include <vector>

class RedNosedReports {
public:
  unsigned long run(const std::vector<std::string> &);

private:
  std::vector<int> getDifferences(const std::vector<unsigned long> &);
  bool differenceValidator(std::vector<int>);
};