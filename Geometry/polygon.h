#ifndef GEOMETRY_HEADERS_POLYGON_H_
#define GEOMETRY_HEADERS_POLYGON_H_
#include "i_shape.h"
#include <vector>
#include <memory>

namespace geometry {

class IShape;
class Point;
class Segment;
class Vector;

class Polygon : public IShape {
 private:
  std::vector<Point> points_;

 public:
  explicit Polygon(std::vector<Point> points);

  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};

}  // namespace geometry
#endif