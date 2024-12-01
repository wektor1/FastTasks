#include "BracesValidator.hpp"
#include <gtest/gtest.h>

TEST(BracesValidatorTest, emptyStringIsValid) {
  BracesValidator sut("");

  EXPECT_TRUE(sut.isValid());
}

TEST(BracesValidatorTest, noBracesIsValid) {
  BracesValidator sut("dead meat");

  EXPECT_TRUE(sut.isValid());
}

TEST(BracesValidatorTest, singleParenthesesIsNotValid) {
  BracesValidator sut("(");

  EXPECT_FALSE(sut.isValid());
}

TEST(BracesValidatorTest, singleClosedParenthesesIsNotValid) {
  BracesValidator sut(")");

  EXPECT_FALSE(sut.isValid());
}

TEST(BracesValidatorTest, parenthesesPairIsValid) {
  BracesValidator sut("()");

  EXPECT_TRUE(sut.isValid());
}

TEST(BracesValidatorTest, invertedParenthesesPairIsNotValid) {
  BracesValidator sut(")(");

  EXPECT_FALSE(sut.isValid());
}

TEST(BracesValidatorTest, multiParentheses) {
  BracesValidator sut("()()((())())");

  EXPECT_TRUE(sut.isValid());
}

TEST(BracesValidatorTest, multiEnclosures) {
  BracesValidator sut("({a})({dh{}jk})gx{((bc([])cx[{}])v())}");

  EXPECT_TRUE(sut.isValid());
}

TEST(BracesValidatorTest, multiEnclosuresWithIncorrectClosing) {
  BracesValidator sut("(({})[)]");

  EXPECT_FALSE(sut.isValid());
}