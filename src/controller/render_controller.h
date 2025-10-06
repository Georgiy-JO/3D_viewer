#ifndef SRC_CONTROLLER_RENDER_CONTROLLER_H
#define SRC_CONTROLLER_RENDER_CONTROLLER_H
#include "../core/parameters/view_parameters.h"
#include "../model/render/gui_model.h"
#include "../model/render/shader_program.h"

namespace controller {
class Render {
 public:
  using EdgeKinds = parameters::ViewParameters::EdgeKind;
  using VertexKinds = parameters::ViewParameters::VertexKind;
  using ProjectionKinds = parameters::ViewParameters::ProjectionKind;

  render::GPU_Model& Model() { return m_model; }
  const render::GPU_Model& Model() const { return m_model; }
  render::uniforms::TransformationMatrix& Transform() {
    return m_transformation_matrix;
  }
  const render::uniforms::TransformationMatrix& Transform() const {
    return m_transformation_matrix;
  }
  render::uniforms::CameraMatrix& Camera() { return m_camera_matrix; }
  const render::uniforms::CameraMatrix& Camera() const {
    return m_camera_matrix;
  }
  render::uniforms::ProjectionMatrix& Projection() {
    return m_projection_matrix;
  }
  const render::uniforms::ProjectionMatrix& Projection() const {
    return m_projection_matrix;
  }
  render::ShaderProgram& Program() { return m_program; }
  const render::ShaderProgram& Program() const { return m_program; }
  parameters::ViewParameters& Parameters() { return m_parameters; }
  const parameters::ViewParameters& Parameters() const {
    return m_parameters;
  }

  void SetUniforms() {
    m_program.UploadUniforms(
        render::uniforms::UniformMatrix(m_projection_matrix.GetMatrix()*m_camera_matrix.GetMatrix()*m_transformation_matrix.GetMatrix()),
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
  render::GPU_Model m_model;
  render::uniforms::TransformationMatrix m_transformation_matrix;
  render::uniforms::CameraMatrix m_camera_matrix;
  render::uniforms::ProjectionMatrix m_projection_matrix;
  render::ShaderProgram m_program;
  parameters::ViewParameters m_parameters;
};
}  // namespace controller

#endif  // SRC_CONTROLLER_RENDER_CONTROLLER_H