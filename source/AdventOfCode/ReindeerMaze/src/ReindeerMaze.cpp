#include "ReindeerMaze.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

namespace {

Direction getDirection(const ReindeerMaze::Position &first,
                       const ReindeerMaze::Position &second) {
  if (first.first != second.first) {
    return first.first > second.first ? Direction::north : Direction::south;
  }
  if (first.second != second.second) {
    return first.second > second.second ? Direction::west : Direction::east;
  }
  return Direction::north;
}
} // namespace

unsigned long long ReindeerMaze::run(const std::vector<std::string> &input) {
  saveMap(input);
  return getBestSpots();
}

void ReindeerMaze::saveMap(const std::vector<std::string> &input) {
  map.reserve(input.size());
  for (int line = 0; line < input.size(); line++) {
    std::vector<MapSign> tempLine;
    tempLine.reserve(input[line].size());
    for (int row = 0; row < input[line].size(); row++) {
      auto sign = input[line][row];
      switch (sign) {
      case '#':
        tempLine.push_back(MapSign::wall);
        break;
      case '.':
        tempLine.push_back(MapSign::track);
        break;
      case 'E':
        endPosition = {line, row};
        tempLine.push_back(MapSign::track);
        break;
      case 'S':
        startPosition = {line, row};
        tempLine.push_back(MapSign::track);
        break;
      default:
        continue;
      }
    }
    map.emplace_back(std::move(tempLine));
  }
}

unsigned long long ReindeerMaze::getBestSpots() {
  Direction moveDirection{Direction::east};
  tracks[0].emplace_back(std::vector<Position>{startPosition}, Direction::east);
  tracks[0].emplace_back(std::vector<Position>{startPosition},
                         Direction::north);
  do {
    auto firstNode = tracks.extract(tracks.begin());
    auto crawlers{std::move(firstNode.mapped())};
    for (int i = 0; i < crawlers.size(); i++) {
      continueTrack(firstNode.key(), std::move(crawlers[i]));
    }
  } while (
      std::ranges::none_of(tracks.begin()->second, [this](const auto &crawler) {
        return crawler.track.back() == endPosition;
      }));
  auto bestScore = tracks.begin()->first;
  std::set<Position> bestSpots{};
  for (const auto &crawler : tracks.begin()->second) {
    if (crawler.track.back() == endPosition) {
      bestSpots.insert(crawler.track.begin(), crawler.track.end());
    }
  }

  return bestSpots.size();
}

std::vector<Direction>
ReindeerMaze::getDirectionsCrossroad(const Position &position, Direction dir) {
  std::vector<Direction> directions{};
  if (map[position.first - 1][position.second] == MapSign::track and
      dir != Direction::south) {
    directions.push_back(Direction::north);
  }
  if (map[position.first][position.second - 1] == MapSign::track and
      dir != Direction::east) {
    directions.push_back(Direction::west);
  }
  if (map[position.first + 1][position.second] == MapSign::track and
      dir != Direction::north) {
    directions.push_back(Direction::south);
  }
  if (map[position.first][position.second + 1] == MapSign::track and
      dir != Direction::west) {
    directions.push_back(Direction::east);
  }
  return directions;
}

void ReindeerMaze::continueTrack(unsigned long long score,
                                 TrackCrawler crawler) {
  std::function<void(Position &)> goForward;
  switch (crawler.direction) {
  case Direction::north:
    goForward = [](Position &position) { position.first--; };
    break;
  case Direction::south:
    goForward = [](Position &position) { position.first++; };
    break;
  case Direction::east:
    goForward = [](Position &position) { position.second++; };
    break;
  case Direction::west:
    goForward = [](Position &position) { position.second--; };
    break;
  default:
    return;
  }
  auto nextPosition = crawler.track.back();
  goForward(nextPosition);
  if (map[nextPosition.first][nextPosition.second] == MapSign::track and
      not std::ranges::contains(crawler.track, nextPosition)) {
    crawler.track.push_back(nextPosition);
    auto score = countScore(crawler.track);
    if (auto dirs = getDirectionsCrossroad(nextPosition, crawler.direction);
        not(dirs.empty() or alreadyVisited.contains(nextPosition))) {
      alreadyVisited.insert(nextPosition);
      crawler.direction = dirs.back();
      dirs.pop_back();
      for (const auto &dir : dirs) {
        tracks[score].emplace_back(crawler.track, dir);
      }
      tracks[score].push_back(std::move(crawler));
    } else {
      if (dirs.size() == 1) {
        for (auto &trackNode : tracks) {
          auto iter = std::find_if(
              trackNode.second.begin(), trackNode.second.end(),
              [nextPosition](const auto &trackCrawler) {
                return std::ranges::contains(trackCrawler.track, nextPosition);
              });
          if (iter != trackNode.second.end()) {
            std::vector<Position> temp{};
            std::copy(iter->track.begin(),
                      std::ranges::find(iter->track, nextPosition) + 1,
                      std::back_inserter(temp));
            auto tempScore = countScore(temp);
            if (tempScore < score) {
              return;
            } else if (score < tempScore) {
              trackNode.second.erase(iter);
            }
          }
        }
        crawler.direction = dirs.back();
        tracks[score].push_back(std::move(crawler));
        return;
      }
      if (dirs.size() > 1) {
        crawler.direction = dirs.back();
        dirs.pop_back();
        for (const auto &dir : dirs) {
          tracks[score].emplace_back(crawler.track, dir);
        }
        tracks[score].push_back(std::move(crawler));
      }
    }
    return;
  }
}

unsigned long long
ReindeerMaze::countScore(const std::vector<Position> &track) {
  Direction direction = Direction::east;
  unsigned long long count{0};
  for (int pos = 0; pos < track.size() - 1; pos++) {
    auto tempDir = getDirection(track[pos], track[pos + 1]);
    if (tempDir != direction) {
      count++;
      direction = tempDir;
    }
  }
  return count * 1000 + track.size() - 1;
}
