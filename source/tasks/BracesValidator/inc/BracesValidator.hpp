#pragma once
#include <string>

class BracesValidator {
public:
  BracesValidator(std::string input);
  bool isValid();

private:
  std::string textToValidate;
};
