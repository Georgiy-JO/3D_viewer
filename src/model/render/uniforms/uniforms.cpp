#include "uniforms.h"

#include <stdexcept>
namespace s21::render::uniforms{

     UniformMatrix::UniformMatrix():m_matrix(){
        m_matrix.SetToIdentity();
    }

    const s21::matrix::Matrix4x4& UniformMatrix::GetMatrix() const{
        return m_matrix;
    }
    
    QMatrix4x4 UniformMatrix::GetMatrixQT() const{
        QMatrix4x4 qmatrix;
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                qmatrix(i,j)=m_matrix(i,j);
            }
        }
        return qmatrix;
    }


    void TransformationMatrix::Reset(){
        m_matrix.SetToIdentity();
    }
    
    void TransformationMatrix::RotateX(float degrees){
        m_matrix.Rotate(degrees, s21::vectors::Vec3(1.0,0.0,0.0));
    }
    
    void TransformationMatrix::RotateY(float degrees){
        m_matrix.Rotate(degrees, s21::vectors::Vec3(0.0,1.0,0.0));
    }
    
    void TransformationMatrix::RotateZ(float degrees){
        m_matrix.Rotate(degrees, s21::vectors::Vec3(0.0,0.0,1.0));
    }
    
    void TransformationMatrix::Translate(float x, float y, float z){
        m_matrix.Translate(s21::vectors::Vec3(x,y,z));
    }
    
    void TransformationMatrix::Scale(float scale){
        m_matrix.Scale(scale);
    }


    CameraMatrix::CameraMatrix(){
        Reset();
    }

    void CameraMatrix::Reset(s21::vectors::Vec3 vec) {
        m_matrix.SetToIdentity();
        m_matrix.Translate(vec);
    }

 

    ProjectionMatrix::ProjectionMatrix(){
        m_matrix.SetToIdentity();
    }

    void ProjectionMatrix::Reset(double w, double h, double fov_angle, double near_plane, double far_plane){        
        if(h<=0)
            throw std::invalid_argument("ProjectionMatrix::Reset - height must be positive");
        fov_angle=s21::matrix::DegreesToRadians(fov_angle);
        double tan=std::tan(fov_angle/2.0f);
        double ratio=w/(h>0?h:1.0f);
        s21::matrix::Matrix local (4,4);

        local(0,0)=1.0f/(ratio*tan);
        local(0,1)=0;
        local(0,2)=0;
        local(0,3)=0;

        local(1,0)=0;
        local(1,1)=1.0f/(tan);
        local(1,2)=0;
        local(1,3)=0;

        local(2,0)=0;
        local(2,1)=0;
        local(2,2)=(far_plane+near_plane)/(near_plane-far_plane);
        local(2,3)=2*far_plane*near_plane/(near_plane-far_plane);

        local(3,0)=0;
        local(3,1)=0;
        local(3,2)=-1;
        local(3,3)=0;  

        m_matrix=local;
    }

}   //s21::render::uniforms