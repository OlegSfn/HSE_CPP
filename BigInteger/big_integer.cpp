#include "big_integer.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

void RemoveLeadingZeros(BigInteger& number){
  while(number.digits_.end()[-1] == 0 && number.digits_.size() != 1){
    number.digits_.pop_back();
  }
}

BigInteger::BigInteger(int64_t n) {
  if (n < 0){
    is_negative_ = true;
    n *= -1;
  } else if (n == 0){
    digits_.push_back(0);
  }

  while(n > 0) {
    DigitType digit = 0;
    digit += n%digit_mod;
    n /= digit_mod;
    digits_.push_back(digit);
  }
}

BigInteger::BigInteger(int32_t num) : BigInteger(static_cast<int64_t>(num)) {}

BigInteger::BigInteger(const char *char_arr) {
  std::string string = char_arr;
  if (char_arr[0] == '-'){
    is_negative_ = true;
  }

  for (auto it = string.crbegin(); it != string.crend() - (char_arr[0] == '-' || char_arr[0] == '+'); ++it) {
    DigitType digit = *it - '0';
    size_t i = 0;
    while(i != 2){
      ++it;
      if (it == string.crend() - (char_arr[0] == '-' || char_arr[0] == '+')){
        break;
      }
      digit = digit + (*it - '0') * static_cast<DigitType>(std::pow(10, i+1));
      ++i;
    }
    digits_.push_back(digit);
    if (it == string.crend() - (char_arr[0] == '-' || char_arr[0] == '+')){
      break;
    }
  }
}

bool BigInteger::IsNegative() const {
  return is_negative_;
}

BigInteger BigInteger::operator+() const {
  return *this;
}

BigInteger BigInteger::operator-() const {
  BigInteger big_integer = *this;
  big_integer.is_negative_ = !big_integer.is_negative_;
  return big_integer;
}

std::ostream &operator<<(std::ostream &ostream, const BigInteger &other) {
  if (other.is_negative_){
    ostream << '-';
  }

  for (auto it = other.digits_.crbegin(); it != other.digits_.crend(); ++it) {
    if (it == other.digits_.crbegin()){
      ostream << *it;
      continue;
    }

    if (*it == 0){
      ostream << "000";
    } else if (*it / 10 == 0){
      ostream << "00" + std::to_string(*it);
    } else if (*it / 100 == 0){
      ostream << "0" + std::to_string(*it);
    } else {
      ostream << *it;
    }
  }

  return ostream;
}

std::istream &operator>>(std::istream &istream, BigInteger &other) {
  std::string input;
  istream >> input;
  other = BigInteger(input.c_str());
  return istream;
}

BigInteger operator+(const BigInteger &l, const BigInteger &r) {
  BigInteger result;

  if (l.is_negative_ == r.is_negative_){
    result.is_negative_ = l.is_negative_;
    BigInteger::DigitType carry = 0;
    size_t i = 0;
    while(i < std::min(l.digits_.size(), r.digits_.size())){
      BigInteger::DigitType digit = l.digits_[i] + r.digits_[i] + carry;
      if (digit < BigInteger::digit_mod){
        result.digits_.push_back(digit);
        carry = 0;
      } else {
        digit -= BigInteger::digit_mod;
        result.digits_.push_back(digit);
        carry = 1;
      }
      ++i;
    }

    while(i < l.digits_.size()){
      BigInteger::DigitType digit = l.digits_[i] + carry;
      if (digit < BigInteger::digit_mod){
        result.digits_.push_back(digit);
        carry = 0;
      } else {
        digit -= BigInteger::digit_mod;
        result.digits_.push_back(digit);
        carry = 1;
      }
      ++i;
    }

    while(i < r.digits_.size()){
      BigInteger::DigitType digit = r.digits_[i] + carry;
      if (digit < BigInteger::digit_mod){
        result.digits_.push_back(digit);
        carry = 0;
      } else {
        digit -= BigInteger::digit_mod;
        result.digits_.push_back(digit);
        carry = 1;
      }
      ++i;
    }

    if (carry == 1){
      result.digits_.push_back(1);
    }
  } else {
    if (l == -r){
      return 0;
    }

    bool abs_l_is_bigger = l.is_negative_ ? -l > r : l > -r;
    result.is_negative_ = l.is_negative_ == abs_l_is_bigger;
    BigInteger::DigitType carry = 0;
    size_t i = 0;
    while(i < std::min(l.digits_.size(), r.digits_.size())){
      BigInteger::DigitType digit = 0;
      if (abs_l_is_bigger) {
        if (l.digits_[i] < r.digits_[i] +carry){
          digit = BigInteger::digit_mod + l.digits_[i] - r.digits_[i] - carry;
          carry = 1;
        } else {
          digit = l.digits_[i] - r.digits_[i] - carry;
          carry = 0;
        }
      } else {
        if (r.digits_[i] < l.digits_[i] + carry){
          digit = BigInteger::digit_mod + r.digits_[i] - l.digits_[i] - carry;
          carry = 1;
        } else{
          digit = r.digits_[i] - l.digits_[i] - carry;
          carry = 0;
        }
      }

      result.digits_.push_back(digit);
      ++i;
    }

    while(i < l.digits_.size()){
      BigInteger::DigitType digit = l.digits_[i] - carry;
      if (digit != 0){
        result.digits_.push_back(digit);
      }
      ++i;
    }

    while(i < r.digits_.size()){
      BigInteger::DigitType digit = r.digits_[i] - carry;
      if (digit != 0){
        result.digits_.push_back(digit);
      }
      ++i;
    }
  }

  RemoveLeadingZeros(result);
  if (result.digits_.size() * 3 > BigInteger::digit_max_size){
    throw BigIntegerOverflow{};
  }
  return result;
}

