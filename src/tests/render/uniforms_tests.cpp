#include <gtest/gtest.h>

#include "../../view/render/uniforms/uniforms.h"

TEST(Render_Uniforms, TransformationMatrix_Basic) {
  render::uniforms::TransformationMatrix tm;

  matrix::Matrix4x4 m;
  m.SetToIdentity();
  EXPECT_EQ(m, tm.GetMatrix());

  QMatrix4x4 qm;
  qm.setToIdentity();
  EXPECT_EQ(qm, tm.GetMatrixQT());
}

TEST(Render_Uniforms, TransformationMatrix_Transformations) {
  render::uniforms::TransformationMatrix tm;

  matrix::Matrix v(4, 1);
  v(0, 0) = 5.5;
  v(1, 0) = 10.5;
  v(2, 0) = 0;
  v(3, 0) = 1;

  tm.RotateZ(90);
  tm.Scale(2);
  tm.Translate(-2.5, 0, -10);

  matrix::Matrix4x4 m4(tm.GetMatrix());

  matrix::Matrix m(4, 4);

  for (int i = 0; i < matrix::Matrix4x4::kMatrixDimention; i++) {
    for (int j = 0; j < matrix::Matrix4x4::kMatrixDimention; j++) {
      m(i, j) = m4(i, j);
    }
  }

  v = m * v;
  EXPECT_EQ(v.getCols(), 1);
  EXPECT_EQ(v.getRows(), 4);
  EXPECT_NEAR(v(0, 0), -23.5, 1e-8);
  EXPECT_NEAR(v(1, 0), 11, 1e-8);
  EXPECT_NEAR(v(2, 0), -10, 1e-8);
  EXPECT_NEAR(v(3, 0), 1, 1e-8);

  tm.Reset();
  m4 = tm.GetMatrix();
  for (int i = 0; i < matrix::Matrix4x4::kMatrixDimention; i++) {
    for (int j = 0; j < matrix::Matrix4x4::kMatrixDimention; j++) {
      m(i, j) = m4(i, j);
    }
  }
  v = m * v;
  EXPECT_EQ(v.getCols(), 1);
  EXPECT_EQ(v.getRows(), 4);
  EXPECT_NEAR(v(0, 0), -23.5, 1e-8);
  EXPECT_NEAR(v(1, 0), 11, 1e-8);
  EXPECT_NEAR(v(2, 0), -10, 1e-8);
  EXPECT_NEAR(v(3, 0), 1, 1e-8);

  tm.Reset();
  tm.RotateY(180);
  m4 = tm.GetMatrix();
  for (int i = 0; i < matrix::Matrix4x4::kMatrixDimention; i++) {
    for (int j = 0; j < matrix::Matrix4x4::kMatrixDimention; j++) {
      m(i, j) = m4(i, j);
    }
  }
  v = m * v;
  EXPECT_EQ(v.getCols(), 1);
  EXPECT_EQ(v.getRows(), 4);
  EXPECT_NEAR(v(0, 0), 23.5, 1e-8);
  EXPECT_NEAR(v(1, 0), 11, 1e-8);
  EXPECT_NEAR(v(2, 0), 10, 1e-8);
  EXPECT_NEAR(v(3, 0), 1, 1e-8);

  tm.Reset();
  tm.RotateZ(360);
  m4 = tm.GetMatrix();
  for (int i = 0; i < matrix::Matrix4x4::kMatrixDimention; i++) {
    for (int j = 0; j < matrix::Matrix4x4::kMatrixDimention; j++) {
      m(i, j) = m4(i, j);
    }
  }
  v = m * v;
  EXPECT_EQ(v.getCols(), 1);
  EXPECT_EQ(v.getRows(), 4);
  EXPECT_NEAR(v(0, 0), 23.5, 1e-8);
  EXPECT_NEAR(v(1, 0), 11, 1e-8);
  EXPECT_NEAR(v(2, 0), 10, 1e-8);
  EXPECT_NEAR(v(3, 0), 1, 1e-8);

  tm.Reset();
  tm.RotateX(360);
  m4 = tm.GetMatrix();
  for (int i = 0; i < matrix::Matrix4x4::kMatrixDimention; i++) {
    for (int j = 0; j < matrix::Matrix4x4::kMatrixDimention; j++) {
      m(i, j) = m4(i, j);
    }
  }
  v = m * v;
  EXPECT_EQ(v.getCols(), 1);
  EXPECT_EQ(v.getRows(), 4);
  EXPECT_NEAR(v(0, 0), 23.5, 1e-8);
  EXPECT_NEAR(v(1, 0), 11, 1e-8);
  EXPECT_NEAR(v(2, 0), 10, 1e-8);
  EXPECT_NEAR(v(3, 0), 1, 1e-8);
}

