#ifndef SRC_MODEL_RENDER_UNIFORMS_H
#define SRC_MODEL_RENDER_UNIFORMS_H

#include <QMatrix4x4>

#include "../../../core/math/matrix4x4.h"
namespace s21::render::uniforms {

class UniformMatrix {
 public:
  UniformMatrix();
  virtual ~UniformMatrix() = default;

  const s21::matrix::Matrix4x4& GetMatrix() const;
  QMatrix4x4 GetMatrixQT() const;

 protected:
  s21::matrix::Matrix4x4 m_matrix;
};

/**
 * @note Interestingly it's not the best way of realization of this.
 * The thing is that storing the Transformation matrix as matrix, changing it
 * every time result in floating-point error accumulation (best seen in
 * scaling). Simply speaking multiplication over and over again result in
 * collecting floating-point numbers approximations. Best way to avoid it would
 * be storing all changes as separate munbers (double rotX, double rotY, double
 * rotZ, s21::vectors::Vec3 translation, double scale) and every time the matrix
 * is needed Reset() it and do all the needed changes to it again.
 * @note Keeping this particular realization is not that troublemaking for this
 * project, but these is a room to grow is better accuracy will be required.
 */
class TransformationMatrix : public UniformMatrix {
 public:
  TransformationMatrix() = default;

  void Reset();
  void RotateX(float degrees);
  void RotateY(float degrees);
  void RotateZ(float degrees);
  void Translate(float x, float y, float z);
  void Scale(float scale);
};

class CameraMatrix : public UniformMatrix {
 public:
  CameraMatrix();
  void Reset(s21::vectors::Vec3 vec = kDefaultCamera);

 private:
  static constexpr s21::vectors::Vec3 kDefaultCamera{0.0f, 0.0f, -5.0f};
};

class ProjectionMatrix : public UniformMatrix {
 public:
  ProjectionMatrix();
  void ResetCentral(double w, double h, double fov_angle = kFovAngle,
                    double near_plane = kNearPlane,
                    double far_plane = kFarPlane);
  void ResetOrthographic(double w, double h,
                         double projection_zone_size = kProjectionCubeSize,
                         double near_plane = kNearPlane,
                         double far_plane = kFarPlane);

 private:
  static constexpr double kFovAngle = 45.0f;
  static constexpr double kNearPlane = 0.1f;
  static constexpr double kFarPlane = 100.0f;
  static constexpr double kProjectionCubeSize = 2.0f;
};

}  // namespace s21::render::uniforms

#endif  // SRC_MODEL_RENDER_UNIFORMS_H