#pragma once

#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

enum class MapSign { wall, track };
enum class Direction { north, south, east, west };

class ReindeerMaze {
public:
  using Position = std::pair<int, int>;
  using Crossroads = std::stack<std::pair<Position, std::set<Direction>>>;
  struct TrackCrawler {
    std::vector<Position> track;
    Direction direction;
    int id;
  };

  unsigned long long run(const std::vector<std::string> &);

private:
  void saveMap(const std::vector<std::string> &);
  unsigned long long getBestSpots();
  void continueTrack(unsigned long long, TrackCrawler);
  std::vector<Direction> getDirectionsCrossroad(const Position &, Direction);
  unsigned long long countScore(const std::vector<Position> &);

  Position startPosition;
  Position endPosition;
  std::map<unsigned long long, std::vector<TrackCrawler>> tracks{};
  std::vector<std::vector<MapSign>> map{};
  std::set<Position> alreadyVisited;
};