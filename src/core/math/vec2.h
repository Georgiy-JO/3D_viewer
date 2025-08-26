#ifndef SRC_CORE_MATH_VEC2_H
#define SRC_CORE_MATH_VEC2_H

namespace s21::vectors {

struct Vec2 {
  double x=0.0f;
  double y=0.0f;

  constexpr Vec2()=default;
  constexpr Vec2(double x_,double y_):x(x_),y(y_){}
  ~Vec2()=default;
};

}  // namespace s21::vectors

#endif  // SRC_CORE_MATH_VEC2_H