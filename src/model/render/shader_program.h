#ifndef SRC_MODEL_RENDER_SHADER_PROGRAM_H
#define SRC_MODEL_RENDER_SHADER_PROGRAM_H

#include <QOpenGLShaderProgram>
#include <string>
#include "uniforms/uniforms.h"
#include "../../core/math/vec4.h"

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
            const s21::render::uniforms::ProjectionMatrix& project_matrix,
            const double vertex_size, const s21::vectors::Vec4& model_color,
            const bool render_mode_switch, const bool dotted_edge_switch, 
            const bool circle_vertex_switch);
        bool Bind();
        void Unbind();

        QOpenGLShaderProgram& GetProgram();

    private:
        static constexpr const char* kDefaultVertexShaderPath = "shaders/shader.vert";
        static constexpr const char* kDefaultFragmentShaderPath = "shaders/shader.frag";
        static constexpr const char* kTransformationUniform = "transformation";
        static constexpr const char* kCameraUniform = "camera";
        static constexpr const char* kProjectionUniform = "projection";
        static constexpr const char* kVertexSizeUniform = "vertex_size";
        static constexpr const char* kModelColorUniform = "model_color";
        static constexpr const char* kRenderModeUniform = "edges_vertex_switch";
        static constexpr const char* kDottedEdgeUniform = "dotted_edge";
        static constexpr const char* kCircleVertexUniform = "circle_vertex";

        QOpenGLShaderProgram m_program;
};

std::string GetFileData(const std::string& file_name);
}   //s21::render

#endif //SRC_MODEL_RENDER_SHADER_PROGRAM_H