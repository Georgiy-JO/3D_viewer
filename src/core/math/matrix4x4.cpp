#include "matrix4x4.h"

namespace s21::matrix
{

    Matrix4x4::Matrix4x4():m_matrix(4,4){}

    Matrix4x4::Matrix4x4(const Matrix4x4& other):Matrix4x4(){
        m_matrix=other.m_matrix;
    }
    
    Matrix4x4::Matrix4x4(const Matrix& other):Matrix4x4(){
        if(other.getCols()>4 || other.getRows()>4 || other.getRows()!=other.getCols())
            throw InputError();
        m_matrix=other;   
    }

    void Matrix4x4::SetToIdentity(){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(i==j)
                    m_matrix(i,j)=1;
                else
                    m_matrix(i,j)=0;
            }
        }
    }

    void Matrix4x4::Translate(const Vec3& vec){
        Matrix4x4 local;
        local.SetToIdentity();
        local.m_matrix(0,3)=vec.x;
        local.m_matrix(1,3)=vec.y;
        local.m_matrix(2,3)=vec.z;
        (*this)*=local;
    }

    void Matrix4x4::Rotate(double angle, Vec3 vec){
        vec.Normalize();
        
        angle=DegreesToRadians(angle);
        double sin=std::sin(angle), cos=std::cos(angle);

        Matrix4x4 local;
        local.SetToIdentity();

        local.m_matrix(0,0)=cos+(1.0-cos)*std::pow(vec.x,2);
        local.m_matrix(0,1)=(1.0-cos)*vec.x*vec.y-sin*vec.z;
        local.m_matrix(0,2)=(1.0-cos)*vec.x*vec.z+sin*vec.y;
        local.m_matrix(0,3)=0.0;

        local.m_matrix(1,0)=(1.0-cos)*vec.y*vec.x+sin*vec.z;
        local.m_matrix(1,1)=cos+(1.0-cos)*pow(vec.y,2);
        local.m_matrix(1,2)=(1.0-cos)*vec.y*vec.z-sin*vec.x;
        local.m_matrix(1,3)=0.0;

        local.m_matrix(2,0)=(1.0-cos)*vec.z*vec.x-sin*vec.y;
        local.m_matrix(2,1)=(1.0-cos)*vec.z*vec.y+sin*vec.x;
        local.m_matrix(2,2)=cos+(1.0-cos)*pow(vec.z,2);
        local.m_matrix(2,3)=0.0;

        local.m_matrix(3,0)=0.0;
        local.m_matrix(3,1)=0.0;
        local.m_matrix(3,2)=0.0;
        local.m_matrix(3,3)=1.0;

        (*this)*=local;
    }

    void Matrix4x4::Scale(double scale){
        if(scale<=0) scale=kMinialScale;
        Matrix4x4 local;
        local.SetToIdentity();
        local.m_matrix(0,0)=scale;
        local.m_matrix(1,1)=scale;
        local.m_matrix(2,2)=scale;
        (*this)*=local;
    }

    Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const{
        return Matrix4x4(m_matrix+other.m_matrix);
    }

    Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other){
        return *this=*this+other;
    }

    Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const{
        return Matrix4x4(m_matrix-other.m_matrix);
    }

    Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other){
        return *this=*this-other;
    }

    Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const{
        return Matrix4x4(m_matrix*other.m_matrix);        
    }

    Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& other){
        return *this=*this*other;
    }

    Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other){
        m_matrix=other.m_matrix;
        return *this;
    }

    Matrix4x4& Matrix4x4::operator=(const Matrix& other){
        m_matrix=other;
        return *this;
    }

    bool Matrix4x4::operator==(const Matrix4x4& other) const{
        return m_matrix==other.m_matrix;
    }

    double Matrix4x4::operator()(int row, int col)const{
        return double(m_matrix(row,col));
    }

    constexpr double DegreesToRadians(double degrees) {
        return degrees * (M_PI / 180.0);
    }

} // namespace s21::matrix