#include "uniforms.h"

#include <stdexcept>

#include "../../../core/math/basis.h"
#include "../../../core/service/service.h"

namespace s21::render::uniforms {

UniformMatrix::UniformMatrix() : m_matrix() { m_matrix.SetToIdentity(); }

const s21::matrix::Matrix4x4& UniformMatrix::GetMatrix() const {
  return m_matrix;
}

QMatrix4x4 UniformMatrix::GetMatrixQT() const {
  QMatrix4x4 qmatrix;
  for (int i = 0; i < s21::matrix::Matrix4x4::kMatrixDimention; i++) {
    for (int j = 0; j < s21::matrix::Matrix4x4::kMatrixDimention; j++) {
      qmatrix(i, j) = s21::service::converters::DoubleToFloat(m_matrix(i, j));
    }
  }
  return qmatrix;
}

void TransformationMatrix::Reset() { m_matrix.SetToIdentity(); }

void TransformationMatrix::RotateX(float degrees) {
  m_matrix.Rotate(degrees, s21::basis::kBasisVectorX);
}

void TransformationMatrix::RotateY(float degrees) {
  m_matrix.Rotate(degrees, s21::basis::kBasisVectorY);
}

void TransformationMatrix::RotateZ(float degrees) {
  m_matrix.Rotate(degrees, s21::basis::kBasisVectorZ);
}

void TransformationMatrix::Translate(float x, float y, float z) {
  m_matrix.Translate(s21::vectors::Vec3(x, y, z));
}

void TransformationMatrix::Scale(float scale) { m_matrix.Scale(scale); }

CameraMatrix::CameraMatrix() { Reset(); }

void CameraMatrix::Reset(s21::vectors::Vec3 vec) {
  m_matrix.SetToIdentity();
  m_matrix.Translate(vec);
}

ProjectionMatrix::ProjectionMatrix() { m_matrix.SetToIdentity(); }

/**
 * @note Using "magic numbers" can't be avoided here.
 */
void ProjectionMatrix::ResetCentral(double w, double h, double fov_angle,
                             double near_plane, double far_plane) {
  fov_angle = s21::matrix::DegreesToRadians(fov_angle);
  double tan = std::tan(fov_angle / 2.0f);
  double ratio = w / (h > 0 ? h : 1.0f);
  s21::matrix::Matrix local(s21::matrix::Matrix4x4::kMatrixDimention,
                            s21::matrix::Matrix4x4::kMatrixDimention);

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
void ProjectionMatrix::ResetOrthographic(double w, double h, double projection_zone_size, double near_plane, double far_plane){
  double ratio = w / (h > 0 ? h : 1.0f);
  double right=projection_zone_size*ratio;
  double left=-right;
  double top=projection_zone_size;
  double bottom=-top;
  s21::matrix::Matrix local(s21::matrix::Matrix4x4::kMatrixDimention,
                            s21::matrix::Matrix4x4::kMatrixDimention);
          
  local(0, 0) = 2.0f / (right-left);
  local(0, 1) = 0;
  local(0, 2) = 0;
  local(0, 3) = (right+left)/(left-right);

  local(1, 0) = 0;
  local(1, 1) = 2.0f / (top-bottom);
  local(1, 2) = 0;
  local(1, 3) = (top+bottom)/(bottom-top);

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

}  // namespace s21::render::uniforms