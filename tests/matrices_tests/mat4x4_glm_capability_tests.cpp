#include <gtest/gtest.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iomanip>
#include <iostream>
#include <string>

#include "core/math/mat4x4.h"
#include "core/math/vectors.h"

namespace {

constexpr double kEpsilon = 1e-7;

}  // namespace

namespace glmatrix {
namespace test {

void PrintRawS21Matrix(Mat4& mat) {
    std::cout << "\nRaw S21Matrix memory (" << 4 << "x" << 4 << "):\n";
    double* x = &mat(0, 0);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << "Address[" << i << "," << j << "]: " << *x
                      << " Value: " << mat(i, j) << "\n";
            ++x;
        }
    }
}

void PrintRawGLMMatrix(glm::dmat4& mat) {
    std::cout << "\nRaw GLM Matrix memory:\n";
    double* x = glm::value_ptr(mat);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << "Address[" << i << "," << j << "]: " << *x
                      << " Value: " << mat[i][j] << "\n";
            ++x;
        }
    }
}

void CompareMatrices(const Mat4& mat, const glm::dmat4& glm_mat) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            auto a = mat(i, j);
            auto b = glm_mat[i][j];
            EXPECT_NEAR(static_cast<float>(a), static_cast<float>(b), kEpsilon)
                << "Mismatch at (" << i << ", " << j << ")";
        }
    }
}

void CompareVectors(const Mat4& vec, const glm::dvec4& glm_vec) {
    for (int i = 0; i < 4; ++i) {
        EXPECT_NEAR(vec(i, 0), glm_vec[i], kEpsilon) << "Mismatch at index " << i;
    }
}

void PrintMat4(const glmatrix::Mat4& mat4x4,
               const std::string& label = "glmatrix::Mat4") {
    std::cout << "\n" << label << ":\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << std::setw(12) << std::setprecision(6) << std::fixed
                      << mat4x4(j, i);
        }
        std::cout << "\n";
    }
}

void PrintGLM(const glm::mat4& mat4x4, const std::string& label = "glm::mat4") {
    std::cout << "\n" << label << ":\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << std::setw(12) << std::setprecision(6) << std::fixed
                      << mat4x4[j][i];
        }
        std::cout << "\n";
    }
}

void PrintMatrix(const Mat4& mat, const std::string& name) {
    std::cout << "\n" << name << ":\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << std::setw(12) << mat(i, j);
        }
        std::cout << "\n";
    }
}

TEST(Mat4Test, IdentityMatrix) {
    Mat4 mat = Mat4::Identity();

    EXPECT_DOUBLE_EQ(mat(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(mat(2, 2), 1.0);
    EXPECT_DOUBLE_EQ(mat(3, 3), 1.0);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i != j) {
                EXPECT_DOUBLE_EQ(mat(i, j), 0.0);
            }
        }
    }
}

TEST(Mat4Test, RadiansConversion) {
    EXPECT_NEAR(Radians(0.0), 0.0, kEpsilon);
    EXPECT_NEAR(Radians(90.0), M_PI / 2, kEpsilon);
    EXPECT_NEAR(Radians(180.0), M_PI, kEpsilon);
    EXPECT_NEAR(Radians(360.0), 2 * M_PI, kEpsilon);
    EXPECT_NEAR(Radians(-45.0), -M_PI / 4, kEpsilon);
}

TEST(Mat4Test, NormalizeVector) {
    math_structs::Vec3 vec{3.0, 0.0, 0.0};
    auto norm = Normalize(vec);

    EXPECT_NEAR(norm.x, 1.0, kEpsilon);
    EXPECT_NEAR(norm.y, 0.0, kEpsilon);
    EXPECT_NEAR(norm.z, 0.0, kEpsilon);

    math_structs::Vec3 zero{0.0, 0.0, 0.0};
    auto default_norm = Normalize(zero);
    EXPECT_NEAR(default_norm.y, 1.0, kEpsilon);
}

TEST(Mat4Test, Translation) {
    Mat4 mat = Mat4::Identity();
    math_structs::Vec3 translation{1.0, 2.0, 3.0};

    Mat4 translated = Translate(mat, translation);

    EXPECT_DOUBLE_EQ(translated(3, 0), 1.0);
    EXPECT_DOUBLE_EQ(translated(3, 1), 2.0);
    EXPECT_DOUBLE_EQ(translated(3, 2), 3.0);
    EXPECT_DOUBLE_EQ(translated(3, 3), 1.0);

    glm::dmat4 glm_mat = glm::translate(
        glm::dmat4(1.0),
        glm::dvec3(translation.x, translation.y, translation.z));
    CompareMatrices(translated, glm_mat);
}

