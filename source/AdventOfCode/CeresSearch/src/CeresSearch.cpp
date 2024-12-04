#include "CeresSearch.hpp"
#include <algorithm>
#include <string>

namespace {
const auto normalXmas{"XMAS"};
const auto invertedXmas{"SAMX"};

unsigned int countXmasInLines(const std::vector<std::string> &lines) {
  unsigned int result{0};
  for (auto line : lines) {
    int normalStart{0};
    int invertedStart{0};
    do {
      normalStart = line.find(normalXmas);
      invertedStart = line.find(invertedXmas);
      if (normalStart != std::string::npos and
          (invertedStart == std::string::npos or invertedStart > normalStart)) {
        result++;
        line.erase(0, normalStart + 3);
      } else if (invertedStart != std::string::npos and
                 (normalStart == std::string::npos or
                  normalStart > invertedStart)) {
        result++;
        line.erase(0, invertedStart + 3);
      }
    } while (normalStart != std::string::npos or
             invertedStart != std::string::npos);
  }
  return result;
}

std::vector<std::string> makeTranspose(const std::vector<std::string> &input) {
  std::vector<std::string> transposed{input[0].size(), ""};
  for (const auto &line : input) {
    for (int i = 0; i < line.size(); i++) {
      transposed[i].push_back(line[i]);
    }
  }
  return transposed;
}

std::vector<std::string>
makeDiagonalLeft(const std::vector<std::string> &input) {
  std::vector<std::string> diagonalLeft{input.size() + input[0].size() - 1, ""};
  auto diagonalReverseIterator = diagonalLeft.rbegin();
  std::for_each(input.rbegin(), input.rend(),
                [&diagonalReverseIterator](const auto &line) {
                  auto forOneLineIterator = diagonalReverseIterator++;
                  for (int i = line.size() - 1; i >= 0; i--) {
                    forOneLineIterator++->push_back(line[i]);
                  };
                });
  return diagonalLeft;
}

std::vector<std::string>
makeDiagonalRight(const std::vector<std::string> &input) {
  std::vector<std::string> diagonalRight{input.size() + input[0].size() - 1,
                                         ""};
  auto diagonalIterator = diagonalRight.begin();
  std::for_each(input.begin(), input.end(),
                [&diagonalIterator](const auto &line) {
                  auto forOneLineIterator = diagonalIterator++;
                  for (int i = line.size() - 1; i >= 0; i--) {
                    forOneLineIterator++->push_back(line[i]);
                  };
                });
  return diagonalRight;
}

bool checkX_Mas(std::pair<int, int> position,
                const std::vector<std::string> &table) {
  if (table[position.first][position.second] == 'A') {
    if ((table[position.first - 1][position.second - 1] == 'M' and
         table[position.first + 1][position.second + 1] == 'S') or
        (table[position.first - 1][position.second - 1] == 'S' and
         table[position.first + 1][position.second + 1] == 'M')) {
      if ((table[position.first - 1][position.second + 1] == 'M' and
           table[position.first + 1][position.second - 1] == 'S') or
          (table[position.first - 1][position.second + 1] == 'S' and
           table[position.first + 1][position.second - 1] == 'M')) {
        return true;
      }
    }
  }
  return false;
}
} // namespace

unsigned int CeresSearch::run(const std::vector<std::string> &input) {
  unsigned int result{0};
  for (int x = 1; x < input.size() - 1; x++) {
    for (int y = 1; y < input[x].size() - 1; y++) {
      result += checkX_Mas({x, y}, input) ? 1 : 0;
    }
  }
  return result;
}
