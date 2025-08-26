#ifndef SRC_MODEL_RENDER_SHADER_PROGRAM_H
#define SRC_MODEL_RENDER_SHADER_PROGRAM_H

#include <QOpenGLShaderProgram>
#include <string>
#include "uniforms/uniforms.h"

namespace s21::render{
class ShaderProgram{
    public:
        static constexpr const char* kDefaultVertexShaderPath = "shaders/shader.vert";
        static constexpr const char* kDefaultFragmentShaderPath = "shaders/shader.frag";

        void SetShaders();
        void SetShaders(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        void UploadUniforms(const s21::render::uniforms::TransformationMatrix& trans_marix, 
            const s21::render::uniforms::CameraMatrix& cam_marix, 
            const s21::render::uniforms::ProjectionMatrix& project_matrix);
        void Bind();
        void Unbind();

        QOpenGLShaderProgram& GetProgram();

    private:
        QOpenGLShaderProgram m_program;

};

std::string GetFileData(const std::string& file_name);
}   //s21::render

#endif //SRC_MODEL_RENDER_SHADER_PROGRAM_H