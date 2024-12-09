#include "DiskFragmenter.hpp"
#include <algorithm>
#include <vector>

unsigned long long DiskFragmenter::run(const std::vector<std::string> &input) {
  sameMemoryBlocks(input[0]);
  moveAllFileBlock();
  return getChecksum();
}

void DiskFragmenter::sameMemoryBlocks(const std::string &singleLine) {
  bool isMemoryBlock{true};
  int blockId{0};
  memoryBlocks.clear();
  for (auto number : singleLine) {
    const int convertedNumber = int(number) - '0';
    memoryBlocks.reserve(memoryBlocks.size() + convertedNumber);
    if (isMemoryBlock) {
      for (int i = 0; i < convertedNumber; i++) {
        memoryBlocks.push_back(blockId);
      }
      isMemoryBlock = false;
      blockId++;
    } else {
      for (int i = 0; i < convertedNumber; i++) {
        memoryBlocks.push_back(-1);
      }
      isMemoryBlock = true;
    }
  }
}

void DiskFragmenter::moveAllFileBlock() {
  auto reverseIter = memoryBlocks.rbegin();
  auto idMoved = *reverseIter;
  while (reverseIter != memoryBlocks.rend()) {
    if (*reverseIter != idMoved) {
      reverseIter++;
      continue;
    }
    auto lowerIdIter =
        std::find_if(reverseIter, memoryBlocks.rend(),
                     [idMoved](auto value) { return value != idMoved; });
    int length = lowerIdIter - reverseIter;
    std::vector<int> gapToFind(length, -1);
    auto firstOfGap = std::search(memoryBlocks.begin(), memoryBlocks.end(),
                                  gapToFind.begin(), gapToFind.end());
    if (firstOfGap != memoryBlocks.end() and
        firstOfGap <= (lowerIdIter + 1).base()) {
      for (int i = 0; i < length; i++) {
        *firstOfGap = *reverseIter;
        firstOfGap++;
        *reverseIter = -1;
        reverseIter++;
      }
    }
    reverseIter = lowerIdIter;
    idMoved--;
  }
}

unsigned long long DiskFragmenter::getChecksum() {
  unsigned long long checksum{0};
  for (int i = 0; i < memoryBlocks.size(); i++) {
    checksum += memoryBlocks[i] > 0 ? (unsigned long long)memoryBlocks[i] *
                                          (unsigned long long)(i)
                                    : 0;
  }
  return checksum;
}
