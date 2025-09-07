#ifndef SRC_CONTROLLER_RENDER_CONTROLLER_H
#define SRC_CONTROLLER_RENDER_CONTROLLER_H
#include "../core/parameters/view_parameters.h"
#include "../model/render/gui_model.h"
#include "../model/render/shader_program.h"

namespace s21::controller {
class Render {
 public:
  using EdgeKinds = s21::parameters::ViewParameters::EdgeKind;
  using VertexKinds = s21::parameters::ViewParameters::VertexKind;
  using ProjectionKinds = s21::parameters::ViewParameters::ProjectionKind;

  s21::render::GPU_Model& Model() { return m_model; }
  const s21::render::GPU_Model& Model() const { return m_model; }
  s21::render::uniforms::TransformationMatrix& Transform() {
    return m_transformation_matrix;
  }
  const s21::render::uniforms::TransformationMatrix& Transform() const {
    return m_transformation_matrix;
  }
  s21::render::uniforms::CameraMatrix& Camera() { return m_camera_matrix; }
  const s21::render::uniforms::CameraMatrix& Camera() const {
    return m_camera_matrix;
  }
  s21::render::uniforms::ProjectionMatrix& Projection() {
    return m_projection_matrix;
  }
  const s21::render::uniforms::ProjectionMatrix& Projection() const {
    return m_projection_matrix;
  }
  s21::render::ShaderProgram& Program() { return m_program; }
  const s21::render::ShaderProgram& Program() const { return m_program; }
  s21::parameters::ViewParameters& Parameters() { return m_parameters; }
  const s21::parameters::ViewParameters& Parameters() const {
    return m_parameters;
  }

  void SetUniforms() {
    m_program.UploadUniforms(
        m_transformation_matrix, m_camera_matrix, m_projection_matrix,
        m_parameters.GetModelColor(), m_parameters.GetVertexSize(),
        m_parameters.GetEdgeWidth(),
        (m_parameters.GetEdgeKind() == EdgeKinds::kDotted),
        (m_parameters.GetVertexKind() == VertexKinds::kCircle));
  }
  void SetVertexProgram() {
    m_program.SetVertexShaders();
    SetUniforms();
  }
  void SetEdgeProgram() {
    m_program.SetEdgeShaders();
    SetUniforms();
  }
  void ResetProjection(double w, double h) {
    (m_parameters.GetProjectionKind() == ProjectionKinds::kOrthographic)
        ? m_projection_matrix.ResetOrthographic(w, h)
        : m_projection_matrix.ResetCentral(w, h);
  }

 private:
  s21::render::GPU_Model m_model;
  s21::render::uniforms::TransformationMatrix m_transformation_matrix;
  s21::render::uniforms::CameraMatrix m_camera_matrix;
  s21::render::uniforms::ProjectionMatrix m_projection_matrix;
  s21::render::ShaderProgram m_program;
  s21::parameters::ViewParameters m_parameters;
};
}  // namespace s21::controller

#endif  // SRC_CONTROLLER_RENDER_CONTROLLER_H