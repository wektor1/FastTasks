#include "BridgeRepair.hpp"
#include "Utils/Parsers.hpp"
#include <exception>

unsigned long long BridgeRepair::run(const std::vector<std::string> &input) {
  values.reserve(input.size());
  for (const auto &line : input) {
    values.push_back(parsers::parseNumbersFromLine(line));
  }

  return calculateTotalCalibrationResult();
}

unsigned long long BridgeRepair::calculateTotalCalibrationResult() {
  unsigned long long result{0};
  for (const auto &equation : values) {
    result += getResultFromCorrectEquation(equation);
  }
  return result;
}

unsigned long long BridgeRepair::getResultFromCorrectEquation(
    const std::vector<unsigned long long> &equation) {
  auto result{equation[0]};
  std::vector<unsigned long long> restOfEquation(equation.begin() + 1,
                                                 equation.end());
  return addAndGoFurther(restOfEquation, result) or
                 multiplyAndGoFurther(restOfEquation, result) or
                 concatentAndGoFurther(restOfEquation, result)
             ? result
             : 0;
}

bool BridgeRepair::addAndGoFurther(std::vector<unsigned long long> equation,
                                   unsigned long long result) {
  try {
    equation[1] += equation[0];
  } catch (std::exception) {
    return false;
  }
  equation.erase(equation.begin());
  return goFurther(std::move(equation), result);
}

bool BridgeRepair::multiplyAndGoFurther(
    std::vector<unsigned long long> equation, unsigned long long result) {
  try {
    equation[1] *= equation[0];
  } catch (std::exception) {
    return false;
  }
  equation.erase(equation.begin());
  return goFurther(std::move(equation), result);
}

bool BridgeRepair::concatentAndGoFurther(
    std::vector<unsigned long long> equation, unsigned long long result) {
  unsigned long long firstNumberMover{10};
  while (equation[1] % firstNumberMover != equation[1]) {
    firstNumberMover *= 10;
  }
  try {
    equation[1] += equation[0] * firstNumberMover;
  } catch (std::exception) {
    return false;
  }
  equation.erase(equation.begin());
  return goFurther(std::move(equation), result);
}

bool BridgeRepair::goFurther(std::vector<unsigned long long> equation,
                             unsigned long long result) {
  if (equation[0] > result) {
    return false;
  }
  if (equation.size() > 1) {

    return addAndGoFurther(equation, result) or
           multiplyAndGoFurther(equation, result) or
           concatentAndGoFurther(equation, result);
  }
  return result == equation[0];
}