TEST(Render_Uniforms, CameraMatrix) {
  render::uniforms::CameraMatrix cm;

  matrix::Matrix m(4, 4);
  m(0, 0) = 1;
  m(0, 1) = 0;
  m(0, 2) = 0;
  m(0, 3) = 0;

  m(1, 0) = 0;
  m(1, 1) = 1;
  m(1, 2) = 0;
  m(1, 3) = 0;

  m(2, 0) = 0;
  m(2, 1) = 0;
  m(2, 2) = 1;
  m(2, 3) = -5.0;

  m(3, 0) = 0;
  m(3, 1) = 0;
  m(3, 2) = 0;
  m(3, 3) = 1;

  EXPECT_EQ(matrix::Matrix4x4(m), cm.GetMatrix());
}

TEST(Render_Uniforms, ProjectionMatrix) {
  render::uniforms::ProjectionMatrix pm;
  pm.ResetCentral(10, 5);
  matrix::Matrix4x4 m4(pm.GetMatrix());
  matrix::Matrix m(4, 4);

  for (int i = 0; i < matrix::Matrix4x4::kMatrixDimention; i++) {
    for (int j = 0; j < matrix::Matrix4x4::kMatrixDimention; j++) {
      m(i, j) = m4(i, j);
    }
  }

  EXPECT_NEAR(
      m(0, 0),
      1.0f / (10.0 / 5.0 * std::tan(matrix::DegreesToRadians(45.0) / 2.0)),
      1e-8);
  EXPECT_NEAR(m(0, 1), 0, 1e-8);
  EXPECT_NEAR(m(0, 2), 0, 1e-8);
  EXPECT_NEAR(m(0, 3), 0, 1e-8);

  EXPECT_NEAR(m(1, 0), 0, 1e-8);
  EXPECT_NEAR(m(1, 1), 1.0f / (std::tan(matrix::DegreesToRadians(45.0) / 2.0)),
              1e-8);
  EXPECT_NEAR(m(1, 2), 0, 1e-8);
  EXPECT_NEAR(m(1, 3), 0, 1e-8);

  EXPECT_NEAR(m(2, 0), 0, 1e-8);
  EXPECT_NEAR(m(2, 1), 0, 1e-8);
  EXPECT_NEAR(m(2, 2), (100.0 + 0.1) / (0.1 - 100.0), 1e-8);
  EXPECT_NEAR(m(2, 3), 2 * 100.0 * 0.1 / (0.1 - 100.0), 1e-8);

  EXPECT_NEAR(m(3, 0), 0, 1e-8);
  EXPECT_NEAR(m(3, 1), 0, 1e-8);
  EXPECT_NEAR(m(3, 2), -1, 1e-8);
  EXPECT_NEAR(m(3, 3), 0, 1e-8);

  pm.ResetOrthographic(10, 5);
  matrix::Matrix4x4 m5(pm.GetMatrix());

  for (int i = 0; i < matrix::Matrix4x4::kMatrixDimention; i++) {
    for (int j = 0; j < matrix::Matrix4x4::kMatrixDimention; j++) {
      m(i, j) = m5(i, j);
    }
  }
  double size = 2;
  double right = 2 * size;
  double left = -right;
  double top = size;
  double bottom = -top;
  matrix::Matrix local(matrix::Matrix4x4::kMatrixDimention,
                       matrix::Matrix4x4::kMatrixDimention);

  EXPECT_NEAR(m(0, 0), 2.0f / (right - left), 1e-8);
  EXPECT_NEAR(m(0, 1), 0, 1e-8);
  EXPECT_NEAR(m(0, 2), 0, 1e-8);
  EXPECT_NEAR(m(0, 3), (right + left) / (left - right), 1e-8);

  EXPECT_NEAR(m(1, 0), 0, 1e-8);
  EXPECT_NEAR(m(1, 1), 2.0f / (top - bottom), 1e-8);
  EXPECT_NEAR(m(1, 2), 0, 1e-8);
  EXPECT_NEAR(m(1, 3), (top + bottom) / (bottom - top), 1e-8);

  EXPECT_NEAR(m(2, 0), 0, 1e-8);
  EXPECT_NEAR(m(2, 1), 0, 1e-8);
  EXPECT_NEAR(m(2, 2), 2.0f / (0.1 - 100.0), 1e-8);
  EXPECT_NEAR(m(2, 3), (100.0 + 0.1) / (0.1 - 100.0), 1e-8);

  EXPECT_NEAR(m(3, 0), 0, 1e-8);
  EXPECT_NEAR(m(3, 1), 0, 1e-8);
  EXPECT_NEAR(m(3, 2), 0, 1e-8);
  EXPECT_NEAR(m(3, 3), 1.0f, 1e-8);
}