#include "WarehouseWoes.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
  auto startTimer{std::chrono::high_resolution_clock::now()};
  auto cwd = std::filesystem::current_path();
  std::ifstream file(cwd / "../../input");
  std::vector<std::string> input;
  std::string temp;
  while (std::getline(file, temp)) {
    input.push_back(temp);
  }
  WarehouseWoes adventOvCode{};
  std::cout << "Result is: " << adventOvCode.run(input);
  auto stopTimer{std::chrono::high_resolution_clock::now()};
  auto duration{std::chrono::duration_cast<std::chrono::microseconds>(
      stopTimer - startTimer)};
  std::cout << "\nIt took me: " << duration.count() << " microseconds.";
  return 0;
}