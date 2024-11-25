#include "BracesValidator.hpp"
#include <iostream>

int main() {
  BracesValidator validator{""};
  std::cout << "Validate string \"\": " << validator.isValid() << std::endl;
  return 0;
}