BigInteger operator*(const BigInteger &l, const BigInteger &r) {
  BigInteger result;
  result.digits_.resize(l.digits_.size() + r.digits_.size());
  for (size_t i = 0; i < l.digits_.size(); ++i) {
    BigInteger::DigitType carry = 0;
    for (size_t j = 0; j < r.digits_.size() || carry != 0; ++j) {
      BigInteger::DigitType cur = result.digits_[i + j] + l.digits_[i] * (j < r.digits_.size() ? r.digits_[j] : 0) + carry;
      result.digits_[i + j] = cur % BigInteger::digit_mod;
      carry = cur / BigInteger::digit_mod;
    }
  }

  RemoveLeadingZeros(result);
  result.is_negative_ = l.is_negative_ != r.is_negative_ && result != 0;
  if (result.digits_.size() * 3 > BigInteger::digit_max_size){
    throw BigIntegerOverflow{};
  }
  return result;
}


bool operator<(const BigInteger &l, const BigInteger &r) {
  if (l.is_negative_ != r.is_negative_){
    return l.is_negative_;
  }

  if (l.digits_.size() != r.digits_.size()){
    return (l.digits_.size() < r.digits_.size() && !l.is_negative_) || (l.digits_.size() > r.digits_.size() && l.is_negative_);
  }

  for (int i = static_cast<int>(l.digits_.size()-1); i >= 0; --i) {
    if ((l.digits_[i] < r.digits_[i] && !l.is_negative_) || (l.digits_[i] > r.digits_[i] && l.is_negative_)){
      return true;
    }

    if (l.digits_[i] > r.digits_[i]){
      return false;
    }
  }

  return false;
}
bool operator>(const BigInteger &l, const BigInteger &r) {
  return r < l;
}

bool operator==(const BigInteger &l, const BigInteger &r) {
  if (l.is_negative_ != r.is_negative_){
    return false;
  }

  if (l.digits_.size() != r.digits_.size()){
    return false;
  }

  for (size_t i = 0; i < l.digits_.size(); ++i) {
    if (l.digits_[i] != r.digits_[i]){
      return false;
    }
  }

  return true;
}
bool operator!=(const BigInteger &l, const BigInteger &r) {
  return !(l == r);
}
bool operator<=(const BigInteger &l, const BigInteger &r) {
  return l < r || l == r;
}
bool operator>=(const BigInteger &l, const BigInteger &r) {
  return l > r || l == r;
}
BigInteger operator-(const BigInteger &l, const BigInteger &r) {
  return l + (-r);
}
BigInteger &BigInteger::operator++() {
  *this += 1;
  return *this;
}

BigInteger BigInteger::operator++(int) {
  auto big_integer = *this;
  *this += 1;
  return big_integer;
}

BigInteger &BigInteger::operator--() {
  *this -= 1;
  return *this;
}

BigInteger BigInteger::operator--(int) {
  auto big_integer = *this;
  *this -= 1;
  return big_integer;
}
BigInteger &BigInteger::operator+=(const BigInteger &other) {
  *this = *this + other;
  return *this;
}
BigInteger &BigInteger::operator*=(const BigInteger &other) {
  *this = *this * other;
  return *this;
}
BigInteger &BigInteger::operator-=(const BigInteger &other) {
  *this = *this - other;
  return *this;
}
BigInteger operator/(const BigInteger &l, const BigInteger &r) {
  if (r == 0){
    throw BigIntegerDivisionByZero{};
  }

  BigInteger result;
  result.digits_.resize(l.digits_.size());
  BigInteger abs_right = r;
  abs_right.is_negative_ = false;

  BigInteger current;
  for (int i = static_cast<int>(l.digits_.size() - 1); i >= 0; --i) {
    current.digits_.insert(current.digits_.begin(), l.digits_[i]);
    int x = 0;
    int left = 0;
    int right = BigInteger::digit_mod;
    while (left <= right) {
      int m = (left + right) / 2;
      BigInteger t = abs_right * m;
      if (t <= current) {
        x = m;
        left = m + 1;
      }
      else{
        right = m - 1;
      }
    }

    result.digits_[i] = x;
    current = current - abs_right * x;
  }

  RemoveLeadingZeros(result);
  result.is_negative_ = l.is_negative_ != r.is_negative_ && result != 0;
  return result;
}
BigInteger &BigInteger::operator/=(const BigInteger &other) {
  *this = *this / other;
  return *this;
}
BigInteger operator%(const BigInteger &l, const BigInteger &r) {
  BigInteger result;
  BigInteger abs_l = l;
  abs_l.is_negative_ = false;
  BigInteger abs_r = r;
  abs_r.is_negative_ = false;
  result = abs_l - abs_r * (abs_l/abs_r);
  result.is_negative_ = l.is_negative_;
  return result;
}
BigInteger &BigInteger::operator%=(const BigInteger &other) {
  *this = *this % other;
  return *this;
}
