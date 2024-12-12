#pragma once

#include <string>
#include <vector>

class GardenGroups {
public:
  unsigned long long run(const std::vector<std::string> &);

private:
  unsigned long long processPosition(const std::vector<std::string> &, int,
                                     int);

  std::vector<std::vector<char>> calculatedGardenMap;
};