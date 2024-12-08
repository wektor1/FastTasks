#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

class PrintQueue {
public:
  unsigned long long run(const std::vector<std::string> &);

private:
  void processInput(const std::vector<std::string> &);
  unsigned long long getResultFromUpdates();
  unsigned long long getResultIfCorrect(std::vector<unsigned long long>);

  std::map<unsigned long long, std::set<unsigned long long>> pagesAfterKeyPage;
  std::vector<std::vector<unsigned long long>> updates;
};