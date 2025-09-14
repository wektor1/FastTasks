#include "DailyTask.hpp"
#include <gtest/gtest.h>

TEST(DailtTaskTest, firstUt) {
  Solution sut{};

  EXPECT_EQ(sut.countInterestingSubarrays({3, 2, 4}, 2, 1), 3);
}