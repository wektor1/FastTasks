#include "BracesValidator.hpp"
#include <string>

Enclosure signToEnclosureMapper(const char sign) {
  switch (sign) {
  case '(':
  case ')':
    return Enclosure::parentheses;
  case '[':
  case ']':
    return Enclosure::brackets;
  case '{':
  case '}':
  default:
    return Enclosure::braces;
  }
}

BracesValidator::BracesValidator(const std::string &input)
    : textToValidate{input} {}

bool BracesValidator::isValid() {
  for (const auto &singleSign : textToValidate) {
    switch (singleSign) {
    case '(':
    case '[':
    case '{':
      enclosures.push(signToEnclosureMapper(singleSign));
      break;
    case ')':
    case ']':
    case '}':
      if (enclosures.empty() or
          enclosures.top() != signToEnclosureMapper(singleSign)) {
        return false;
      }
      enclosures.pop();
      break;
    default:
      continue;
    }
  }
  return enclosures.empty();
}