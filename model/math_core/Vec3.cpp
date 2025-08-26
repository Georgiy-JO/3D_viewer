#include "Vec3.h"

namespace s21 {

    Vec3::Vec3() : x(0), y(0), z(0) {}
    Vec3::Vec3(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    Vec3::Vec3(const Vec3& vec):x(vec.x), y(vec.y), z(vec.z){}
    Vec3 Vec3::operator*(double number) const{
        return Vec3(x * number, y * number, z * number);
    }
    Vec3 operator*(double number, const Vec3& vec){
        return Vec3(vec.x*number,vec.y*number,vec.z*number);
    }
    Vec3& Vec3::operator*=(double number){
        x*=number;
        y*=number;
        z*=number;
        return *this;
    }
    Vec3 Vec3::operator-(const Vec3& vec) const{
        return Vec3(x-vec.x,y-vec.y,z-vec.z);
    }
    Vec3& Vec3::operator-=(const Vec3& vec){
        x-=vec.x;
        y-=vec.y;
        z-=vec.z;
        return *this;
    }
    Vec3 Vec3::operator+(const Vec3& vec) const{
        return Vec3(x+vec.x,y+vec.y,z+vec.z);
    }
    Vec3& Vec3::operator+=(const Vec3& vec){
        x+=vec.x;
        y+=vec.y;
        z+=vec.z;
        return *this;
    }
    Vec3& Vec3::operator=(const Vec3& vec){
        x=vec.x;
        y=vec.y;
        z=vec.z;
    }
    bool Vec3::operator==(const Vec3& vec) const{
        return(x==vec.x && y==vec.y && z==vec.z);
    }
    bool Vec3::operator!=(const Vec3& vec) const{
        return !(*this==vec);
    }
    
    Vec3& Vec3::operator--(){
        *this-=Vec3(1,1,1);
        return *this;
    }
    Vec3& Vec3::operator++(){

    }

}  // namespace s21