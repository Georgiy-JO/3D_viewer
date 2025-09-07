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
        void SetShaders(const std::string& vertex_shader_path, const std::string& geometry_shader_path, const std::string& fragment_shader_path);
        void UploadUniforms(const s21::render::uniforms::TransformationMatrix& trans_marix, 
            const s21::render::uniforms::CameraMatrix& cam_marix, 
            const s21::render::uniforms::ProjectionMatrix& project_matrix,
            const double vertex_size, const double edge_width,
            const s21::vectors::Vec4& model_color, const bool render_mode_switch, 
            const bool dotted_edge_switch, const bool circle_vertex_switch);
        bool Bind();
        void Unbind();

        QOpenGLShaderProgram& GetProgram();

    private:
        static constexpr const char* kDefaultVertexShaderPath = "shaders/shader.vert";
        static constexpr const char* kDefaultGeometryShaderPath = "shaders/shader.geom";
        static constexpr const char* kDefaultFragmentShaderPath = "shaders/shader.frag";
        static constexpr const char* kTransformationUniform = "mTransformation";
        static constexpr const char* kCameraUniform = "mCamera";
        static constexpr const char* kProjectionUniform = "mProjection";
        static constexpr const char* kVertexSizeUniform = "dVertexSize";
        static constexpr const char* kEdgeWidthUniform = "dEdgeWidth";
        static constexpr const char* kModelColorUniform = "vModelColor";
        static constexpr const char* kRenderModeUniform = "sVertexMode";
        static constexpr const char* kDottedEdgeUniform = "sDottedEdge";
        static constexpr const char* kCircleVertexUniform = "sCircleVertex";

        QOpenGLShaderProgram m_program;
};

std::string GetFileData(const std::string& file_name);
}   //s21::render

#endif //SRC_MODEL_RENDER_SHADER_PROGRAM_H