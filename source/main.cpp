#include "RedNosedReports.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
  auto cwd = std::filesystem::current_path();
  std::ifstream file(cwd / "../../input");
  std::vector<std::string> input;
  std::string temp;
  while (std::getline(file, temp)) {
    input.push_back(temp);
  }
  RedNosedReports day2{};
  std::cout << "Result is: " << day2.run(input);
  return 0;
}