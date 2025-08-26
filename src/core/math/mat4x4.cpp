#include "mat4x4.h"
#include "vec3.h"

#include <cmath>
#include <cassert>

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kDegToRad = kPi / 180.0;
constexpr double kRadToDeg = 180.0 / kPi;
}  // namespace

namespace s21::glmatrix {

double Radians(double degrees) {
    return degrees * kDegToRad;
}

double Degrees(double radians) {
    return radians * kRadToDeg;
}

vectors::Vec3 Normalize(const vectors::Vec3& vec) {
    const double mul = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
    const double length = std::sqrt(mul);

    if (length > 0.0) {
        return vectors::Vec3(vec.x / length, vec.y / length, vec.z / length);
    }
    return vectors::Vec3(0.0, 1.0, 0.0);
}

Mat4 Translate(const Mat4& mat4x4, const vectors::Vec3& vec) {
    Mat4 translation_matrix(mat4x4);
    translation_matrix(3, 0) = vec.x;
    translation_matrix(3, 1) = vec.y;
    translation_matrix(3, 2) = vec.z;
    return translation_matrix;
}

Mat4 Scale(Mat4& mat4x4, const vectors::Vec3& vec) {
    Mat4 scale_matrix(mat4x4);
    scale_matrix(0, 0) = vec.x;
    scale_matrix(1, 1) = vec.y;
    scale_matrix(2, 2) = vec.z;
    return scale_matrix;
}

Mat4 Rotate(Mat4& mat4x4, double angle, const vectors::Vec3& vec) {
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    const vectors::Vec3 axis = Normalize(vec);
    const float t = 1.0 - c;

    Mat4 rotation;
    rotation(0, 0) = c + axis.x * axis.x * t;
    rotation(0, 1) = axis.y * axis.x * t + axis.z * s;
    rotation(0, 2) = axis.z * axis.x * t - axis.y * s;
    rotation(0, 3) = 0.0;

    rotation(1, 0) = axis.x * axis.y * t - axis.z * s;
    rotation(1, 1) = c + axis.y * axis.y * t;
    rotation(1, 2) = axis.z * axis.y * t + axis.x * s;
    rotation(1, 3) = 0.0;

    rotation(2, 0) = axis.x * axis.z * t + axis.y * s;
    rotation(2, 1) = axis.y * axis.z * t - axis.x * s;
    rotation(2, 2) = c + axis.z * axis.z * t;
    rotation(2, 3) = 0.0;

    rotation(3, 0) = 0.0;
    rotation(3, 1) = 0.0;
    rotation(3, 2) = 0.0;
    rotation(3, 3) = 1.0;

    return rotation * mat4x4;
}

Mat4::Mat4() : m_mat4x4(4, 4) {
    IdentityMatrix();
}

double Mat4::operator()(int row, int col) const {
    return m_mat4x4(row, col);
}

double& Mat4::operator()(int row, int col) {
    return m_mat4x4(row, col);
}

Mat4 Mat4::operator*(const Mat4& other) {
    return Mat4(m_mat4x4 * other.m_mat4x4);
}

Mat4 Mat4::operator+(const Mat4& other) const {
    return Mat4(m_mat4x4 + other.m_mat4x4);
}

Mat4 Mat4::operator-(const Mat4& other) const {
    return Mat4(m_mat4x4 - other.m_mat4x4);
}

void Mat4::IdentityMatrix() {
    m_mat4x4(0, 0) = 1.0;
    m_mat4x4(1, 1) = 1.0;
    m_mat4x4(2, 2) = 1.0;
    m_mat4x4(3, 3) = 1.0;
}

Mat4 Mat4::Identity(double val) {
    Mat4 result;
    result(0, 0) = val;
    result(1, 1) = val;
    result(2, 2) = val;
    result(3, 3) = val;
    return result;
}

Mat4::Mat4(const s21::S21Matrix& other) : m_mat4x4(other) {}

}  // namespace glmatrix
