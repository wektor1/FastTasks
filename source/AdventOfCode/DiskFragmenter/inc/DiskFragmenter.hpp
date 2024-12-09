#pragma once

#include <string>
#include <vector>
class DiskFragmenter {
public:
  unsigned long long run(const std::vector<std::string> &);

private:
  void sameMemoryBlocks(const std::string &);
  void moveAllFileBlock();
  unsigned long long getChecksum();

  std::vector<int> memoryBlocks{};
};
