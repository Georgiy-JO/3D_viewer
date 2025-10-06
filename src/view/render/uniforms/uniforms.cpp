#include "uniforms.h"

#include <stdexcept>

#include "../../../core/math/basis.h"
#include "../../../core/service/service.h"

namespace render::uniforms {

UniformMatrix::UniformMatrix() : m_matrix() { m_matrix.SetToIdentity(); }
UniformMatrix::UniformMatrix(const matrix::Matrix4x4& matrix_)
    : m_matrix(matrix_) {}

const matrix::Matrix4x4& UniformMatrix::GetMatrix() const { return m_matrix; }

QMatrix4x4 UniformMatrix::GetMatrixQT() const {
  QMatrix4x4 qmatrix;
  for (int i = 0; i < matrix::Matrix4x4::kMatrixDimention; i++) {
    for (int j = 0; j < matrix::Matrix4x4::kMatrixDimention; j++) {
      qmatrix(i, j) = service::converters::DoubleToFloat(m_matrix(i, j));
    }
  }
  return qmatrix;
}

void TransformationMatrix::Reset() { m_matrix.SetToIdentity(); }

void TransformationMatrix::RotateX(float degrees) {
  m_matrix.Rotate(degrees, basis::kBasisVectorX);
}

void TransformationMatrix::RotateY(float degrees) {
  m_matrix.Rotate(degrees, basis::kBasisVectorY);
}

void TransformationMatrix::RotateZ(float degrees) {
  m_matrix.Rotate(degrees, basis::kBasisVectorZ);
}

void TransformationMatrix::Translate(float x, float y, float z) {
  m_matrix.Translate(vectors::Vec3(x, y, z));
}

void TransformationMatrix::Scale(float scale) { m_matrix.Scale(scale); }

CameraMatrix::CameraMatrix() { Reset(); }

void CameraMatrix::Reset(vectors::Vec3 vec) {
  m_matrix.SetToIdentity();
  m_matrix.Translate(vec);
}

ProjectionMatrix::ProjectionMatrix() { m_matrix.SetToIdentity(); }

/**
 * @note Using "magic numbers" can't be avoided here.
 */
void ProjectionMatrix::ResetCentral(double w, double h, double fov_angle,
                                    double near_plane, double far_plane) {
  fov_angle = matrix::DegreesToRadians(fov_angle);
  double tan = std::tan(fov_angle / 2.0f);
  double ratio = w / (h > 0 ? h : 1.0f);
  matrix::Matrix local(matrix::Matrix4x4::kMatrixDimention,
                       matrix::Matrix4x4::kMatrixDimention);

  local(0, 0) = 1.0f / (ratio * tan);
  local(0, 1) = 0;
  local(0, 2) = 0;
  local(0, 3) = 0;

  local(1, 0) = 0;
  local(1, 1) = 1.0f / (tan);
  local(1, 2) = 0;
  local(1, 3) = 0;

  local(2, 0) = 0;
  local(2, 1) = 0;
  local(2, 2) = (far_plane + near_plane) / (near_plane - far_plane);
  local(2, 3) = 2 * far_plane * near_plane / (near_plane - far_plane);

  local(3, 0) = 0;
  local(3, 1) = 0;
  local(3, 2) = -1;
  local(3, 3) = 0;

  m_matrix = local;
}

/**
 * @note Using "magic numbers" can't be avoided here.
 */
void ProjectionMatrix::ResetOrthographic(double w, double h,
                                         double projection_zone_size,
                                         double near_plane, double far_plane) {
  double ratio = w / (h > 0 ? h : 1.0f);
  double right = projection_zone_size * ratio;
  double left = -right;
  double top = projection_zone_size;
  double bottom = -top;
  matrix::Matrix local(matrix::Matrix4x4::kMatrixDimention,
                       matrix::Matrix4x4::kMatrixDimention);

  local(0, 0) = 2.0f / (right - left);
  local(0, 1) = 0;
  local(0, 2) = 0;
  local(0, 3) = (right + left) / (left - right);

  local(1, 0) = 0;
  local(1, 1) = 2.0f / (top - bottom);
  local(1, 2) = 0;
  local(1, 3) = (top + bottom) / (bottom - top);

  local(2, 0) = 0;
  local(2, 1) = 0;
  local(2, 2) = 2.0f / (near_plane - far_plane);
  local(2, 3) = (far_plane + near_plane) / (near_plane - far_plane);

  local(3, 0) = 0;
  local(3, 1) = 0;
  local(3, 2) = 0;
  local(3, 3) = 1.0f;

  m_matrix = local;
}

}  // namespace render::uniforms