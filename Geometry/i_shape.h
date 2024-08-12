#ifndef GEOMETRY_HEADERS_ISHAPE_H_
#define GEOMETRY_HEADERS_ISHAPE_H_
#include <string>
#include <memory>

namespace geometry {

class Segment;
class Vector;
class Point;

class IShape {
 public:
  virtual ~IShape() = default;
  virtual IShape& Move(const Vector& vector) = 0;
  virtual bool ContainsPoint(const Point& point) const = 0;
  virtual bool CrossesSegment(const Segment& segment) const = 0;
  virtual std::unique_ptr<IShape> Clone() const = 0;
  virtual std::string ToString() const = 0;
};

}  // namespace geometry
#endif