TEST(Mat4Test, Scale) {
    Mat4 mat = Mat4::Identity();
    math_structs::Vec3 scale{2.0, 3.0, 4.0};

    Mat4 scaled = Scale(mat, scale);

    EXPECT_DOUBLE_EQ(scaled(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(scaled(1, 1), 3.0);
    EXPECT_DOUBLE_EQ(scaled(2, 2), 4.0);
    EXPECT_DOUBLE_EQ(scaled(3, 3), 1.0);

    EXPECT_DOUBLE_EQ(scaled(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(scaled(1, 0), 0.0);
}

TEST(Mat4Test, RotationX) {
    const double angle = Radians(45.0);
    Mat4 mat = Mat4::Identity();
    math_structs::Vec3 axis{1.0, 0.0, 0.0};

    Mat4 rotated = Rotate(mat, angle, axis);

    glm::dmat4 glm_rot = glm::rotate(glm::dmat4(1.0), angle,
                                     glm::dvec3(axis.x, axis.y, axis.z));

    CompareMatrices(rotated, glm_rot);
}

TEST(Mat4Test, RotationY) {
    const double angle = Radians(30.0);
    Mat4 mat = Mat4::Identity();
    math_structs::Vec3 axis{0.0, 1.0, 0.0};

    Mat4 rotated = Rotate(mat, angle, axis);
    glm::dmat4 glm_rot = glm::rotate(glm::dmat4(1.0), angle,
                                     glm::dvec3(axis.x, axis.y, axis.z));
    CompareMatrices(rotated, glm_rot);
}

TEST(Mat4Test, RotationZ) {
    const double angle = Radians(60.0);
    Mat4 mat = Mat4::Identity();
    math_structs::Vec3 axis{0.0, 0.0, 1.0};

    Mat4 rotated = Rotate(mat, angle, axis);
    glm::dmat4 glm_rot = glm::rotate(glm::dmat4(1.0), angle,
                                     glm::dvec3(axis.x, axis.y, axis.z));
    CompareMatrices(rotated, glm_rot);
}

TEST(Mat4Test, CombinedTransformations) {
    Mat4 mat = Mat4::Identity();
    math_structs::Vec3 trans{1.0, 2.0, 3.0};
    math_structs::Vec3 scale{2.0, 3.0, 4.0};
    double angle = Radians(45.0);
    math_structs::Vec3 axis{1.0, 1.0, 0.0};

    Mat4 transformed = Translate(mat, trans);
    transformed = Scale(transformed, scale);
    transformed = Rotate(transformed, angle, axis);

    EXPECT_NEAR(transformed(3, 3), 1.0, kEpsilon);

    glm::dmat4 glm_mat = glm::translate(
        glm::dmat4(1.0), glm::dvec3(trans.x, trans.y, trans.z));
    glm_mat = glm::scale(glm_mat, glm::dvec3(scale.x, scale.y, scale.z));
    glm_mat = glm::rotate(glm_mat, angle,
                          glm::normalize(glm::dvec3(axis.x, axis.y, axis.z)));

    CompareMatrices(transformed, glm_mat);
}

TEST(Mat4Test, MatrixMultiplication) {
    Mat4 a = Mat4::Identity();
    Mat4 b = Mat4::Identity();

    a(0, 0) = 2.0;
    b(1, 1) = 3.0;

    Mat4 c = a * b;

    EXPECT_DOUBLE_EQ(c(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 3.0);
    EXPECT_DOUBLE_EQ(c(2, 2), 1.0);
    EXPECT_DOUBLE_EQ(c(3, 3), 1.0);
}

TEST(Mat4Test, ZeroVectorNormalize) {
    math_structs::Vec3 zero{0.0, 0.0, 0.0};
    auto result = Normalize(zero);

    EXPECT_DOUBLE_EQ(result.x, 0.0);
    EXPECT_DOUBLE_EQ(result.y, 1.0);
    EXPECT_DOUBLE_EQ(result.z, 0.0);
}

}  // namespace test
}  // namespace glmatrix
