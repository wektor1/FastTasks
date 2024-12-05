#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

class PrintQueue {
public:
  unsigned long run(const std::vector<std::string> &);

private:
  void processInput(const std::vector<std::string> &);
  unsigned long getResultFromUpdates();
  unsigned long getResultIfCorrect(std::vector<unsigned long>);

  std::map<unsigned long, std::set<unsigned long>> pagesAfterKeyPage;
  std::vector<std::vector<unsigned long>> updates;
};