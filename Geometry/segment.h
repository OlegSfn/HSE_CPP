#ifndef GEOMETRY_HEADERS_SEGMENT_H_
#define GEOMETRY_HEADERS_SEGMENT_H_
#include "i_shape.h"
#include <memory>

namespace geometry {

class IShape;
class Point;
class Vector;

class Segment : public IShape {
 private:
  std::unique_ptr<Point> start_a_, start_b_;

 public:
  Segment(const Point& a, const Point& b);

  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;

  friend class Line;
  friend class Point;
  friend class Circle;
  friend class Ray;
};

}  // namespace geometry
#endif