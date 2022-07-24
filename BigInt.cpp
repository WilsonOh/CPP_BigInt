#include "BigInt.hpp"
#include <algorithm> // std::find_if
#include <cmath>     // std::abs
#include <string_view>

BigInt::BigInt() : _val("0"), _negative(false) {}

BigInt::BigInt(const std::string &val) {
  if (val.front() == '-') {
    _negative = true;
    _val = std::string(val, 1, val.length() - 1);
  } else {
    _negative = false;
    _val = val;
  }
}

BigInt::BigInt(const std::string &val, bool negative)
    : _val(val), _negative(negative) {}

BigInt::BigInt(const int64_t &val)
    : _val(std::to_string(val)), _negative(val < 0) {}

BigInt BigInt::negate() const { return {_val, !_negative}; }

BigInt BigInt::operator+(const BigInt &bn) const {
  if (this->_negative && bn._negative) {
    return (this->negate() + bn.negate()).negate();
  }
  if (!this->_negative && bn._negative) {
    return (*this - bn.negate());
  }
  if (this->_negative && !bn._negative) {
    return (this->negate() - bn).negate();
  }
  std::string ret;
  std::string_view other =
      this->_val.length() > bn._val.length() ? bn._val : this->_val;
  if (this->_val.length() > bn._val.length()) {
    ret.reserve(this->_val.length() + 1);
    ret = this->_val;
  } else {
    ret.reserve(bn._val.length() + 1);
    ret = bn._val;
  }
  auto it1 = ret.rbegin();
  auto it2 = other.crbegin();
  auto it1_end = ret.rend();
  auto it2_end = other.crend();

  char a;
  char b;
  int carry = 0;
  int curr;

  while (it1 != it1_end || it2 != it2_end) {
    if (it1 == it1_end) {
      a = 0;
    } else {
      a = *it1 - '0';
    }
    if (it2 == it2_end) {
      b = 0;
    } else {
      b = *(it2++) - '0';
    }
    curr = a + b + carry;
    if (curr > 9) {
      curr %= 10;
      carry = 1;
    } else {
      carry = 0;
    }
    *it1 = curr + '0';
    ++it1;
  }
  if (carry) {
    ret.insert(ret.begin(), '1');
  }
  return {ret};
}

BigInt BigInt::operator-(const BigInt &bn) const {
  if (this->_negative && bn._negative) {
    if (*this > bn) {
      return (bn.negate() - this->negate());
    } else {
      return (this->negate() - bn.negate()).negate();
    }
  }
  if (!this->_negative && !bn._negative) {
    if (*this < bn) {
      return (bn - *this).negate();
    }
  }
  if (this->_negative && !bn._negative) {
    return (this->negate() + bn).negate();
  }
  if (!this->_negative && bn._negative) {
    return (*this + bn.negate());
  }
  std::string ret = this->_val;
  std::string_view other = bn._val;
  auto it1 = ret.rbegin();
  auto it2 = other.crbegin();
  auto it1_end = ret.rend();
  auto it2_end = other.crend();

  int a;
  int b;
  int curr;
  int carry = 0;

  while (it1 != it1_end || it2 != it2_end) {
    if (it1 == it1_end) {
      a = 0;
    } else {
      a = *it1 - '0';
    }
    if (it2 == it2_end) {
      b = 0;
    } else {
      b = *(it2++) - '0';
    }
    if (a > b) {
      curr = a - b - carry;
      carry = 0;
    } else if (a < b || it2 == it2_end) {
      curr = (a + 10) - b - carry;
      carry = 1;
    } else {
      curr = 0;
      carry = 0;
    }
    if (it1 == it1_end) {
      ret.insert(ret.begin(), static_cast<char>(curr + '0'));
      continue;
    }
    *it1 = curr + '0';
    ++it1;
  }
  auto tmp = std::find_if(ret.cbegin(), ret.cend(),
                          [](const char &c) { return c != '0'; });
  if (tmp == ret.cend()) {
    return {"0"};
  }
  return {std::string(tmp, ret.cend())};
}

