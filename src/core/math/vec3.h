#ifndef SRC_CORE_MATH_VEC3_H
#define SRC_CORE_MATH_VEC3_H

namespace vectors {

struct Vec3 {
  double x = 0.0f;
  double y = 0.0f;
  double z = 0.0f;

  constexpr Vec3() = default;
  constexpr explicit Vec3(double value) : x(value), y(value), z(value) {}
  constexpr Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
  constexpr Vec3(const Vec3 &vec) : x(vec.x), y(vec.y), z(vec.z) {}
  ~Vec3() = default;

  void Normalize();

  Vec3 operator*(double number) const;
  friend Vec3 operator*(double number, const Vec3 &vec);
  Vec3 &operator*=(double number);
  Vec3 operator-(const Vec3 &vec) const;
  Vec3 &operator-=(const Vec3 &vec);
  Vec3 operator+(const Vec3 &vec) const;
  Vec3 &operator+=(const Vec3 &vec);
  Vec3 &operator=(const Vec3 &vec);
  bool operator==(const Vec3 &vec) const;
  bool operator!=(const Vec3 &vec) const;

  Vec3 operator--();
  Vec3 operator++();
  Vec3 operator--(int);
  Vec3 operator++(int);
};

}  // namespace vectors

#endif  // SRC_CORE_MATH_VEC3_H