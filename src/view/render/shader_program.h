#ifndef SRC_VIEW_RENDER_SHADER_PROGRAM_H
#define SRC_VIEW_RENDER_SHADER_PROGRAM_H

#include <QOpenGLShaderProgram>
#include <string>

#include "../../core/math/vec4.h"
#include "uniforms/uniforms.h"

namespace render {
class ShaderProgram {
 public:
  /**
   * @note Need to have active OpenGL context before calling.
   */
  void SetVertexShaders();
  void SetEdgeShaders();
  void SetShaders(const std::string& vertex_shader_path,
                  const std::string& fragment_shader_path,
                  const std::string& geometry_shader_path = "");
  void UploadUniforms(const render::uniforms::TransformationMatrix& trans_marix,
                      const render::uniforms::CameraMatrix& cam_marix,
                      const render::uniforms::ProjectionMatrix& project_matrix,
                      const vectors::Vec4& model_color,
                      const double vertex_size, const double edge_width,
                      const bool dotted_edge_switch,
                      const bool circle_vertex_switch);
  void UploadUniforms(
      const render::uniforms::UniformMatrix& combined_affect_matrix,
      const vectors::Vec4& model_color, const double vertex_size,
      const double edge_width, const bool dotted_edge_switch,
      const bool circle_vertex_switch);
  bool Bind();
  void Unbind();

  QOpenGLShaderProgram& GetProgram();

 private:
  static constexpr const char* kDefaultGlobalVertexShaderPath =
      "shaders/shader.vert";
  static constexpr const char* kDefaultVertexVertexShaderPath =
      "shaders/vertex_shader.vert";
  static constexpr const char* kDefaultEdgeVertexShaderPath =
      "shaders/edge_shader.vert";
  static constexpr const char* kDefaultEdgeGeometryShaderPath =
      "shaders/edge_shader.geom";
  static constexpr const char* kDefaultEdgeFragmentShaderPath =
      "shaders/edge_shader.frag";
  static constexpr const char* kDefaultVertexFragmentShaderPath =
      "shaders/vertex_shader.frag";
  static constexpr const char* kTransformationUniform = "mTransformation";
  static constexpr const char* kCameraUniform = "mCamera";
  static constexpr const char* kProjectionUniform = "mProjection";
  static constexpr const char* kCombinedAffectUniform = "mCombinedAffect";
  static constexpr const char* kModelColorUniform = "vModelColor";
  static constexpr const char* kVertexSizeUniform = "dVertexSize";
  static constexpr const char* kEdgeWidthUniform = "dEdgeWidth";
  static constexpr const char* kCombinedAffectSwitchUniform = "sCombinedAffect";
  static constexpr const char* kDottedEdgeUniform = "sDottedEdge";
  static constexpr const char* kCircleVertexUniform = "sCircleVertex";

  QOpenGLShaderProgram m_program;
};

std::string GetFileData(const std::string& file_name);
}  // namespace render

#endif  // SRC_VIEW_RENDER_SHADER_PROGRAM_H