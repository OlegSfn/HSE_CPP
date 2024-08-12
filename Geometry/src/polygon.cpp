#include "../polygon.h"
#include "../segment.h"
#include "../point.h"
#include "../ray.h"
#include <memory>
#include <utility>
#include <vector>

namespace geometry {

Polygon::Polygon(std::vector<Point> points) : points_(std::move(points)) {
}

IShape &Polygon::Move(const Vector &vector) {
  for (auto &point : points_) {
    point += vector;
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point &point) const {
  for (auto &vertex : points_) {
    if (vertex == point) {
      return true;
    }
  }

  Point rayDirPoint(Point(point.x_ + 900000, point.y_ + 1));
  Ray ray(point, rayDirPoint);

  int intersectionsCounter = 0;
  for (size_t i = 0; i < points_.size(); ++i) {
    Segment segment(points_[i], points_[(i + 1) % points_.size()]);
    if (segment.ContainsPoint(point)) {
      return true;
    }
    intersectionsCounter += ray.CrossesSegment(segment);
  }

  return intersectionsCounter % 2 == 1;
}
bool Polygon::CrossesSegment(const Segment &segment) const {
  for (size_t i = 0; i < points_.size() - 1; ++i) {
    Segment polygonSegment(points_[i], points_[i + 1]);
    if (segment.CrossesSegment(polygonSegment)) {
      return true;
    }
  }

  return false;
}
std::unique_ptr<IShape> Polygon::Clone() const {
  return std::make_unique<Polygon>(std::vector<Point>(points_));
}
std::string Polygon::ToString() const {
  std::string result = "Polygon(";
  for (size_t i = 0; i < points_.size(); ++i) {
    if (i != points_.size() - 1) {
      result += points_[i].ToString() + ", ";
    } else {
      return result += points_[i].ToString() + ")";
    }
  }

  return "Polygon()";
}

}  // namespace geometry