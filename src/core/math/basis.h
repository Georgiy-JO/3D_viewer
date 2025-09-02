#ifndef SRC_CORE_MATH_BASIS_H
#define SRC_CORE_MATH_BASIS_H
#include "vec3.h"

namespace s21::basis
{
  static constexpr s21::vectors::Vec3 kBasisVectorX {1.0f,0.0f,0.0f};
  static constexpr s21::vectors::Vec3 kBasisVectorY {0.0f,1.0f,0.0f};
  static constexpr s21::vectors::Vec3 kBasisVectorZ {0.0f,0.0f,1.0f};
}

#endif //SRC_CORE_MATH_BASIS_H
