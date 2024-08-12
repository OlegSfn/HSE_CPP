#include "../vector.h"
#include "../point.h"
#include "../segment.h"
#include <memory>

namespace geometry {

Point::Point(int x, int y) {
  this->x_ = x;
  this->y_ = y;
}

Vector operator-(const geometry::Point &a, const geometry::Point &b) {
  return {a.x_ - b.x_, a.y_ - b.y_};
}

Point &operator+=(Point &a, const Vector &b) {
  a.x_ += b.x_;
  a.y_ += b.y_;
  return a;
}

IShape &Point::Move(const Vector &vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  return *this;
}
bool Point::ContainsPoint(const Point &point) const {
  return (this->x_ == point.x_ && this->y_ == point.y_);
}
bool Point::CrossesSegment(const Segment &segment) const {
  Point temp = *this;
  Vector a(temp - *segment.start_a_);
  Vector b(*segment.start_b_ - temp);
  return a.CrossProductWith(b) == 0 && a.DotProductWith(b) >= 0;
}
std::unique_ptr<IShape> Point::Clone() const {
  return std::make_unique<Point>(x_, y_);
}
std::string Point::ToString() const {
  return "Point(" + std::to_string(static_cast<int>(x_)) + ", " + std::to_string(static_cast<int>(y_)) + ")";
}
bool operator==(const Point &a, const Point &b) {
  return a.x_ == b.x_ && a.y_ == b.y_;
}
bool operator!=(const Point &a, const Point &b) {
  return !(a == b);
}

size_t Point::DistanceToSegmentSqr(const Segment &segment) const {
  Vector ap(*this - *segment.start_a_);
  Vector ab(*segment.start_b_ - *segment.start_a_);
  Vector bp(*this - *segment.start_b_);

  if (ap.DotProductWith(ab) <= 0) {
    return ap.GetLengthSqr();
  } else if (bp.DotProductWith(-ab) <= 0) {
    return bp.GetLengthSqr();
  }

  int crossProduct = ap.CrossProductWith(ab);
  return crossProduct * crossProduct / ab.GetLengthSqr();
}

}  // namespace geometry
