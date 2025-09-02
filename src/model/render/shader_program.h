#ifndef SRC_MODEL_RENDER_SHADER_PROGRAM_H
#define SRC_MODEL_RENDER_SHADER_PROGRAM_H

#include <QOpenGLShaderProgram>
#include <string>
#include "uniforms/uniforms.h"

namespace s21::render{
class ShaderProgram{
    public:
        /**
         * @note Need to have active OpenGL context before calling. 
         */
        void SetShaders();
        void SetShaders(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        void UploadUniforms(const s21::render::uniforms::TransformationMatrix& trans_marix, 
            const s21::render::uniforms::CameraMatrix& cam_marix, 
            const s21::render::uniforms::ProjectionMatrix& project_matrix);
        bool Bind();
        void Unbind();

        QOpenGLShaderProgram& GetProgram();

    private:
        static constexpr const char* kDefaultVertexShaderPath = "shaders/shader.vert";
        static constexpr const char* kDefaultFragmentShaderPath = "shaders/shader.frag";
        static constexpr const char* kTransformationUniform = "model";
        static constexpr const char* kCameraUniform = "view";
        static constexpr const char* kProjectionUniform = "projection";
        QOpenGLShaderProgram m_program;

};

std::string GetFileData(const std::string& file_name);
}   //s21::render

#endif //SRC_MODEL_RENDER_SHADER_PROGRAM_H