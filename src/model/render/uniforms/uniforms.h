#ifndef SRC_MODEL_RENDER_UNIFORMS_H
#define SRC_MODEL_RENDER_UNIFORMS_H

#include "../../../core/math/matrix4x4.h"
#include <QMatrix4x4>
namespace s21::render::uniforms{

class UniformMatrix{
    public:
        UniformMatrix();
        virtual ~UniformMatrix()=default;

        const s21::matrix::Matrix4x4& GetMatrix() const;
        QMatrix4x4 GetMatrixQT() const;

    protected:
        s21::matrix::Matrix4x4 m_matrix;
};


class TransformationMatrix: public UniformMatrix{
    public:
        TransformationMatrix()=default;

        void Reset();
        void RotateX(float degrees);
        void RotateY(float degrees);
        void RotateZ(float degrees);
        void Translate(float x, float y, float z);
        void Scale(float scale);
};

class CameraMatrix: public UniformMatrix{
    public:
        static constexpr s21::vectors::Vec3 kDefaultCamera {0.0f, 0.0f, -5.0f};
        CameraMatrix();
        void Reset(s21::vectors::Vec3 vec=kDefaultCamera) ;
};

class ProjectionMatrix: public UniformMatrix{
    public:
        static constexpr double kFovAngle = 45.0f; 
        static constexpr double kNearPlane =0.1f; 
        static constexpr double kFarPlane = 100.0f; 
        ProjectionMatrix();
        void Reset(double w, double h, double fov_angle = kFovAngle, double near_plane =kNearPlane, double far_plane =kFarPlane);
};

}       //s21::render::uniforms

#endif  //SRC_MODEL_RENDER_UNIFORMS_H