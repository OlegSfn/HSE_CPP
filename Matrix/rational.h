#ifndef TEST__RATIONAL_H_
#define TEST__RATIONAL_H_
#include <iostream>

int GetSign(int x);

class Rational {
 private:
  int numerator_;
  int denominator_;

  friend Rational operator+(const Rational& rational, const Rational& other);
  friend Rational operator-(const Rational& rational, const Rational& other);
  friend Rational operator*(const Rational& rational, const Rational& other);
  friend Rational operator/(const Rational& rational, const Rational& other);

  friend Rational& operator+=(Rational& rational, const Rational& other);
  friend Rational& operator-=(Rational& rational, const Rational& other);
  friend Rational& operator*=(Rational& rational, const Rational& other);
  friend Rational& operator/=(Rational& rational, const Rational& other);

  friend bool operator<(const Rational& rational, const Rational& other);
  friend bool operator==(const Rational& rational, const Rational& other);
  friend bool operator>(const Rational& rational, const Rational& other);
  friend bool operator<=(const Rational& rational, const Rational& other);
  friend bool operator>=(const Rational& rational, const Rational& other);

  friend std::istream& operator>>(std::istream& is, Rational& rational);
  friend std::ostream& operator<<(std::ostream& os, Rational rational);

 public:
  Rational();
  Rational(int n);  // NOLINT

  Rational(int numerator, int denominator);

  int GetNumerator() const;

  int GetDenominator() const;

  void SetNumerator(int numerator);

  void SetDenominator(int denominator);

  void MakePretty();

  Rational operator+() const;
  Rational operator-() const;

  Rational& operator++();

  Rational operator++(int);

  Rational& operator--();

  Rational operator--(int);
};

class RationalDivisionByZero {};
#endif