#include "HistorianHysteria.hpp"
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
  HistorianHysteria day1{};
  std::cout << "Result is: " << day1.run(input);
  return 0;
}