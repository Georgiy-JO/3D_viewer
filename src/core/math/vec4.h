#ifndef SRC_CORE_MATH_VEC4_H
#define SRC_CORE_MATH_VEC4_H

namespace s21::vectors {
struct Vec4 {
  double x = 0.0f;
  double y = 0.0f;
  double z = 0.0f;
  double w = 0.0f;

  constexpr Vec4()=default;
  constexpr explicit Vec4(double value): x(value), y(value), z(value), w(value) {}
  constexpr Vec4(double x_, double y_, double z_, double w_) : x(x_), y(y_), z(z_), w(w_) {}
  ~Vec4() = default;

  Vec4 operator*(double number) const;
  friend Vec4 operator*(double number, const Vec4 &vec);
  Vec4 &operator*=(double number);
  Vec4 operator-(const Vec4 &vec) const;
  Vec4 &operator-=(const Vec4 &vec);
  Vec4 operator+(const Vec4 &vec) const;
  Vec4 &operator+=(const Vec4 &vec);
  Vec4 &operator=(const Vec4 &vec);
  bool operator==(const Vec4 &vec) const;
  bool operator!=(const Vec4 &vec) const;
};
}  // namespace s21::vectors

#endif  // SRC_CORE_MATH_VEC4_H