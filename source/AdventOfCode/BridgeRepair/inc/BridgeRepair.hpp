#pragma once

#include <string>
#include <vector>
class BridgeRepair {
public:
  unsigned long long run(const std::vector<std::string> &);

private:
  unsigned long long calculateTotalCalibrationResult();
  unsigned long long
  getResultFromCorrectEquation(const std::vector<unsigned long long> &);

  bool addAndGoFurther(std::vector<unsigned long long>, unsigned long long);
  bool multiplyAndGoFurther(std::vector<unsigned long long>,
                            unsigned long long);
  bool concatentAndGoFurther(std::vector<unsigned long long>,
                             unsigned long long);
  bool goFurther(std::vector<unsigned long long>, unsigned long long);

  std::vector<std::vector<unsigned long long>> values;
};