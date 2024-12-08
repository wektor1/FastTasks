#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>
class ResonantCollinearity {
public:
  unsigned int run(const std::vector<std::string> &);
  void collectAllNodes(const std::vector<std::string> &);
  void createAntinodes(const std::vector<std::string> &);
  void createAntinodesForAntennaType(
      const std::vector<std::string> &,
      const std::pair<const char, std::vector<std::pair<int, int>>> &);
  void calculateAntennasForPair(const std::vector<std::string> &,
                                const std::vector<std::pair<int, int>> &, int,
                                int);
  std::pair<int, int>
  calculateDistance(const std::vector<std::pair<int, int>> &, int, int);

private:
  std::pair<int, int> createAntinode(const std::pair<int, int> &,
                                     const std::pair<int, int> &,
                                     const std::pair<int, int> &);
  void resonantHarmonicsAntinodes(const std::pair<int, int> &,
                                  const std::pair<int, int> &,
                                  const std::pair<int, int> &, int, int);

  std::map<char, std::vector<std::pair<int, int>>> nodes;
  std::set<std::pair<int, int>> antinodesLocations;
};
