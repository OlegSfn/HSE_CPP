#include "../line.h"
#include "../point.h"
#include "../segment.h"
#include <numeric>
#include <memory>

namespace geometry {

int getSign(int64_t value) {
  if (value < 0) {
    return -1;
  } else if (value == 0) {
    return 0;
  } else {
    return 1;
  }
}

Line::Line(const Point &a, const Point &b) : start_a_(new Point(a)), start_b_(new Point(b)) {
  CalculateEquation(*start_a_, *start_b_);
}

void Line::CalculateEquation(const Point &first, const Point &second) {
  a_ = first.y_ - second.y_;
  b_ = second.x_ - first.x_;
  c_ = first.x_ * second.y_ - second.x_ * first.y_;
  int gcd = std::gcd(a_, std::gcd(b_, c_));
  a_ /= gcd;
  b_ /= gcd;
  c_ /= gcd;
}

IShape &Line::Move(const Vector &vector) {
  *start_a_ += vector;
  *start_b_ += vector;
  CalculateEquation(*start_a_, *start_b_);
  return *this;
}
bool Line::ContainsPoint(const Point &point) const {
  return InsertPointInEquation(point) == 0;
}
bool Line::CrossesSegment(const Segment &segment) const {
  return getSign(InsertPointInEquation(*segment.start_a_)) * getSign(InsertPointInEquation(*segment.start_b_)) <= 0;
}
int64_t Line::InsertPointInEquation(const Point &point) const {
  return a_ * point.x_ + b_ * point.y_ + c_;
}
std::unique_ptr<IShape> Line::Clone() const {
  return std::make_unique<Line>(*start_a_, *start_b_);
}
std::string Line::ToString() const {
  return "Line(" + std::to_string(static_cast<int>(a_)) + ", " + std::to_string(static_cast<int>(b_)) + ", " +
         std::to_string(static_cast<int>(c_)) + ")";
}

bool Line::DoesIntersectWithLine(const Line &line) const {
  return (a_ * line.b_ - line.a_ * b_ != 0 ||
          c_ / std::gcd(a_, std::gcd(b_, c_)) == line.c_ / std::gcd(line.a_, std::gcd(line.b_, line.c_)));
}
bool Line::IsParallelWith(const Line &line) const {
  return a_ * line.b_ - line.a_ * b_ == 0;
}

}  // namespace geometry
