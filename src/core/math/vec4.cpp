#include "vec4.h"

namespace vectors {

Vec4 Vec4::operator*(double number) const {
  return Vec4(x * number, y * number, z * number, w * number);
}

Vec4 operator*(double number, const Vec4 &vec) {
  return Vec4(vec.x * number, vec.y * number, vec.z * number, vec.w * number);
}

Vec4 &Vec4::operator*=(double number) {
  x *= number;
  y *= number;
  z *= number;
  w *= number;
  return *this;
}

Vec4 Vec4::operator-(const Vec4 &vec) const {
  return Vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

Vec4 &Vec4::operator-=(const Vec4 &vec) {
  x -= vec.x;
  y -= vec.y;
  z -= vec.z;
  w -= vec.w;
  return *this;
}

Vec4 Vec4::operator+(const Vec4 &vec) const {
  return Vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

Vec4 &Vec4::operator+=(const Vec4 &vec) {
  x += vec.x;
  y += vec.y;
  z += vec.z;
  w += vec.w;
  return *this;
}

Vec4 &Vec4::operator=(const Vec4 &vec) {
  x = vec.x;
  y = vec.y;
  z = vec.z;
  w = vec.w;
  return *this;
}

bool Vec4::operator==(const Vec4 &vec) const {
  return (x == vec.x && y == vec.y && z == vec.z && w == vec.w);
}

bool Vec4::operator!=(const Vec4 &vec) const { return !(*this == vec); }
}  // namespace vectors