#include "../shader_program.h"

#include <QOpenGLContext>
#include <fstream>
#include <stdexcept>

#include "core/service/service.h"
namespace render {

void ShaderProgram::SetVertexShaders() {
  SetShaders(kDefaultGlobalVertexShaderPath, kDefaultVertexFragmentShaderPath);
}

/**
 * @note Here must be kDefaultEdgeGeometryShaderPath too, it is required for
 * changing the width of the model edges, but, I haven't found a proper way to
 * make it work. So no Eges width controle for now ;(.
 */
void ShaderProgram::SetEdgeShaders() {
  SetShaders(kDefaultGlobalVertexShaderPath, kDefaultEdgeFragmentShaderPath);
}

void ShaderProgram::SetShaders(const std::string& vertex_shader_path,
                               const std::string& fragment_shader_path,
                               const std::string& geometry_shader_path) {
  if (!QOpenGLContext::currentContext())
    throw std::runtime_error("OpenGL context is not initialized.");

  auto vertexShSrc = GetFileData(vertex_shader_path);
  auto fragmentShSrc = GetFileData(fragment_shader_path);
  auto geometryShSrc = GetFileData(geometry_shader_path);

  if (vertexShSrc.empty())
    throw std::ios_base::failure("Vertex shader file can't be found: " +
                                 vertex_shader_path);
  if (fragmentShSrc.empty())
    throw std::ios_base::failure("Fragment shader file can't be found: " +
                                 fragment_shader_path);
  if (!geometry_shader_path.empty() && geometryShSrc.empty()) {
    throw std::ios_base::failure("Geometry shader file can't be found: " +
                                 geometry_shader_path);
  }

  m_program.removeAllShaders();

  if (!m_program.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                         vertexShSrc.c_str()))
    throw std::runtime_error("Vertex shader is inconsistent: " +
                             m_program.log().toStdString());
  if (!m_program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                         fragmentShSrc.c_str()))
    throw std::runtime_error("Fragment shader is inconsistent: " +
                             m_program.log().toStdString());
  if (!geometry_shader_path.empty()) {
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Geometry,
                                           geometryShSrc.c_str()))
      throw std::runtime_error("Geometry shader is inconsistent: " +
                               m_program.log().toStdString());
  }

  // Link the program
  m_program.link();
}

QOpenGLShaderProgram& ShaderProgram::GetProgram() { return m_program; }
std::string GetFileData(const std::string& file_name) {
  std::ifstream ifs(file_name, std::ios::binary | std::ios::ate);
  if (!ifs) return {};

  std::size_t size = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  std::string output(size, '\0');
  ifs.read(output.data(), size);
  return output;
}

void ShaderProgram::UploadUniforms(
    const render::uniforms::TransformationMatrix& trans_marix,
    const render::uniforms::CameraMatrix& cam_marix,
    const render::uniforms::ProjectionMatrix& project_matrix,
    const vectors::Vec4& model_color, const double vertex_size,
    const double edge_width, const bool dotted_edge_switch,
    const bool circle_vertex_switch) {
  if (!m_program.isLinked() || !Bind())
    throw std::runtime_error("Shader program is not linked or can't be bound.");

  m_program.setUniformValue(kCombinedAffectSwitchUniform, false);
  m_program.setUniformValue(kTransformationUniform, trans_marix.GetMatrixQT());
  m_program.setUniformValue(kCameraUniform, cam_marix.GetMatrixQT());
  m_program.setUniformValue(kProjectionUniform, project_matrix.GetMatrixQT());
  m_program.setUniformValue(
      kModelColorUniform,
      QVector4D(service::converters::DoubleToFloat(model_color.x),
                service::converters::DoubleToFloat(model_color.y),
                service::converters::DoubleToFloat(model_color.z),
                service::converters::DoubleToFloat(model_color.w)));
  m_program.setUniformValue(kVertexSizeUniform,
                            service::converters::DoubleToFloat(vertex_size));

  m_program.setUniformValue(kEdgeWidthUniform,
                            service::converters::DoubleToFloat(edge_width));
  m_program.setUniformValue(kDottedEdgeUniform, dotted_edge_switch);

  m_program.setUniformValue(kCircleVertexUniform, circle_vertex_switch);

  Unbind();
}

void ShaderProgram::UploadUniforms(
    const render::uniforms::UniformMatrix& combined_affect_matrix,
    const vectors::Vec4& model_color, const double vertex_size,
    const double edge_width, const bool dotted_edge_switch,
    const bool circle_vertex_switch) {
  if (!m_program.isLinked() || !Bind())
    throw std::runtime_error("Shader program is not linked or can't be bound.");

  m_program.setUniformValue(kCombinedAffectSwitchUniform, true);
  m_program.setUniformValue(kCombinedAffectUniform,
                            combined_affect_matrix.GetMatrixQT());
  m_program.setUniformValue(
      kModelColorUniform,
      QVector4D(service::converters::DoubleToFloat(model_color.x),
                service::converters::DoubleToFloat(model_color.y),
                service::converters::DoubleToFloat(model_color.z),
                service::converters::DoubleToFloat(model_color.w)));
  m_program.setUniformValue(kVertexSizeUniform,
                            service::converters::DoubleToFloat(vertex_size));

  m_program.setUniformValue(kEdgeWidthUniform,
                            service::converters::DoubleToFloat(edge_width));
  m_program.setUniformValue(kDottedEdgeUniform, dotted_edge_switch);

  m_program.setUniformValue(kCircleVertexUniform, circle_vertex_switch);

  Unbind();
}

bool ShaderProgram::Bind() { return m_program.bind(); }
void ShaderProgram::Unbind() { m_program.release(); }
}  // namespace render