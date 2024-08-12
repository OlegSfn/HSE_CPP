#ifndef BIGINTEGER__BIG_INTEGER_H_
#define BIGINTEGER__BIG_INTEGER_H_
#define BIG_INTEGER_DIVISION_IMPLEMENTED

#include <cmath>
#include <cstdint>
#include <vector>
#include <stdexcept>

class BigIntegerOverflow : public std::runtime_error {
 public:
  BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {
  }
};

class BigIntegerDivisionByZero : public std::runtime_error {
 public:
  BigIntegerDivisionByZero() : std::runtime_error("BigIntegerDivisionByZero") {
  }
};

class BigInteger{
  friend BigInteger operator+(const BigInteger& l, const BigInteger& r);
  friend BigInteger operator-(const BigInteger& l, const BigInteger& r);
  friend BigInteger operator*(const BigInteger& l, const BigInteger& r);
  friend BigInteger operator/(const BigInteger& l, const BigInteger& r);
  friend BigInteger operator%(const BigInteger& l, const BigInteger& r);
  friend bool operator<(const BigInteger& l, const BigInteger& r);
  friend bool operator<=(const BigInteger& l, const BigInteger& r);
  friend bool operator>(const BigInteger& l, const BigInteger& r);
  friend bool operator>=(const BigInteger& l, const BigInteger& r);
  friend bool operator==(const BigInteger& l, const BigInteger& r);
  friend bool operator!=(const BigInteger& l, const BigInteger& r);
  friend std::ostream& operator<<(std::ostream& ostream, const BigInteger& other);
  friend std::istream& operator>>(std::istream& istream, BigInteger& other);
  friend void RemoveLeadingZeros(BigInteger& number);

 public:
  using DigitType = u_int32_t;
  inline static u_int16_t digit_size = 3;
  inline static u_int16_t digit_max_size = 30001;
  inline static u_int16_t digit_mod = static_cast<uint16_t>(std::pow(10, digit_size));
  BigInteger() = default;
  BigInteger(int32_t num); // NOLINT
  BigInteger(int64_t num); // NOLINT
  BigInteger(const char* char_arr); // NOLINT
  [[nodiscard]] bool IsNegative() const;

  BigInteger operator+() const;
  BigInteger operator-() const;
  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger operator--(int);
  BigInteger& operator--();
  BigInteger& operator+=(const BigInteger& other);
  BigInteger& operator*=(const BigInteger& other);
  BigInteger& operator-=(const BigInteger& other);
  BigInteger& operator/=(const BigInteger& other);
  BigInteger& operator%=(const BigInteger& other);


 private:
  std::vector<DigitType> digits_;
  bool is_negative_ = false;
};
#endif //BIGINTEGER__BIG_INTEGER_H_
