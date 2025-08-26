#pragma once

namespace s21 {

struct Vec3{
    double x=0, y=0, z=0;

    Vec3();
    Vec3(double x_, double y_, double z_);
    Vec3(const Vec3& vec);
    Vec3 operator*(double number) const;
    friend Vec3 operator*(double number, const Vec3& vec);
    Vec3& operator*=(double number);
    Vec3 operator-(const Vec3& vec) const;
    Vec3& operator-=(const Vec3& vec);
    Vec3 operator+(const Vec3& vec) const;
    Vec3& operator+=(const Vec3& vec);
    Vec3& operator=(const Vec3& vec);
    bool operator==(const Vec3& vec) const;
    bool operator!=(const Vec3& vec) const;

    // if these ones won't be needed, they can be deleted
    Vec3& operator--();
    Vec3& operator++();

    // if these ones will be needed, they can be added
    // Vec3 operator*(const Vec3& vec) const;
    // Vec3& operator*=(const Vec3& vec);
    // double length() const;

};  //struct Vect3


}  // namespace s21

