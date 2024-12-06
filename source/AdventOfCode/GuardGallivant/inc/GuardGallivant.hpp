#pragma once

#include <string>
#include <vector>

class GuardGallivant {
public:
  int run(const std::vector<std::string> &);

private:
  std::pair<int, int> findStartPosition();
  void startPatrol(std::pair<int, int>);
  void goUp(std::pair<int, int>);
  void goRight(std::pair<int, int>);
  void goDown(std::pair<int, int>);
  void goLeft(std::pair<int, int>);
  int countRoute();
  bool isLoop(std::pair<int, int>, const char);
  std::pair<int, int> loopUp(std::pair<int, int>);
  std::pair<int, int> loopRight(std::pair<int, int>);
  std::pair<int, int> loopLeft(std::pair<int, int>);
  std::pair<int, int> loopDown(std::pair<int, int>);

  std::vector<std::string> map;
  int possibleLoopTriggers{0};
};
