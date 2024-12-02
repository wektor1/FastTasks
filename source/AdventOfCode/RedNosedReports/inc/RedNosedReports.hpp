#pragma once

#include <functional>
#include <string>
#include <vector>

class RedNosedReports {
public:
  unsigned long run(const std::vector<std::string> &);

private:
  std::vector<int> getDifferences(const std::vector<unsigned long> &);
  bool differenceValidator(const std::vector<int> &);
  void recheckOnMistake(std::function<bool(int)> isMistake,
                        const std::vector<int> &differences,
                        const std::vector<unsigned long> &report,
                        unsigned long &result);
};