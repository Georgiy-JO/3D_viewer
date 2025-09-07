#include "../shader_program.h"
#include "../../core/service/service.h"

#include <QOpenGLContext>
#include <fstream>
#include <stdexcept>
namespace s21::render {

void ShaderProgram::SetVertexShaders() {
  SetShaders(kDefaultVertexVertexShaderPath,kDefaultVertexFragmentShaderPath);
}

void ShaderProgram::SetEdgeShaders() {
  SetShaders(kDefaultEdgeVertexShaderPath,kDefaultEdgeFragmentShaderPath,kDefaultEdgeGeometryShaderPath);
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
  if(!geometry_shader_path.empty() && geometryShSrc.empty()){
    throw std::ios_base::failure("Geometry shader file can't be found: " +
                                geometry_shader_path);
}

  m_program.removeAllShaders();

  if (!m_program.addShaderFromSourceCode(QOpenGLShader::Vertex,vertexShSrc.c_str()))
    throw std::runtime_error("Vertex shader is inconsistent: " + m_program.log().toStdString());
  if (!m_program.addShaderFromSourceCode(QOpenGLShader::Fragment,fragmentShSrc.c_str()))
    throw std::runtime_error("Fragment shader is inconsistent: " + m_program.log().toStdString());

  if(!geometry_shader_path.empty()){
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Geometry,geometryShSrc.c_str()))
      throw std::runtime_error("Geometry shader is inconsistent: " + m_program.log().toStdString());
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
    const s21::render::uniforms::TransformationMatrix& trans_marix,
    const s21::render::uniforms::CameraMatrix& cam_marix,
    const s21::render::uniforms::ProjectionMatrix& project_matrix,
    const s21::vectors::Vec4& model_color,
    const double vertex_size, const double edge_width,
    const bool dotted_edge_switch, const bool circle_vertex_switch, const s21::vectors::Vec2& view_dementions ) {
  if (!m_program.isLinked() || !Bind())
    throw std::runtime_error("Shader program is not linked or can't be bound.");

  m_program.setUniformValue(kTransformationUniform, trans_marix.GetMatrixQT());
  m_program.setUniformValue(kCameraUniform, cam_marix.GetMatrixQT());
  m_program.setUniformValue(kProjectionUniform, project_matrix.GetMatrixQT());
  m_program.setUniformValue(kModelColorUniform, QVector4D(s21::service::converters::DoubleToFloat(model_color.x),s21::service::converters::DoubleToFloat (model_color.y),s21::service::converters::DoubleToFloat(model_color.z),s21::service::converters::DoubleToFloat(model_color.w)));
  
  m_program.setUniformValue(kVertexSizeUniform, s21::service::converters::DoubleToFloat(vertex_size));
  m_program.setUniformValue(kCircleVertexUniform, circle_vertex_switch);
  m_program.setUniformValue(kEdgeWidthUniform, s21::service::converters::DoubleToFloat(edge_width));
  m_program.setUniformValue(kDottedEdgeUniform, dotted_edge_switch);
  m_program.setUniformValue(kViewDementionsUniform, QVector2D(s21::service::converters::DoubleToFloat(view_dementions.x),s21::service::converters::DoubleToFloat(view_dementions.y)));

  Unbind();
}

bool ShaderProgram::Bind() { return m_program.bind(); }
void ShaderProgram::Unbind() { m_program.release(); }
}  // namespace s21::render