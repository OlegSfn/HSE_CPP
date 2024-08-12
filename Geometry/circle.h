#ifndef GEOMETRY_HEADERS_CIRCLE_H_
#define GEOMETRY_HEADERS_CIRCLE_H_
#include "i_shape.h"
#include <cstdio>
#include <memory>

namespace geometry {

class IShape;
class Point;
class Segment;
class Vector;

class Circle : public IShape {
 private:
  std::unique_ptr<Point> center_;
  size_t radius_;

 public:
  Circle(const Point& center, size_t radius);

  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;

  int SdfSquared(const Point& point) const;
};

}  // namespace geometry

#endif
