#include "../circle.h"
#include "../segment.h"
#include "../point.h"
#include "../vector.h"
#include <cmath>
#include <memory>

namespace geometry {

Circle::Circle(const geometry::Point &center, size_t radius) : center_(new Point(center)), radius_(radius) {
}
IShape &Circle::Move(const Vector &vector) {
  *center_ += vector;
  return *this;
}
bool Circle::ContainsPoint(const Point &point) const {
  return SdfSquared(point) <= 0;
}
bool Circle::CrossesSegment(const Segment &segment) const {
  return center_->DistanceToSegmentSqr(segment) <= radius_ * radius_ &&
         ((*center_ - *segment.start_a_).GetLengthSqr() >= radius_ * radius_ ||
          (*center_ - *segment.start_b_).GetLengthSqr() >= radius_ * radius_);
}
int Circle::SdfSquared(const Point &point) const {
  return static_cast<int>(std::pow(point.x_ - center_->x_, 2) + std::pow(point.y_ - center_->y_, 2) -
                          std::pow(radius_, 2));
}
std::unique_ptr<IShape> Circle::Clone() const {
  return std::make_unique<Circle>(*center_, radius_);
}
std::string Circle::ToString() const {
  return "Circle(" + center_->ToString() + ", " + std::to_string(static_cast<int>(radius_)) + ")";
}

}  // namespace geometry