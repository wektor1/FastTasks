#include "MullItOver.hpp"
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
  MullItOver adventOvCode{};
  std::cout << "Result is: " << adventOvCode.run(input);
  return 0;
}