#ifndef SRC_CONTROLLER_RENDER_CONTROLLER_H
#define SRC_CONTROLLER_RENDER_CONTROLLER_H
#include "../model/render/gui_model.h"
#include "../model/render/shader_program.h"

namespace s21::controller{
class Render{
    public:
        Render():m_model(),m_transformation_matrix(),m_camera_matrix(),m_projection_matrix(),m_program(){}
        
        s21::render::GPU_Model& Model(){return m_model;}
        s21::render::uniforms::TransformationMatrix& Transform(){return m_transformation_matrix;}
        s21::render::uniforms::CameraMatrix& Camera(){return m_camera_matrix;}
        s21::render::uniforms::ProjectionMatrix& Projection(){return m_projection_matrix;}
        s21::render::ShaderProgram& Program(){return m_program;}
        void SetUniforms(){ 
            m_program.UploadUniforms(m_transformation_matrix,m_camera_matrix,m_projection_matrix);
            // m_transformation_matrix.Reset();//????
        }

    private:
        s21::render::GPU_Model m_model;
        s21::render::uniforms::TransformationMatrix m_transformation_matrix;
        s21::render::uniforms::CameraMatrix m_camera_matrix;
        s21::render::uniforms::ProjectionMatrix m_projection_matrix;
        s21::render::ShaderProgram m_program;
};
}   //s21::controller

#endif //SRC_CONTROLLER_RENDER_CONTROLLER_H