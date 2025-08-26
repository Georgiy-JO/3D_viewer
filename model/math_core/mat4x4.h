#pragma once

#include "../s21matrix/s21_matrix.h"
#include "Vect3.h"

// namespace glmatrix {
namespace s21 {

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
    explicit Mat4(const matrix::S21Matrix& other);
    void IdentityMatrix();

private:
    matrix::S21Matrix m_mat4x4;
};

double Radians(double degrees);
double Degrees(double radians);
Vect3 Normalize(const Vect3& vec);
Mat4 Translate(const Mat4& mat4x4, const Vect3& vec);
Mat4 Scale(Mat4& mat4x4, const Vect3& vec);
Mat4 Rotate(Mat4& mat4x4, double angle /* radians */, const Vect3& vec);

}  // namespace s21
// namespace glmatrix

