#ifndef GEOMETRY_HEADERS_LINE_H_
#define GEOMETRY_HEADERS_LINE_H_
#include "i_shape.h"
#include <memory>

namespace geometry {

class IShape;
class Segment;
class Vector;
class Point;

class Line : public IShape {
 private:
  std::unique_ptr<Point> start_a_, start_b_;
  int64_t a_, b_, c_;

 public:
  Line(const Point& a, const Point& b);

  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;

  void CalculateEquation(const Point& first, const Point& second);
  int64_t InsertPointInEquation(const Point& point) const;
  bool DoesIntersectWithLine(const Line& line) const;
  bool IsParallelWith(const Line& line) const;
};

}  // namespace geometry
#endif