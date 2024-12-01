#pragma once
#include <stack>
#include <string>

enum class Enclosure { parentheses, brackets, braces };

class BracesValidator {
public:
  BracesValidator(const std::string &input);
  bool isValid();

private:
  std::string textToValidate;
  std::stack<Enclosure> enclosures;
};
