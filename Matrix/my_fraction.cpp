#include <iostream>
#include <numeric>
#include <vector>
#include "rational.h"

int GetSign(int x) {
  return (x > 0) - (x < 0);
}

Rational::Rational() : Rational(0) {
}

Rational::Rational(int n) : numerator_(n), denominator_(1) {
}

Rational::Rational(int numerator, int denominator) : numerator_(0), denominator_(1) {
  SetNumerator(numerator);
  SetDenominator(denominator);
}

int Rational::GetNumerator() const {
  return numerator_;
}

int Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(int numerator) {
  this->numerator_ = numerator;
  MakePretty();
}

void Rational::SetDenominator(int denominator) {
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }

  this->denominator_ = denominator;
  MakePretty();
}

void Rational::MakePretty() {
  int gcd = std::gcd(numerator_, denominator_);
  this->numerator_ = GetSign(numerator_) * GetSign(denominator_) * std::abs(numerator_ / gcd);
  this->denominator_ = std::abs(denominator_ / gcd);
}

Rational operator+(const Rational& rational, const Rational& other) {
  return {rational.numerator_ * other.denominator_ + other.numerator_ * rational.denominator_,
          rational.denominator_ * other.denominator_};
}

Rational operator-(const Rational& rational, const Rational& other) {
  return {rational.numerator_ * other.denominator_ - other.numerator_ * rational.denominator_,
          rational.denominator_ * other.denominator_};
}

Rational operator*(const Rational& rational, const Rational& other) {
  return {rational.numerator_ * other.numerator_, rational.denominator_ * other.denominator_};
}

Rational operator/(const Rational& rational, const Rational& other) {
  if (other.numerator_ == 0) {
    throw RationalDivisionByZero{};
  }

  return {rational.numerator_ * other.denominator_, rational.denominator_ * other.numerator_};
}

Rational& operator+=(Rational& rational, const Rational& other) {
  rational.numerator_ = rational.numerator_ * other.denominator_ + other.numerator_ * rational.denominator_;
  rational.denominator_ = rational.denominator_ * other.denominator_;
  rational.MakePretty();
  return rational;
}

Rational& operator-=(Rational& rational, const Rational& other) {
  rational.numerator_ = rational.numerator_ * other.denominator_ - other.numerator_ * rational.denominator_;
  rational.denominator_ = rational.denominator_ * other.denominator_;
  rational.MakePretty();
  return rational;
}

Rational& operator*=(Rational& rational, const Rational& other) {
  rational.numerator_ = rational.numerator_ * other.numerator_;
  rational.denominator_ = rational.denominator_ * other.denominator_;
  rational.MakePretty();
  return rational;
}

Rational& operator/=(Rational& rational, const Rational& other) {
  if (other.numerator_ == 0) {
    throw RationalDivisionByZero{};
  }

  rational.numerator_ = rational.numerator_ * other.denominator_;
  rational.denominator_ = rational.denominator_ * other.numerator_;
  rational.MakePretty();
  return rational;
}

Rational Rational::operator+() const {
  return *this;
}

Rational Rational::operator-() const {
  return {-numerator_, denominator_};
}

Rational& Rational::operator++() {
  numerator_ = numerator_ + denominator_;
  MakePretty();
  return *this;
}

Rational Rational::operator++(int) {
  auto old_value = *this;
  ++(*this);
  return old_value;
}

Rational& Rational::operator--() {
  numerator_ = numerator_ - denominator_;
  MakePretty();
  return *this;
}

Rational Rational::operator--(int) {
  auto old_value = *this;
  --(*this);
  return old_value;
}

bool operator==(const Rational& rational, const Rational& other) {
  return (rational.numerator_ == other.numerator_ && rational.denominator_ == other.denominator_);
}

bool operator<(const Rational& rational, const Rational& other) {
  return rational.numerator_ * other.denominator_ < other.numerator_ * rational.denominator_;
}

bool operator>(const Rational& rational, const Rational& other) {
  return other < rational;
}

bool operator<=(const Rational& rational, const Rational& other) {
  return rational.numerator_ * other.denominator_ <= other.numerator_ * rational.denominator_;
}

bool operator>=(const Rational& rational, const Rational& other) {
  return other <= rational;
}

std::istream& operator>>(std::istream& is, Rational& rational) {
  std::string s;
  is >> s;

  if (s.find('/') != std::string::npos) {
    std::vector<int> rational_from_inp;

    std::string cur_string;
    for (size_t i = 0; i < s.size(); ++i) {
      if (s[i] == '/') {
        rational_from_inp.push_back(std::stoi(cur_string));
        cur_string.clear();
      } else {
        cur_string += s[i];
      }
    }

    if (!cur_string.empty()) {
      rational_from_inp.push_back(std::stoi(cur_string));
    }

    if (rational_from_inp[1] == 0) {
      throw RationalDivisionByZero{};
    }

    rational.numerator_ = rational_from_inp[0];
    rational.denominator_ = rational_from_inp[1];
    rational.MakePretty();
  } else {
    rational.numerator_ = std::stoi(s);
  }

  return is;
}

std::ostream& operator<<(std::ostream& os, Rational rational) {
  if (rational.denominator_ == 1) {
    os << rational.numerator_;
  } else {
    os << rational.numerator_ << '/' << rational.denominator_;
  }

  return os;
}