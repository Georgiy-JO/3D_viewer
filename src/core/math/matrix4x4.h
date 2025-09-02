#ifndef SRC_CORE_MATH_MATRIX4X4_H
#define SRC_CORE_MATH_MATRIX4X4_H
#include "../../third_party/s21_matrix/matrix.hpp"
#include "vec3.h"

namespace s21::matrix
{
    using namespace s21::vectors;
    constexpr double kStraightAngle =180.0f;
    class Matrix4x4{
        public:
            static constexpr double kMinialScale =0.0001;
            static constexpr int kMatrixDimention = 4;

            Matrix4x4();
            Matrix4x4(const Matrix4x4& other);
            Matrix4x4(const Matrix& other);

            void SetToIdentity();
            void Translate(const Vec3& vec);
            // angle in degrees
            void Rotate(double angle, Vec3 vec);
            void Scale(double scale);
            
            Matrix4x4 operator+(const Matrix4x4& other) const;
            Matrix4x4& operator+=(const Matrix4x4& other);
            Matrix4x4 operator-(const Matrix4x4& other) const;
            Matrix4x4& operator-=(const Matrix4x4& other);
            Matrix4x4 operator*(const Matrix4x4& other) const;
            Matrix4x4& operator*=(const Matrix4x4& other);
            Matrix4x4& operator=(const Matrix4x4& other);
            Matrix4x4& operator=(const Matrix& other);
            bool operator==(const Matrix4x4& other) const;
            bool operator!=(const Matrix4x4& other) const;
            double operator()(int row, int col)const;
            
        private:
            void MatrixDementionsCheck(const Matrix& other) const;
            Matrix m_matrix;   
    };

    double DegreesToRadians(double degrees);
    
    
} // namespace s21::matrix


#endif //SRC_CORE_MATH_MATRIX4X4_H