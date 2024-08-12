#ifndef GEOMETRY_HEADERS_RAY_H_
#define GEOMETRY_HEADERS_RAY_H_
#include <memory>
namespace geometry {

class IShape;
class Point;
class Segment;
class Vector;

class Ray : public IShape {
 private:
  std::unique_ptr<Point> start_a_, start_b_;

 public:
  Ray(const Point& a, const Point& b);

  IShape& Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossesSegment(const Segment& segment) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};

}  // namespace geometry
#endif