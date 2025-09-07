#include "vec3.h"

#include <cmath>

namespace s21::vectors {
Vec3 Vec3::operator*(double number) const {
  return Vec3(x * number, y * number, z * number);
}

Vec3 operator*(double number, const Vec3 &vec) {
  return Vec3(vec.x * number, vec.y * number, vec.z * number);
}

Vec3 &Vec3::operator*=(double number) {
  x *= number;
  y *= number;
  z *= number;
  return *this;
}

Vec3 Vec3::operator-(const Vec3 &vec) const {
  return Vec3(x - vec.x, y - vec.y, z - vec.z);
}

Vec3 &Vec3::operator-=(const Vec3 &vec) {
  x -= vec.x;
  y -= vec.y;
  z -= vec.z;
  return *this;
}

Vec3 Vec3::operator+(const Vec3 &vec) const {
  return Vec3(x + vec.x, y + vec.y, z + vec.z);
}

Vec3 &Vec3::operator+=(const Vec3 &vec) {
  x += vec.x;
  y += vec.y;
  z += vec.z;
  return *this;
}

Vec3 &Vec3::operator=(const Vec3 &vec) {
  x = vec.x;
  y = vec.y;
  z = vec.z;
  return *this;
}

bool Vec3::operator==(const Vec3 &vec) const {
  return (x == vec.x && y == vec.y && z == vec.z);
}

bool Vec3::operator!=(const Vec3 &vec) const { return !(*this == vec); }

/**
 * @note Using "magic numbers" can't be avoided here.
 */
Vec3 Vec3::operator--() {
  *this -= Vec3(1, 1, 1);
  return *this;
}

/**
 * @note Using "magic numbers" can't be avoided here.
 */
Vec3 Vec3::operator++() {
  *this += Vec3(1, 1, 1);
  return *this;
}

/**
 * @note Using "magic numbers" can't be avoided here.
 */
Vec3 Vec3::operator--(int) {
  Vec3 tmp = *this;
  *this -= Vec3(1, 1, 1);
  return tmp;
}

/**
 * @note Using "magic numbers" can't be avoided here.
 */
Vec3 Vec3::operator++(int) {
  Vec3 tmp = *this;
  *this += Vec3(1, 1, 1);
  return tmp;
}

void Vec3::Normalize() {
  double length = std::sqrt(x * x + y * y + z * z);
  if (length != 0) {
    x /= length;
    y /= length;
    z /= length;
  }
}

}  // namespace s21::vectors
