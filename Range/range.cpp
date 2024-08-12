#include "range.h"

RangeIterator Range::end() const {
  return {end_, step_};
}
RangeIterator Range::begin() const {
  return {begin_, step_};
}
RangeIterator Range::rbegin() const {
  int new_begin = begin_ - 1;
  if (step_ < 0) {
    new_begin = begin_ + 1;
  }

  for (auto it : Range(begin_, end_, step_)) {
    new_begin = it;
  }

  return {new_begin, -step_};
}
RangeIterator Range::rend() const {
  if (step_ > 0) {
    return {begin_ - 1, -step_};
  }

  return {begin_ + 1, -step_};
}
const RangeIterator &RangeIterator::operator++() {
  current_ += step_;
  return *this;
}
int RangeIterator::operator*() const {
  return current_;
}
bool RangeIterator::operator!=(const RangeIterator &other) const {
  if (step_ == 0) {
    return false;
  }
  return step_ > 0 ? current_ < other.current_ : current_ > other.current_;
}
