#pragma once

#include <string>
#include <vector>

class HoofIt {
public:
  int run(const std::vector<std::string> &);

private:
  void saveRatingForTrail(std::pair<int, int>,
                          const std::vector<std::string> &);

  int result{0};
};
