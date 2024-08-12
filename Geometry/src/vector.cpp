#include "../vector.h"
#include "../point.h"

namespace geometry {

std::string Vector::ToString() const {
  return "Vector(" + std::to_string(static_cast<int>(x_)) + ", " + std::to_string(static_cast<int>(y_)) + ")";
}
Vector::Vector(int x, int y) {
  this->x_ = x;
  this->y_ = y;
}
Vector operator+(const Vector &a, const Vector &b) {
  return {a.x_ + b.x_, a.y_ + b.y_};
}
Vector operator-(const Vector &a, const Vector &b) {
  return {a.x_ - b.x_, a.y_ + b.y_};
}
Vector operator+(const Vector &a) {
  return {a.x_, a.y_};
}
Vector operator-(const Vector &a) {
  return {-a.x_, -a.y_};
}
Vector operator*(const Vector &a, const int b) {
  return {a.x_ * b, a.y_ * b};
}
Vector operator*(const int a, const Vector &b) {
  return b * a;
}
Vector operator/(const Vector &a, const int b) {
  return {a.x_ / b, a.y_ / b};
}
Vector &operator+=(Vector &a, const Vector &b) {
  a.x_ += b.x_;
  a.y_ += b.y_;
  return a;
}
Vector &operator-=(Vector &a, const Vector &b) {
  return a += -b;
}
Vector &operator*=(Vector &a, const int b) {
  a.x_ *= b;
  a.y_ *= b;
  return a;
}
Vector &operator/=(Vector &a, const int b) {
  return a *= 1 / b;
}
int Vector::DotProductWith(const Vector &vector) const {
  return x_ * vector.x_ + y_ * vector.y_;
}
Vector::Vector(const Point &point) : x_(point.x_), y_(point.y_) {
}
int Vector::CrossProductWith(const Vector &vector) const {
  return x_ * vector.y_ - y_ * vector.x_;
}
size_t Vector::GetLengthSqr() const {
  return this->DotProductWith(*this);
}
}  // namespace geometry
