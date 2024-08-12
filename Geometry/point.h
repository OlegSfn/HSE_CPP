#ifndef GEOMETRY_HEADERS_POINT_H_
#define GEOMETRY_HEADERS_POINT_H_
#include "i_shape.h"
#include <memory>

namespace geometry {

class Vector;
class Segment;

class Point : public IShape {
 private:
  int x_;
  int y_;

  friend Vector operator-(const Point& a, const Point& b);
  friend Point& operator+=(Point& a, const Vector& b);

  friend class Vector;
  friend class Segment;
  friend class Line;
  friend class Ray;
  friend class Circle;
  friend class Polygon;

 public:
  Point(int x, int y);

  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;

  friend bool operator==(const Point& a, const Point& b);
  friend bool operator!=(const Point& a, const Point& b);

  size_t DistanceToSegmentSqr(const Segment& segment) const;
};

}  // namespace geometry
#endif