#include "PrintQueue.hpp"
#include "Utils/Parsers.hpp"
#include <string>

unsigned long PrintQueue::run(const std::vector<std::string> &input) {
  processInput(input);
  return getResultFromUpdates();
}

void PrintQueue::processInput(const std::vector<std::string> &input) {
  bool startParsingUpdates{false};
  for (const auto &line : input) {
    if (std::string::npos == line.find_first_of(parsers::digits)) {
      startParsingUpdates = true;
      continue;
    }
    if (startParsingUpdates) {
      updates.push_back(parsers::parseNumbersFromLine(line));
    } else {
      auto rule = parsers::parseNumbersFromLine(line);
      pagesAfterKeyPage[rule[0]].insert(rule[1]);
    }
  }
}

unsigned long PrintQueue::getResultFromUpdates() {
  unsigned long result{0};
  for (const auto &update : updates) {
    result += getResultIfCorrect(update);
  }
  return result;
}

unsigned long PrintQueue::getResultIfCorrect(std::vector<unsigned long> line) {
  bool isCorrect{true};
  for (int i = 0; i < line.size(); i++) {
    int j = i - 1;
    while (j >= 0) {
      if (pagesAfterKeyPage[line[i]].contains(line[j])) {
        isCorrect = false;
        line.insert(line.begin() + i + 1, line[j]);
        line.erase(line.begin() + j);
        i--;
      }
      j--;
    }
  }
  return isCorrect ? 0 : line[(line.size() - 1) / 2];
}
