#include "../segment.h"
#include "../point.h"
#include "../vector.h"
#include "../line.h"
#include <memory>

namespace geometry {

Segment::Segment(const Point &a, const Point &b) : start_a_(new Point(a)), start_b_(new Point(b)) {
}

IShape &Segment::Move(const Vector &vector) {
  *start_a_ += vector;
  *start_b_ += vector;
  return *this;
}
bool Segment::ContainsPoint(const Point &point) const {
  return point.CrossesSegment(*this);
}
bool Segment::CrossesSegment(const Segment &segment) const {
  if (*this->start_a_ == *this->start_b_) {
    return this->start_a_->CrossesSegment(segment);
  } else if (*segment.start_a_ == *segment.start_b_) {
    return segment.start_a_->CrossesSegment(*this);
  }

  Line line1 = Line(*start_a_, *start_b_);
  Line line2 = Line(*segment.start_a_, *segment.start_b_);
  if (line1.IsParallelWith(line2)) {
    if ((*start_a_ - *start_b_).CrossProductWith(*start_a_ - *segment.start_a_) == 0) {
      int minSegmentX = std::min(segment.start_a_->x_, segment.start_b_->x_);
      int maxSegmentX = std::max(segment.start_a_->x_, segment.start_b_->x_);
      int minX = std::min(start_a_->x_, start_b_->x_);
      int maxX = std::max(start_a_->x_, start_b_->x_);

      int minSegmentY = std::min(segment.start_a_->y_, segment.start_b_->y_);
      int maxSegmentY = std::max(segment.start_a_->y_, segment.start_b_->y_);
      int minY = std::min(start_a_->y_, start_b_->y_);
      int maxY = std::max(start_a_->y_, start_b_->y_);

      bool isCrossedByX = (minSegmentX <= start_b_->x_ && start_b_->x_ <= maxSegmentX) ||
                          (minSegmentX <= start_a_->x_ && start_a_->x_ <= maxSegmentX) ||
                          (minX <= segment.start_a_->x_ && segment.start_a_->x_ <= maxX);

      bool isCrossedByY = (minSegmentY <= start_b_->y_ && start_b_->y_ <= maxSegmentY) ||
                          (minSegmentY <= start_a_->y_ && start_a_->y_ <= maxSegmentY) ||
                          (minY <= segment.start_a_->y_ && segment.start_a_->y_ <= maxY);

      return isCrossedByX && isCrossedByY;
    } else {
      return false;
    }
  } else {
    return line1.CrossesSegment(segment) && line2.CrossesSegment(*this);
  }
}

std::unique_ptr<IShape> Segment::Clone() const {
  return std::make_unique<Segment>(*start_a_, *start_b_);
}
std::string Segment::ToString() const {
  return "Segment(" + start_a_->ToString() + ", " + start_b_->ToString() + ")";
}

}  // namespace geometry
