#ifndef CORE_MATH_MAT4X4_H_
#define CORE_MATH_MAT4X4_H_

#include "third_party/s21matrix/s21_matrix.h"

namespace s21::vectors {
struct Vec4;
struct Vec3;
}  // namespace s21::vectors

namespace s21::glmatrix {

class Mat4 final {
public:
    Mat4();

    double& operator()(int row, int col);
    double operator()(int row, int col) const;
    Mat4 operator*(const Mat4& other);
    Mat4 operator+(const Mat4& other) const;
    Mat4 operator-(const Mat4& other) const;

    static Mat4 Identity(double val = 1.0);

private:
    explicit Mat4(const s21::S21Matrix& other);
    void IdentityMatrix();

private:
    s21::S21Matrix m_mat4x4;
};

double Radians(double degrees);
double Degrees(double radians);
vectors::Vec3 Normalize(const vectors::Vec3& vec);
Mat4 Translate(const Mat4& mat4x4, const vectors::Vec3& vec);
Mat4 Scale(Mat4& mat4x4, const vectors::Vec3& vec);
Mat4 Rotate(Mat4& mat4x4, double angle /* radians */, const vectors::Vec3& vec);

}  // namespace glmatrix

#endif  // CORE_MATH_MAT4X4_H_