bool BigInt::operator>(const BigInt &other) const {
  if (*this == other)
    return false;
  if (this->_negative && !other._negative)
    return false;
  if (!this->_negative && other._negative)
    return true;
  if (other._val.length() > this->_val.length())
    return this->_negative && other._negative ? true : false;
  if (other._val.length() < this->_val.length())
    return this->_negative && other._negative ? false : true;

  bool larger = false;
  auto it1 = this->_val.cbegin();
  auto it2 = other._val.cbegin();
  auto it1_end = this->_val.cend();
  auto it2_end = other._val.cend();
  int a;
  int b;
  while (it1 != it1_end && it2 != it2_end) {
    a = *(it1++) - '0';
    b = *(it2++) - '0';
    if (a > b) {
      larger = true;
      break;
    }
    if (a < b) {
      larger = false;
      break;
    }
  }
  if (this->_negative && other._negative)
    return !larger;
  return larger;
}

BigInt &BigInt::operator+=(const BigInt &other) {
  BigInt ret = *this + other;
  *this = ret;
  return *this;
}

BigInt &BigInt::operator-=(const BigInt &other) {
  BigInt ret = *this - other;
  *this = ret;
  return *this;
}

BigInt &BigInt::operator--() {
  BigInt ret = *this - 1_bn;
  *this = ret;
  return *this;
}

BigInt &BigInt::operator++() {
  BigInt ret = *this + 1_bn;
  *this = ret;
  return *this;
}

BigInt BigInt::operator--(int) {
  BigInt ret = *this;
  --(*this);
  return ret;
}

BigInt BigInt::operator++(int) {
  BigInt ret = *this;
  ++(*this);
  return ret;
}

BigInt &BigInt::operator/=(const BigInt &other) {
  BigInt ret = *this / other;
  *this = ret;
  return *this;
}

BigInt &BigInt::operator*=(const BigInt &other) {
  BigInt ret = *this * other;
  *this = ret;
  return *this;
}

BigInt mult_helper(const BigInt &a, const BigInt &b) {
  auto ret = 0_bn;
  int idx = a._val.length() - 1;
  for (const char &c : a._val) {
    BigInt tmp = 0_bn;
    for (int i = 0; i < (c - '0'); ++i) {
      tmp += b;
    }
    tmp._val.append(idx, '0');
    idx--;
    ret += tmp;
  }
  return ret;
}

BigInt BigInt::operator*(const BigInt &other) const {
  BigInt a = *this;
  a._negative = false;
  BigInt b = other;
  b._negative = false;
  auto ret =
      a._val.length() < b._val.length() ? mult_helper(a, b) : mult_helper(b, a);
  ret._negative = !(this->_negative && other._negative) &&
                  (this->_negative || other._negative);
  return ret;
}

BigInt BigInt::operator/(const BigInt &other) const {
  auto quotient = 0_bn;
  BigInt curr = *this;
  curr._negative = false;
  BigInt divisor = other;
  divisor._negative = false;
  while (curr > 0) {
    if ((curr - divisor) >= 0)
      ++quotient;
    curr -= divisor;
  }
  quotient._negative = !(this->_negative && other._negative) &&
                       (this->_negative || other._negative);
  return quotient;
}

BigInt BigInt::operator%(const BigInt &other) const {
  BigInt divisor = other;
  divisor._negative = false;
  BigInt quotient = *this / other;
  quotient._negative = false;
  BigInt n = *this;
  n._negative = false;
  BigInt ret = n - (quotient * divisor);
  ret._negative = false;
  return ret;
}

BigInt &BigInt::operator%=(const BigInt &other) {
  BigInt ret = *this % other;
  *this = other;
  return *this;
}

bool BigInt::operator<(const BigInt &other) const {
  return (*this != other) && !(*this > other);
}

bool BigInt::operator==(const BigInt &other) const {
  return (this->_negative == other._negative) && (this->_val == other._val);
}

bool BigInt::operator!=(const BigInt &other) const { return !(*this == other); }

bool BigInt::operator>=(const BigInt &other) const {
  return *this > other || *this == other;
}

bool BigInt::operator<=(const BigInt &other) const {
  return *this < other || *this == other;
}

std::ostream &operator<<(std::ostream &out, const BigInt &bn) {
  if (bn._negative) {
    out << '-';
  }
  out << bn._val;
  return out;
}

BigInt operator""_bn(const char *s) { return {s}; }
BigInt operator""_bn(const char *s, std::size_t) { return {s}; }
