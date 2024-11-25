#include "BracesValidator.hpp"
#include <gtest/gtest.h>

TEST(BracesValidatorTest, emptyStringIsValid) {
  BracesValidator sut("");

  EXPECT_TRUE(sut.isValid());
}