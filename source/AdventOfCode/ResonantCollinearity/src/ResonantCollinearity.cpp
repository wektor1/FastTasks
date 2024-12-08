#include "ResonantCollinearity.hpp"
#include <algorithm>

namespace {
bool isAntinodeValid(const std::pair<int, int> &antinode, int firstSize,
                     int secondSize) {
  return antinode.first >= 0 and antinode.first < firstSize and
         antinode.second >= 0 and antinode.second < secondSize;
}
} // namespace

unsigned int ResonantCollinearity::run(const std::vector<std::string> &input) {
  collectAllNodes(input);
  createAntinodes(input);
  return antinodesLocations.size();
}

void ResonantCollinearity::collectAllNodes(
    const std::vector<std::string> &input) {
  int lineIdx{0};
  for (const auto &line : input) {
    int posIdx{0};
    for (auto node : line) {
      if (node != '.') {
        nodes[node].push_back({lineIdx, posIdx});
      }
      posIdx++;
    }
    lineIdx++;
  }
}

void ResonantCollinearity::createAntinodes(
    const std::vector<std::string> &input) {
  std::ranges::for_each(nodes, [this, &input](auto node) {
    createAntinodesForAntennaType(input, node);
  });
}

void ResonantCollinearity::createAntinodesForAntennaType(
    const std::vector<std::string> &input,
    const std::pair<const char, std::vector<std::pair<int, int>>> &node) {
  auto [_, positionsList] = node;
  for (int first = 0; first < positionsList.size(); first++) {
    for (int nextNodeIt = 1; nextNodeIt + first < positionsList.size();
         nextNodeIt++) {
      calculateAntennasForPair(input, positionsList, first, nextNodeIt);
    }
  }
}

void ResonantCollinearity::calculateAntennasForPair(
    const std::vector<std::string> &input,
    const std::vector<std::pair<int, int>> &positionsList, int first,
    int nextNodeIt) {
  antinodesLocations.insert(positionsList[first]);
  antinodesLocations.insert(positionsList[first + nextNodeIt]);
  std::pair<int, int> distance =
      calculateDistance(positionsList, first, nextNodeIt);
  resonantHarmonicsAntinodes(distance, positionsList[first],
                             positionsList[first + nextNodeIt], input.size(),
                             input[0].size());
  resonantHarmonicsAntinodes(distance, positionsList[first + nextNodeIt],
                             positionsList[first], input.size(),
                             input[0].size());
}

std::pair<int, int> ResonantCollinearity::calculateDistance(
    const std::vector<std::pair<int, int>> &positionsList, int first,
    int nextNodeIt) {
  return {
      abs(positionsList[first].first - positionsList[first + nextNodeIt].first),
      abs(positionsList[first].second -
          positionsList[first + nextNodeIt].second)};
}

std::pair<int, int>
ResonantCollinearity::createAntinode(const std::pair<int, int> &distance,
                                     const std::pair<int, int> &first,
                                     const std::pair<int, int> &second) {
  std::pair<int, int> antinode{first.first, first.second};
  antinode.first +=
      first.first > second.first ? distance.first : -distance.first;
  antinode.second +=
      first.second > second.second ? distance.second : -distance.second;
  return antinode;
}

void ResonantCollinearity::resonantHarmonicsAntinodes(
    const std::pair<int, int> &distance, const std::pair<int, int> &firstNode,
    const std::pair<int, int> &secondNode, int firstSize, int secondSize) {
  std::pair<int, int> antinode{createAntinode(distance, firstNode, secondNode)};

  if (isAntinodeValid(antinode, firstSize, secondSize)) {
    antinodesLocations.insert(antinode);
    auto previous = firstNode;
    auto current = antinode;
    antinode = createAntinode(distance, current, previous);
    while (isAntinodeValid(antinode, firstSize, secondSize)) {
      antinodesLocations.insert(antinode);
      previous = current;
      current = antinode;
      antinode = createAntinode(distance, current, previous);
    }
  }
}