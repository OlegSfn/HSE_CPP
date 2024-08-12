#include "../segment.h"
#include "../point.h"
#include "../vector.h"
#include "../line.h"
#include "../ray.h"
#include <memory>

namespace geometry {

int getSign(int64_t);

Ray::Ray(const Point &a, const Point &b) : start_a_(new Point(a)), start_b_(new Point(b)) {
}
IShape &Ray::Move(const Vector &vector) {
  *start_a_ += vector;
  *start_b_ += vector;
  return *this;
}
bool Ray::ContainsPoint(const Point &point) const {
  Line line(*start_a_, *start_b_);
  if (!line.ContainsPoint(point)) {
    return false;
  }

  Vector directionOfRay(start_b_->x_ - start_a_->x_, start_b_->y_ - start_a_->y_);
  Vector directionToPoint(point.x_ - start_a_->x_, point.y_ - start_a_->y_);

  return directionOfRay.DotProductWith(directionToPoint) >= 0;
}
bool Ray::CrossesSegment(const Segment &segment) const {
  Line line(*start_a_, *start_b_);
  if (!line.CrossesSegment(segment)) {
    return false;
  }

  Vector ao = *start_a_ - *segment.start_a_;
  Vector ab = *segment.start_b_ - *segment.start_a_;
  Vector v = *start_b_ - *start_a_;

  return getSign(ao.CrossProductWith(ab)) * getSign(v.CrossProductWith(ab)) <= 0;
}
std::unique_ptr<IShape> Ray::Clone() const {
  return std::make_unique<Ray>(*start_a_, *start_b_);
}
std::string Ray::ToString() const {
  return "Ray(" + start_a_->ToString() + ", " + (*start_b_ - *start_a_).ToString() + ")";
}

}  // namespace geometry
