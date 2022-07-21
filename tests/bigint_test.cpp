#include <BigInt.hpp>
#include <gtest/gtest.h>

TEST(addition_in_fix, same_length) {
  auto a = 25_bn;
  auto b = 35_bn;
  auto ans1 = 60_bn;
  auto ans2 = 10_bn;
  // +ve, +ve
  EXPECT_EQ(a + b, ans1);
  // +ve, -ve
  EXPECT_EQ(a + b.negate(), ans2.negate());
  // -ve, +ve
  EXPECT_EQ(a.negate() + b, ans2);
  // -ve, -ve
  EXPECT_EQ(a.negate() + b.negate(), ans1.negate());
}

TEST(addition_in_fix, different_length) {
  auto a = 125_bn;
  auto b = 35_bn;
  auto ans1 = 160_bn;
  auto ans2 = 90_bn;
  // +ve, +ve
  EXPECT_EQ(a + b, ans1);
  // +ve, -ve
  EXPECT_EQ(a + b.negate(), ans2);
  // -ve, +ve
  EXPECT_EQ(a.negate() + b, ans2.negate());
  // -ve, -ve
  EXPECT_EQ(a.negate() + b.negate(), ans1.negate());
}

TEST(subtraction_in_fix, same_length) {
  auto a = 25_bn;
  auto b = 35_bn;
  auto ans1 = 60_bn;
  auto ans2 = 10_bn;
  // +ve, +ve
  EXPECT_EQ(a - b, ans2.negate());
  // +ve, -ve
  EXPECT_EQ(a - b.negate(), ans1);
  // -ve, +ve
  EXPECT_EQ(a.negate() - b, ans1.negate());
  // -ve, -ve
  EXPECT_EQ(a.negate() - b.negate(), ans2);
}

TEST(subtraction_in_fix, different_length) {
  auto a = 125_bn;
  auto b = 35_bn;
  auto ans1 = 90_bn;
  auto ans2 = 160_bn;
  // +ve, +ve
  EXPECT_EQ(a - b, ans1);
  // +ve, -ve
  EXPECT_EQ(a - b.negate(), ans2);
  // -ve, +ve
  EXPECT_EQ(a.negate() - b, ans2.negate());
  // -ve, -ve
  EXPECT_EQ(a.negate() - b.negate(), ans1.negate());
}

TEST(multiplication_in_fix, small_numbers) {
  auto a = 25_bn;
  auto b = 35_bn;
  auto ans = 875_bn;
  // +ve, +ve
  EXPECT_EQ(a * b, ans);
  // +ve, -ve
  EXPECT_EQ(a * b.negate(), ans.negate());
  // -ve, +ve
  EXPECT_EQ(a.negate() * b, ans.negate());
  // -ve, -ve
  EXPECT_EQ(a.negate() * b.negate(), ans);
}

TEST(multiplication_in_fix, large_numbers) {
  auto a = 12345_bn;
  auto b = 98765_bn;
  auto ans = 1219253925_bn;
  // +ve, +ve
  EXPECT_EQ(a * b, ans);
  // +ve, -ve
  EXPECT_EQ(a * b.negate(), ans.negate());
  // -ve, +ve
  EXPECT_EQ(a.negate() * b, ans.negate());
  // -ve, -ve
  EXPECT_EQ(a.negate() * b.negate(), ans);
}

TEST(division_in_fix, small_numbers) {
  auto a = 1234_bn;
  auto b = 35_bn;
  auto ans = 35_bn;
  // +ve, +ve
  EXPECT_EQ(a / b, ans);
  // +ve, -ve
  EXPECT_EQ(a / b.negate(), ans.negate());
  // -ve, +ve
  EXPECT_EQ(a.negate() / b, ans.negate());
  // -ve, -ve
  EXPECT_EQ(a.negate() / b.negate(), ans);
}

TEST(division_in_fix, large_numbers) {
  auto a = 123456_bn;
  auto b = 9_bn;
  auto ans = 13717_bn;
  // +ve, +ve
  EXPECT_EQ(a / b, ans);
  // +ve, -ve
  EXPECT_EQ(a / b.negate(), ans.negate());
  // -ve, +ve
  EXPECT_EQ(a.negate() / b, ans.negate());
  // -ve, -ve
  EXPECT_EQ(a.negate() / b.negate(), ans);
}
