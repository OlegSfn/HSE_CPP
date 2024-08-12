#ifndef GEOMETRY_HEADERS_VECTOR_H_
#define GEOMETRY_HEADERS_VECTOR_H_

#include <string>

namespace geometry {

class Point;

class Vector {
 private:
  int x_;
  int y_;

  friend Vector operator+(const Vector &a, const Vector &b);
  friend Vector operator-(const Vector &a, const Vector &b);

  friend Vector operator+(const Vector &a);
  friend Vector operator-(const Vector &a);

  friend Vector operator*(const Vector &a, const int b);
  friend Vector operator*(const int a, const Vector &b);

  friend Vector operator/(const Vector &a, const int b);

  friend Vector &operator+=(Vector &a, const Vector &b);
  friend Vector &operator-=(Vector &a, const Vector &b);

  friend Vector &operator*=(Vector &a, const int b);

  friend Vector &operator/=(Vector &a, const int b);

  friend Point &operator+=(Point &a, const Vector &b);

  friend class Point;

 public:
  Vector(int x, int y);
  explicit Vector(const Point &point);
  std::string ToString() const;

  int DotProductWith(const Vector &vector) const;
  int CrossProductWith(const Vector &vector) const;
  size_t GetLengthSqr() const;
};

}  // namespace geometry
#endif
