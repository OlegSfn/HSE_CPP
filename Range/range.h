#ifndef RANGE__RANGE_H_
#define RANGE__RANGE_H_

#define REVERSE_RANGE_IMPLEMENTED

class RangeIterator {
 private:
  int current_;
  int step_;

 public:
  RangeIterator(int start, int step) : current_(start), step_(step) {
  }

  bool operator!=(const RangeIterator& other) const;

  int operator*() const;

  const RangeIterator& operator++();
};

class Range {
 private:
  int begin_;
  int end_;
  int step_;

 public:
  explicit Range(int end) : Range(0, end) {
  }

  Range(int begin, int end) : Range(begin, end, 1) {
  }

  Range(int begin, int end, int step) : begin_(begin), end_(end), step_(step) {
  }

  [[nodiscard]] RangeIterator begin() const;  // NOLINT

  [[nodiscard]] RangeIterator end() const;  // NOLINT

  [[nodiscard]] RangeIterator rbegin() const;  // NOLINT

  [[nodiscard]] RangeIterator rend() const;  // NOLINT
};

#endif  // RANGE__RANGE_H_
