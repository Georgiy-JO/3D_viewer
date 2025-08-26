#include "../shader_program.h"

#include <fstream>
#include <stdexcept>
namespace s21::render{

void ShaderProgram::SetShaders(){
    SetShaders(kDefaultVertexShaderPath, kDefaultFragmentShaderPath);
}

void ShaderProgram::SetShaders(const std::string& vertex_shader_path, const std::string& fragment_shader_path){
    auto vertexShSrc = GetFileData(vertex_shader_path);
    auto fragmentShSrc = GetFileData(fragment_shader_path);
    if(vertexShSrc.empty()) throw std::ios_base::failure("Vertex shader file can't be found: "+vertex_shader_path);
    if(fragmentShSrc.empty()) throw std::ios_base::failure("Fragment shader file can't be found: "+fragment_shader_path);

    m_program.removeAllShaders();

    if(!m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShSrc.c_str()))
        throw std::runtime_error("Vertex shader is inconsistent: "+ m_program.log().toStdString());
    if(!m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShSrc.c_str()))
        throw std::runtime_error("Fragment shader is inconsistent: "+ m_program.log().toStdString());

    // Link the program
    m_program.link();
}

QOpenGLShaderProgram& ShaderProgram::GetProgram(){
    return m_program;
}
std::string GetFileData(const std::string& file_name){
    std::ifstream ifs(file_name, std::ios::binary | std::ios::ate);
    if(!ifs) return {};

    std::size_t size=ifs.tellg();
    ifs.seekg(0,std::ios::beg);

    std::string output (size, '\0');
    ifs.read(output.data(),size);
    return output;
}
void ShaderProgram::UploadUniforms(const s21::render::uniforms::TransformationMatrix& trans_marix, 
            const s21::render::uniforms::CameraMatrix& cam_marix, 
            const s21::render::uniforms::ProjectionMatrix& project_matrix){
    Bind();
    m_program.setUniformValue("model", trans_marix.GetMatrixQT());
    m_program.setUniformValue("view", cam_marix.GetMatrixQT());
    m_program.setUniformValue("projection", project_matrix.GetMatrixQT());
    Unbind();
}
void ShaderProgram::Bind(){
    m_program.bind();
}
void ShaderProgram::Unbind(){
    m_program.release();
}
}   //s21::render