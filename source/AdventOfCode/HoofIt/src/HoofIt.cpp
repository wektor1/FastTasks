#include "HoofIt.hpp"
#include <set>
#include <utility>

namespace {
void saveNewTrailOfInterest(
    const std::vector<std::string> &input, char point,
    std::set<std::vector<std::pair<int, int>>> &newTrailsOfInterest,
    const std::vector<std::pair<int, int>> &trailOfInterest,
    std::pair<int, int> newPoint) {
  if (input[newPoint.first][newPoint.second] == point) {
    auto tempTrail = trailOfInterest;
    tempTrail.push_back(newPoint);
    newTrailsOfInterest.insert(std::move(tempTrail));
  }
}
} // namespace

int HoofIt::run(const std::vector<std::string> &input) {
  for (int line = 0; line < input.size(); line++) {
    for (int row = 0; row < input[0].size(); row++) {
      if (input[line][row] == '0') {
        saveRatingForTrail({line, row}, input);
      }
    }
  }
  return result;
}

void HoofIt::saveRatingForTrail(std::pair<int, int> start,
                                const std::vector<std::string> &input) {
  std::set<std::vector<std::pair<int, int>>> trailsOfInterest{{start}};
  for (char point = '1'; point <= '9'; point++) {
    decltype(trailsOfInterest) newTrailsOfInterest{};
    for (const auto &trailOfInterest : trailsOfInterest) {
      auto pointOfInterest = trailOfInterest.back();
      if (decltype(start) newPoint = {pointOfInterest.first,
                                      pointOfInterest.second - 1};
          newPoint.second >= 0) {
        saveNewTrailOfInterest(input, point, newTrailsOfInterest,
                               trailOfInterest, newPoint);
      }
      if (decltype(start) newPoint = {pointOfInterest.first - 1,
                                      pointOfInterest.second};
          newPoint.first >= 0) {
        saveNewTrailOfInterest(input, point, newTrailsOfInterest,
                               trailOfInterest, newPoint);
      }
      if (decltype(start) newPoint = {pointOfInterest.first + 1,
                                      pointOfInterest.second};
          newPoint.first < input.size()) {
        saveNewTrailOfInterest(input, point, newTrailsOfInterest,
                               trailOfInterest, newPoint);
      }
      if (decltype(start) newPoint = {pointOfInterest.first,
                                      pointOfInterest.second + 1};
          newPoint.second < input[0].size()) {
        saveNewTrailOfInterest(input, point, newTrailsOfInterest,
                               trailOfInterest, newPoint);
      }
    }
    trailsOfInterest = std::move(newTrailsOfInterest);
  }
  result += trailsOfInterest.size();
}
