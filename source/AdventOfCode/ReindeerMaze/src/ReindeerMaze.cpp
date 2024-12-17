#include "ReindeerMaze.hpp"
#include <algorithm>
#include <functional>
#include <iterator>

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
  return getScoreFromBestTrack();
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

unsigned long long ReindeerMaze::getScoreFromBestTrack() {
  Direction moveDirection{Direction::east};
  tracks.emplace_back(std::vector<Position>{startPosition}, 0, Direction::east);
  tracks.emplace_back(std::vector<Position>{startPosition}, 0,
                      Direction::north);
  do {
    tracks.reserve(tracks.size() + 3);
    continueTrack();
    std::ranges::sort(tracks, [](auto first, auto second) {
      return first.score < second.score;
    });
  } while (tracks[0].track.back() != endPosition);
  return tracks[0].score;
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

void ReindeerMaze::continueTrack() {
  std::function<void(Position &)> goForward;
  switch (tracks[0].direction) {
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
  auto nextPosition = tracks[0].track.back();
  goForward(nextPosition);
  if (map[nextPosition.first][nextPosition.second] == MapSign::track and
      not std::ranges::contains(tracks[0].track, nextPosition)) {
    tracks[0].track.push_back(nextPosition);
    tracks[0].score = countScore(tracks[0].track);
    if (auto dirs = getDirectionsCrossroad(nextPosition, tracks[0].direction);
        not(dirs.empty() or alreadyVisited.contains(nextPosition))) {
      alreadyVisited.insert(nextPosition);
      tracks[0].direction = dirs.back();
      dirs.pop_back();
      for (const auto &dir : dirs) {
        tracks.emplace(tracks.begin(), tracks[0].track, tracks[0].score, dir);
      }
    } else {
      if (dirs.size() == 1) {
        auto iter = std::find_if(tracks.rbegin(), tracks.rend(),
                                 [nextPosition](const auto &trackCrawler) {
                                   return std::ranges::contains(
                                       trackCrawler.track, nextPosition);
                                 });
        std::vector<Position> temp{};
        std::copy(iter->track.begin(),
                  std::ranges::find(iter->track, nextPosition) + 1,
                  std::back_inserter(temp));
        if (countScore(temp) < tracks[0].score) {
          tracks.erase(tracks.begin());
        } else {
          tracks[0].direction = dirs.back();
          dirs.pop_back();
          tracks.erase((iter + 1).base());
          for (const auto &dir : dirs) {
            tracks.emplace(tracks.begin(), tracks[0].track, tracks[0].score,
                           dir);
          }
        }
        return;
      }
      if (alreadyVisited.contains(nextPosition) and dirs.size() > 1) {
        tracks[0].direction = dirs.back();
        dirs.pop_back();
        for (const auto &dir : dirs) {
          tracks.emplace(tracks.begin(), tracks[0].track, tracks[0].score, dir);
        }
      } else {
        tracks.erase(tracks.begin());
      }
    }
    return;
  }
  tracks.erase(tracks.begin());
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
