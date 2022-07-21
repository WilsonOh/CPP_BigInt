#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>

class BigInt {
  std::string _val;
  bool _negative;

  friend BigInt mult_helper(const BigInt &a, const BigInt &b);

public:
  BigInt();
  BigInt(const std::string &val);
  BigInt(const std::string &val, bool negative);
  BigInt(const int64_t &val);
  BigInt negate() const;

  BigInt operator+(const BigInt &other) const;
  BigInt operator-(const BigInt &other) const;
  BigInt operator/(const BigInt &other) const;
  BigInt operator*(const BigInt &other) const;
  BigInt operator%(const BigInt &other) const;
  BigInt &operator%=(const BigInt &other);
  BigInt &operator+=(const BigInt &other);
  BigInt &operator-=(const BigInt &other);
  BigInt &operator/=(const BigInt &other);
  BigInt &operator*=(const BigInt &other);
  BigInt &operator--();
  BigInt &operator++();
  BigInt operator--(int);
  BigInt operator++(int);
  bool operator>(const BigInt &other) const;
  bool operator<(const BigInt &other) const;
  bool operator>=(const BigInt &other) const;
  bool operator<=(const BigInt &other) const;
  bool operator==(const BigInt &other) const;
  bool operator!=(const BigInt &other) const;

  friend std::ostream &operator<<(std::ostream &out, const BigInt &bn);
};

BigInt operator""_bn(const char *s);
BigInt operator""_bn(const char *s, std::size_t);

#endif // !BIGINT_HPP
