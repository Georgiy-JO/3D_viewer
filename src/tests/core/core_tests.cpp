#include <gtest/gtest.h>
#include "../../core/math/vec2.h"
#include "../../core/math/vec3.h"
#include "../../core/math/vec4.h"
#include "../../core/math/basis.h"
#include "../../core/math/matrix4x4.h"
#include "../../core/service/service.h"

TEST(Core_Vectors, Vec3_1) {
  using Vec3 = s21::vectors::Vec3;
  Vec3 a;
  Vec3 b(0, 0, 0);
  EXPECT_DOUBLE_EQ(a.x, b.x);
  EXPECT_DOUBLE_EQ(a.y, b.y);
  EXPECT_DOUBLE_EQ(a.z, b.z);

  Vec3 c{1, 2, 3};
  Vec3 d(c);
  Vec3 e(5);
  EXPECT_DOUBLE_EQ(c.x, 1);
  EXPECT_DOUBLE_EQ(c.y, 2);
  EXPECT_DOUBLE_EQ(c.z, 3);
  EXPECT_DOUBLE_EQ(d.x, 1);
  EXPECT_DOUBLE_EQ(d.y, 2);
  EXPECT_DOUBLE_EQ(d.z, 3);
  EXPECT_DOUBLE_EQ(e.x, 5);
  EXPECT_DOUBLE_EQ(e.y, 5);
  EXPECT_DOUBLE_EQ(e.z, 5);

  a = c * 5;
  b = 5 * d;
  EXPECT_DOUBLE_EQ(a.x, 5);
  EXPECT_DOUBLE_EQ(a.y, 10);
  EXPECT_DOUBLE_EQ(a.z, 15);
  EXPECT_DOUBLE_EQ(b.x, 5);
  EXPECT_DOUBLE_EQ(b.y, 10);
  EXPECT_DOUBLE_EQ(b.z, 15);

  e *= 5;
  EXPECT_DOUBLE_EQ(e.x, 25);
  EXPECT_DOUBLE_EQ(e.y, 25);
  EXPECT_DOUBLE_EQ(e.z, 25);

  b = e - a;
  EXPECT_DOUBLE_EQ(b.x, 20);
  EXPECT_DOUBLE_EQ(b.y, 15);
  EXPECT_DOUBLE_EQ(b.z, 10);

  b -= a;
  EXPECT_DOUBLE_EQ(b.x, 15);
  EXPECT_DOUBLE_EQ(b.y, 5);
  EXPECT_DOUBLE_EQ(b.z, -5);

  b = b + b;
  EXPECT_DOUBLE_EQ(b.x, 30);
  EXPECT_DOUBLE_EQ(b.y, 10);
  EXPECT_DOUBLE_EQ(b.z, -10);

  a += b;
  EXPECT_DOUBLE_EQ(a.x, 35);
  EXPECT_DOUBLE_EQ(a.y, 20);
  EXPECT_DOUBLE_EQ(a.z, 5);

  a = b;
  EXPECT_DOUBLE_EQ(a.x, 30);
  EXPECT_DOUBLE_EQ(a.y, 10);
  EXPECT_DOUBLE_EQ(a.z, -10);

  EXPECT_EQ(a, b);
  EXPECT_DOUBLE_EQ(a == b, true);
  EXPECT_DOUBLE_EQ(a == c, false);
  EXPECT_DOUBLE_EQ(a == b, 1);

  EXPECT_NE(a, c);
  EXPECT_DOUBLE_EQ(a != b, false);
  EXPECT_DOUBLE_EQ(a != c, true);
  EXPECT_DOUBLE_EQ(a != c, 1);

  --e;
  EXPECT_DOUBLE_EQ(e.x, 24);
  EXPECT_DOUBLE_EQ(e.y, 24);
  EXPECT_DOUBLE_EQ(e.z, 24);
  d = --e;
  EXPECT_DOUBLE_EQ(e.x, 23);
  EXPECT_DOUBLE_EQ(e.y, 23);
  EXPECT_DOUBLE_EQ(e.z, 23);
  EXPECT_DOUBLE_EQ(d.x, 23);
  EXPECT_DOUBLE_EQ(d.y, 23);
  EXPECT_DOUBLE_EQ(d.z, 23);

  e--;
  EXPECT_DOUBLE_EQ(e.x, 22);
  EXPECT_DOUBLE_EQ(e.y, 22);
  EXPECT_DOUBLE_EQ(e.z, 22);
  d = e--;
  EXPECT_DOUBLE_EQ(e.x, 21);
  EXPECT_DOUBLE_EQ(e.y, 21);
  EXPECT_DOUBLE_EQ(e.z, 21);
  EXPECT_DOUBLE_EQ(d.x, 22);
  EXPECT_DOUBLE_EQ(d.y, 22);
  EXPECT_DOUBLE_EQ(d.z, 22);

  for (int i = 0; i < 79; i++, e++) {
  }
  EXPECT_DOUBLE_EQ(e.x, 100);
  EXPECT_DOUBLE_EQ(e.y, 100);
  EXPECT_DOUBLE_EQ(e.z, 100);
  for (int i = 0; i < 5; i++, ++e) {
  }
  EXPECT_DOUBLE_EQ(e.x, 105);
  EXPECT_DOUBLE_EQ(e.y, 105);
  EXPECT_DOUBLE_EQ(e.z, 105);
}

TEST(Core_Vectors, Vec3_2) {
  using Vec3 = s21::vectors::Vec3;
  Vec3 a;

  a.x=1;
  a.y=2;
  a.z=2;
  a.Normalize();
  EXPECT_DOUBLE_EQ(a.x, 1.0/3.0);
  EXPECT_DOUBLE_EQ(a.y, 2.0/3.0);
  EXPECT_DOUBLE_EQ(a.z, 2.0/3.0);

  a.x=0;
  a.y=0;
  a.z=5;
  a.Normalize();
  EXPECT_DOUBLE_EQ(a.x, 0);
  EXPECT_DOUBLE_EQ(a.y, 0);
  EXPECT_DOUBLE_EQ(a.z, 1);

  a.x=6;
  a.y=8;
  a.z=0;
  a.Normalize();
  EXPECT_DOUBLE_EQ(a.x, 0.6);
  EXPECT_DOUBLE_EQ(a.y, 0.8);
  EXPECT_DOUBLE_EQ(a.z, 0);

  a.x=0;
  a.y=0;
  a.z=0;
  a.Normalize();
  EXPECT_DOUBLE_EQ(a.x, 0);
  EXPECT_DOUBLE_EQ(a.y, 0);
  EXPECT_DOUBLE_EQ(a.z, 0);
}

TEST(Core_Vectors, Vec2) {
    s21::vectors::Vec2 a;

    EXPECT_DOUBLE_EQ(a.x, 0);
    EXPECT_DOUBLE_EQ(a.y, 0);

    s21::vectors::Vec2 b(4.5,5.5);
    EXPECT_DOUBLE_EQ(b.x, 4.5);
    EXPECT_DOUBLE_EQ(b.y, 5.5);
}

TEST(Core_Vectors, Vec4) {
  using Vec4 = s21::vectors::Vec4;
  Vec4 a;
  Vec4 b(0, 0, 0,0);
  EXPECT_DOUBLE_EQ(a.x, b.x);
  EXPECT_DOUBLE_EQ(a.y, b.y);
  EXPECT_DOUBLE_EQ(a.z, b.z);
  EXPECT_DOUBLE_EQ(a.w, b.w);

  Vec4 c{1, 2, 3,4};
  Vec4 d(c);
  Vec4 e(5);
  EXPECT_DOUBLE_EQ(c.x, 1);
  EXPECT_DOUBLE_EQ(c.y, 2);
  EXPECT_DOUBLE_EQ(c.z, 3);
  EXPECT_DOUBLE_EQ(c.w, 4);
  EXPECT_DOUBLE_EQ(d.x, 1);
  EXPECT_DOUBLE_EQ(d.y, 2);
  EXPECT_DOUBLE_EQ(d.z, 3);
  EXPECT_DOUBLE_EQ(d.w, 4);
  EXPECT_DOUBLE_EQ(e.x, 5);
  EXPECT_DOUBLE_EQ(e.y, 5);
  EXPECT_DOUBLE_EQ(e.z, 5);
  EXPECT_DOUBLE_EQ(e.w, 5);

  a = c * 5;
  b = 5 * d;
  EXPECT_DOUBLE_EQ(a.x, 5);
  EXPECT_DOUBLE_EQ(a.y, 10);
  EXPECT_DOUBLE_EQ(a.z, 15);
  EXPECT_DOUBLE_EQ(a.w, 20);
  EXPECT_DOUBLE_EQ(b.x, 5);
  EXPECT_DOUBLE_EQ(b.y, 10);
  EXPECT_DOUBLE_EQ(b.z, 15);
  EXPECT_DOUBLE_EQ(b.w, 20);

  e *= 5;
  EXPECT_DOUBLE_EQ(e.x, 25);
  EXPECT_DOUBLE_EQ(e.y, 25);
  EXPECT_DOUBLE_EQ(e.z, 25);
  EXPECT_DOUBLE_EQ(e.w, 25);

  b = e - a;
  EXPECT_DOUBLE_EQ(b.x, 20);
  EXPECT_DOUBLE_EQ(b.y, 15);
  EXPECT_DOUBLE_EQ(b.z, 10);
  EXPECT_DOUBLE_EQ(b.w, 5);

  b -= a;
  EXPECT_DOUBLE_EQ(b.x, 15);
  EXPECT_DOUBLE_EQ(b.y, 5);
  EXPECT_DOUBLE_EQ(b.z, -5);
  EXPECT_DOUBLE_EQ(b.w, -15);

  b = b + b;
  EXPECT_DOUBLE_EQ(b.x, 30);
  EXPECT_DOUBLE_EQ(b.y, 10);
  EXPECT_DOUBLE_EQ(b.z, -10);
  EXPECT_DOUBLE_EQ(b.w, -30);

  a += b;
  EXPECT_DOUBLE_EQ(a.x, 35);
  EXPECT_DOUBLE_EQ(a.y, 20);
  EXPECT_DOUBLE_EQ(a.z, 5);
  EXPECT_DOUBLE_EQ(a.w, -10);

  a = b;
  EXPECT_DOUBLE_EQ(a.x, 30);
  EXPECT_DOUBLE_EQ(a.y, 10);
  EXPECT_DOUBLE_EQ(a.z, -10);
  EXPECT_DOUBLE_EQ(a.w, -30);

  EXPECT_EQ(a, b);
  EXPECT_DOUBLE_EQ(a == b, true);
  EXPECT_DOUBLE_EQ(a == c, false);
  EXPECT_DOUBLE_EQ(a == b, 1);

  EXPECT_NE(a, c);
  EXPECT_DOUBLE_EQ(a != b, false);
  EXPECT_DOUBLE_EQ(a != c, true);
  EXPECT_DOUBLE_EQ(a != c, 1);

}

TEST(Core_Vectors, Basis) {
    EXPECT_EQ(s21::basis::kBasisVectorX,s21::vectors::Vec3(1,0,0));
    EXPECT_EQ(s21::basis::kBasisVectorY,s21::vectors::Vec3(0,1,0));
    EXPECT_EQ(s21::basis::kBasisVectorZ,s21::vectors::Vec3(0,0,1));
}

TEST(Core_Vectors, Matrix4x4_1_and_Translate) {
    using Matrix4x4=s21::matrix::Matrix4x4;
    using Matrix=s21::matrix::Matrix;
    using Vec3=s21::vectors::Vec3;

    Matrix4x4 a;
    EXPECT_DOUBLE_EQ(a(0,0),0);
    EXPECT_DOUBLE_EQ(a(0,1),0);
    EXPECT_DOUBLE_EQ(a(0,2),0);
    EXPECT_DOUBLE_EQ(a(0,3),0);

    EXPECT_DOUBLE_EQ(a(1,0),0);
    EXPECT_DOUBLE_EQ(a(1,1),0);
    EXPECT_DOUBLE_EQ(a(1,2),0);
    EXPECT_DOUBLE_EQ(a(1,3),0);

    EXPECT_DOUBLE_EQ(a(2,0),0);
    EXPECT_DOUBLE_EQ(a(2,1),0);
    EXPECT_DOUBLE_EQ(a(2,2),0);
    EXPECT_DOUBLE_EQ(a(2,3),0);

    EXPECT_DOUBLE_EQ(a(3,0),0);
    EXPECT_DOUBLE_EQ(a(3,1),0);
    EXPECT_DOUBLE_EQ(a(3,2),0);
    EXPECT_DOUBLE_EQ(a(3,3),0);

    Matrix4x4 b(a);
    EXPECT_DOUBLE_EQ(b(0,0),0);
    EXPECT_DOUBLE_EQ(b(0,1),0);
    EXPECT_DOUBLE_EQ(b(0,2),0);
    EXPECT_DOUBLE_EQ(b(0,3),0);

    EXPECT_DOUBLE_EQ(b(1,0),0);
    EXPECT_DOUBLE_EQ(b(1,1),0);
    EXPECT_DOUBLE_EQ(b(1,2),0);
    EXPECT_DOUBLE_EQ(b(1,3),0);

    EXPECT_DOUBLE_EQ(b(2,0),0);
    EXPECT_DOUBLE_EQ(b(2,1),0);
    EXPECT_DOUBLE_EQ(b(2,2),0);
    EXPECT_DOUBLE_EQ(b(2,3),0);

    EXPECT_DOUBLE_EQ(b(3,0),0);
    EXPECT_DOUBLE_EQ(b(3,1),0);
    EXPECT_DOUBLE_EQ(b(3,2),0);
    EXPECT_DOUBLE_EQ(b(3,3),0);

    Matrix m(4,4);
    EXPECT_DOUBLE_EQ(m(0,0),0);
    EXPECT_DOUBLE_EQ(m(0,1),0);
    EXPECT_DOUBLE_EQ(m(0,2),0);
    EXPECT_DOUBLE_EQ(m(0,3),0);

    EXPECT_DOUBLE_EQ(m(1,0),0);
    EXPECT_DOUBLE_EQ(m(1,1),0);
    EXPECT_DOUBLE_EQ(m(1,2),0);
    EXPECT_DOUBLE_EQ(m(1,3),0);

    EXPECT_DOUBLE_EQ(m(2,0),0);
    EXPECT_DOUBLE_EQ(m(2,1),0);
    EXPECT_DOUBLE_EQ(m(2,2),0);
    EXPECT_DOUBLE_EQ(m(2,3),0);

    EXPECT_DOUBLE_EQ(m(3,0),0);
    EXPECT_DOUBLE_EQ(m(3,1),0);
    EXPECT_DOUBLE_EQ(m(3,2),0);
    EXPECT_DOUBLE_EQ(m(3,3),0);

    m(0,0)=1;
    m(0,1)=2;
    m(0,2)=3;
    m(0,3)=4;

    m(1,0)=5;
    m(1,1)=6;
    m(1,2)=7;
    m(1,3)=8;

    m(2,0)=9;
    m(2,1)=0.1;
    m(2,2)=0.2;
    m(2,3)=0.3;

    m(3,0)=0.4;
    m(3,1)=0.5;
    m(3,2)=0.6;
    m(3,3)=0.7;

    Matrix4x4 c(m);

    EXPECT_DOUBLE_EQ(m(0,0),1);
    EXPECT_DOUBLE_EQ(m(0,1),2);
    EXPECT_DOUBLE_EQ(m(0,2),3);
    EXPECT_DOUBLE_EQ(m(0,3),4);

    EXPECT_DOUBLE_EQ(m(1,0),5);
    EXPECT_DOUBLE_EQ(m(1,1),6);
    EXPECT_DOUBLE_EQ(m(1,2),7);
    EXPECT_DOUBLE_EQ(m(1,3),8);

    EXPECT_DOUBLE_EQ(m(2,0),9);
    EXPECT_DOUBLE_EQ(m(2,1),0.1);
    EXPECT_DOUBLE_EQ(m(2,2),0.2);
    EXPECT_DOUBLE_EQ(m(2,3),0.3);

    EXPECT_DOUBLE_EQ(m(3,0),0.4);
    EXPECT_DOUBLE_EQ(m(3,1),0.5);
    EXPECT_DOUBLE_EQ(m(3,2),0.6);
    EXPECT_DOUBLE_EQ(m(3,3),0.7);

    EXPECT_DOUBLE_EQ(c(0,0),1);
    EXPECT_DOUBLE_EQ(c(0,1),2);
    EXPECT_DOUBLE_EQ(c(0,2),3);
    EXPECT_DOUBLE_EQ(c(0,3),4);

    EXPECT_DOUBLE_EQ(c(1,0),5);
    EXPECT_DOUBLE_EQ(c(1,1),6);
    EXPECT_DOUBLE_EQ(c(1,2),7);
    EXPECT_DOUBLE_EQ(c(1,3),8);

    EXPECT_DOUBLE_EQ(c(2,0),9);
    EXPECT_DOUBLE_EQ(c(2,1),0.1);
    EXPECT_DOUBLE_EQ(c(2,2),0.2);
    EXPECT_DOUBLE_EQ(c(2,3),0.3);

    EXPECT_DOUBLE_EQ(c(3,0),0.4);
    EXPECT_DOUBLE_EQ(c(3,1),0.5);
    EXPECT_DOUBLE_EQ(c(3,2),0.6);
    EXPECT_DOUBLE_EQ(c(3,3),0.7);

    c.SetToIdentity();

    EXPECT_DOUBLE_EQ(c(0,0),1);
    EXPECT_DOUBLE_EQ(c(0,1),0);
    EXPECT_DOUBLE_EQ(c(0,2),0);
    EXPECT_DOUBLE_EQ(c(0,3),0);

    EXPECT_DOUBLE_EQ(c(1,0),0);
    EXPECT_DOUBLE_EQ(c(1,1),1);
    EXPECT_DOUBLE_EQ(c(1,2),0);
    EXPECT_DOUBLE_EQ(c(1,3),0);

    EXPECT_DOUBLE_EQ(c(2,0),0);
    EXPECT_DOUBLE_EQ(c(2,1),0);
    EXPECT_DOUBLE_EQ(c(2,2),1);
    EXPECT_DOUBLE_EQ(c(2,3),0);

    EXPECT_DOUBLE_EQ(c(3,0),0);
    EXPECT_DOUBLE_EQ(c(3,1),0);
    EXPECT_DOUBLE_EQ(c(3,2),0);
    EXPECT_DOUBLE_EQ(c(3,3),1);

    Vec3 vt(1,2,3);
    c.Translate(vt);
    c.Translate(vt);
    c.Translate(vt);
    c.Translate(vt);

    EXPECT_DOUBLE_EQ(c(0,0),1);
    EXPECT_DOUBLE_EQ(c(0,1),0);
    EXPECT_DOUBLE_EQ(c(0,2),0);
    EXPECT_DOUBLE_EQ(c(0,3),4);

    EXPECT_DOUBLE_EQ(c(1,0),0);
    EXPECT_DOUBLE_EQ(c(1,1),1);
    EXPECT_DOUBLE_EQ(c(1,2),0);
    EXPECT_DOUBLE_EQ(c(1,3),8);

    EXPECT_DOUBLE_EQ(c(2,0),0);
    EXPECT_DOUBLE_EQ(c(2,1),0);
    EXPECT_DOUBLE_EQ(c(2,2),1);
    EXPECT_DOUBLE_EQ(c(2,3),12);

    EXPECT_DOUBLE_EQ(c(3,0),0);
    EXPECT_DOUBLE_EQ(c(3,1),0);
    EXPECT_DOUBLE_EQ(c(3,2),0);
    EXPECT_DOUBLE_EQ(c(3,3),1);

}

TEST(Core_Vectors, Matrix4x4_Rotate_1) {
    using Matrix4x4=s21::matrix::Matrix4x4;
    using Matrix=s21::matrix::Matrix;

    Matrix4x4 c;
    c.SetToIdentity();
    c.Rotate(90,s21::basis::kBasisVectorX);
    Matrix m(4,4);

    m(0,0)=c(0,0);
    m(0,1)=c(0,1);
    m(0,2)=c(0,2);
    m(0,3)=c(0,3);

    m(1,0)=c(1,0);
    m(1,1)=c(1,1);
    m(1,2)=c(1,2);
    m(1,3)=c(1,3);

    m(2,0)=c(2,0);
    m(2,1)=c(2,1);
    m(2,2)=c(2,2);
    m(2,3)=c(2,3);

    m(3,0)=c(3,0);
    m(3,1)=c(3,1);
    m(3,2)=c(3,2);
    m(3,3)=c(3,3);

    Matrix vx(4,1);
    vx(0,0)=1;
    vx(1,0)=0;
    vx(2,0)=0;
    vx(3,0)=0;

    Matrix vy(4,1);
    vy(0,0)=0;
    vy(1,0)=1;
    vy(2,0)=0;
    vy(3,0)=0;

    Matrix vz(4,1);
    vz(0,0)=0;
    vz(1,0)=0;
    vz(2,0)=1;
    vz(3,0)=0;

    Matrix res=m*vx;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_DOUBLE_EQ(res(0,0),1);
    EXPECT_DOUBLE_EQ(res(1,0),0);
    EXPECT_DOUBLE_EQ(res(2,0),0);
    EXPECT_DOUBLE_EQ(res(3,0),0);

    res=m*vy;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),-1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),-1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);

    res=m*vz;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),-1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),-1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
}

TEST(Core_Vectors, Matrix4x4_Rotate_2) {
    using Matrix4x4=s21::matrix::Matrix4x4;
    using Matrix=s21::matrix::Matrix;

    Matrix4x4 c;
    c.SetToIdentity();
    c.Rotate(90,s21::basis::kBasisVectorY);
    Matrix m(4,4);

    m(0,0)=c(0,0);
    m(0,1)=c(0,1);
    m(0,2)=c(0,2);
    m(0,3)=c(0,3);

    m(1,0)=c(1,0);
    m(1,1)=c(1,1);
    m(1,2)=c(1,2);
    m(1,3)=c(1,3);

    m(2,0)=c(2,0);
    m(2,1)=c(2,1);
    m(2,2)=c(2,2);
    m(2,3)=c(2,3);

    m(3,0)=c(3,0);
    m(3,1)=c(3,1);
    m(3,2)=c(3,2);
    m(3,3)=c(3,3);

    Matrix vx(4,1);
    vx(0,0)=1;
    vx(1,0)=0;
    vx(2,0)=0;
    vx(3,0)=0;

    Matrix vy(4,1);
    vy(0,0)=0;
    vy(1,0)=1;
    vy(2,0)=0;
    vy(3,0)=0;

    Matrix vz(4,1);
    vz(0,0)=0;
    vz(1,0)=0;
    vz(2,0)=1;
    vz(3,0)=0;

    Matrix res=m*vx;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),-1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),-1,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),1,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);

    res=m*vy;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);

    res=m*vz;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),1,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),-1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),-1,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
}

TEST(Core_Vectors, Matrix4x4_Rotate_3) {
    using Matrix4x4=s21::matrix::Matrix4x4;
    using Matrix=s21::matrix::Matrix;

    Matrix4x4 c;
    c.SetToIdentity();
    c.Rotate(90,s21::basis::kBasisVectorZ);
    Matrix m(4,4);

    m(0,0)=c(0,0);
    m(0,1)=c(0,1);
    m(0,2)=c(0,2);
    m(0,3)=c(0,3);

    m(1,0)=c(1,0);
    m(1,1)=c(1,1);
    m(1,2)=c(1,2);
    m(1,3)=c(1,3);

    m(2,0)=c(2,0);
    m(2,1)=c(2,1);
    m(2,2)=c(2,2);
    m(2,3)=c(2,3);

    m(3,0)=c(3,0);
    m(3,1)=c(3,1);
    m(3,2)=c(3,2);
    m(3,3)=c(3,3);

    Matrix vx(4,1);
    vx(0,0)=1;
    vx(1,0)=0;
    vx(2,0)=0;
    vx(3,0)=0;

    Matrix vy(4,1);
    vy(0,0)=0;
    vy(1,0)=1;
    vy(2,0)=0;
    vy(3,0)=0;

    Matrix vz(4,1);
    vz(0,0)=0;
    vz(1,0)=0;
    vz(2,0)=1;
    vz(3,0)=0;

    Matrix res=m*vx;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),-1,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),-1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),1,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);

    res=m*vy;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),-1,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),-1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),1,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),1,1e-10);
    EXPECT_NEAR(res(2,0),0,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);

    res=m*vz;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),0,1e-10);
    EXPECT_NEAR(res(1,0),0,1e-10);
    EXPECT_NEAR(res(2,0),1,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
}

TEST(Core_Vectors, Matrix4x4_Scale) {
    using Matrix4x4=s21::matrix::Matrix4x4;
    using Matrix=s21::matrix::Matrix;

    Matrix4x4 c;
    c.SetToIdentity();
    c.Scale(1);
    Matrix m(4,4);

    m(0,0)=c(0,0);
    m(0,1)=c(0,1);
    m(0,2)=c(0,2);
    m(0,3)=c(0,3);

    m(1,0)=c(1,0);
    m(1,1)=c(1,1);
    m(1,2)=c(1,2);
    m(1,3)=c(1,3);

    m(2,0)=c(2,0);
    m(2,1)=c(2,1);
    m(2,2)=c(2,2);
    m(2,3)=c(2,3);

    m(3,0)=c(3,0);
    m(3,1)=c(3,1);
    m(3,2)=c(3,2);
    m(3,3)=c(3,3);

    Matrix v(4,1);
    v(0,0)=10;
    v(1,0)=10;
    v(2,0)=10;
    v(3,0)=0;

    Matrix res=v;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),10,1e-10);
    EXPECT_NEAR(res(1,0),10,1e-10);
    EXPECT_NEAR(res(2,0),10,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);

    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),10,1e-10);
    EXPECT_NEAR(res(1,0),10,1e-10);
    EXPECT_NEAR(res(2,0),10,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);

    c.SetToIdentity();
    c.Scale(0.5);
    for(int i=0;i<s21::matrix::Matrix4x4::kMatrixDimention;i++){
        for(int j=0;j<s21::matrix::Matrix4x4::kMatrixDimention;j++){
            m(i,j)=c(i,j);
        }
    }
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),5,1e-10);
    EXPECT_NEAR(res(1,0),5,1e-10);
    EXPECT_NEAR(res(2,0),5,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
    c.SetToIdentity();
    c.Scale(4);
    for(int i=0;i<s21::matrix::Matrix4x4::kMatrixDimention;i++){
        for(int j=0;j<s21::matrix::Matrix4x4::kMatrixDimention;j++){
            m(i,j)=c(i,j);
        }
    }
    res=m*res;
    EXPECT_EQ(res.getCols(),1);
    EXPECT_EQ(res.getRows(),4);
    EXPECT_NEAR(res(0,0),20,1e-10);
    EXPECT_NEAR(res(1,0),20,1e-10);
    EXPECT_NEAR(res(2,0),20,1e-10);
    EXPECT_NEAR(res(3,0),0,1e-10);
}

TEST(Core_Vectors, Matrix4x4_2) {
    using Matrix4x4=s21::matrix::Matrix4x4;
    using Matrix=s21::matrix::Matrix;

    Matrix4x4 a;
    EXPECT_DOUBLE_EQ(a(0,0),0);
    EXPECT_DOUBLE_EQ(a(0,1),0);
    EXPECT_DOUBLE_EQ(a(0,2),0);
    EXPECT_DOUBLE_EQ(a(0,3),0);

    EXPECT_DOUBLE_EQ(a(1,0),0);
    EXPECT_DOUBLE_EQ(a(1,1),0);
    EXPECT_DOUBLE_EQ(a(1,2),0);
    EXPECT_DOUBLE_EQ(a(1,3),0);

    EXPECT_DOUBLE_EQ(a(2,0),0);
    EXPECT_DOUBLE_EQ(a(2,1),0);
    EXPECT_DOUBLE_EQ(a(2,2),0);
    EXPECT_DOUBLE_EQ(a(2,3),0);

    EXPECT_DOUBLE_EQ(a(3,0),0);
    EXPECT_DOUBLE_EQ(a(3,1),0);
    EXPECT_DOUBLE_EQ(a(3,2),0);
    EXPECT_DOUBLE_EQ(a(3,3),0);

    Matrix4x4 b;
    b.SetToIdentity();
    Matrix4x4 res=a+b;
    EXPECT_DOUBLE_EQ(a(0,0),0);
    EXPECT_DOUBLE_EQ(a(0,1),0);
    EXPECT_DOUBLE_EQ(a(0,2),0);
    EXPECT_DOUBLE_EQ(a(0,3),0);

    EXPECT_DOUBLE_EQ(a(1,0),0);
    EXPECT_DOUBLE_EQ(a(1,1),0);
    EXPECT_DOUBLE_EQ(a(1,2),0);
    EXPECT_DOUBLE_EQ(a(1,3),0);

    EXPECT_DOUBLE_EQ(a(2,0),0);
    EXPECT_DOUBLE_EQ(a(2,1),0);
    EXPECT_DOUBLE_EQ(a(2,2),0);
    EXPECT_DOUBLE_EQ(a(2,3),0);

    EXPECT_DOUBLE_EQ(a(3,0),0);
    EXPECT_DOUBLE_EQ(a(3,1),0);
    EXPECT_DOUBLE_EQ(a(3,2),0);
    EXPECT_DOUBLE_EQ(a(3,3),0);


    EXPECT_DOUBLE_EQ(b(0,0),1);
    EXPECT_DOUBLE_EQ(b(0,1),0);
    EXPECT_DOUBLE_EQ(b(0,2),0);
    EXPECT_DOUBLE_EQ(b(0,3),0);

    EXPECT_DOUBLE_EQ(b(1,0),0);
    EXPECT_DOUBLE_EQ(b(1,1),1);
    EXPECT_DOUBLE_EQ(b(1,2),0);
    EXPECT_DOUBLE_EQ(b(1,3),0);

    EXPECT_DOUBLE_EQ(b(2,0),0);
    EXPECT_DOUBLE_EQ(b(2,1),0);
    EXPECT_DOUBLE_EQ(b(2,2),1);
    EXPECT_DOUBLE_EQ(b(2,3),0);

    EXPECT_DOUBLE_EQ(b(3,0),0);
    EXPECT_DOUBLE_EQ(b(3,1),0);
    EXPECT_DOUBLE_EQ(b(3,2),0);
    EXPECT_DOUBLE_EQ(b(3,3),1);


    EXPECT_DOUBLE_EQ(res(0,0),1);
    EXPECT_DOUBLE_EQ(res(0,1),0);
    EXPECT_DOUBLE_EQ(res(0,2),0);
    EXPECT_DOUBLE_EQ(res(0,3),0);

    EXPECT_DOUBLE_EQ(res(1,0),0);
    EXPECT_DOUBLE_EQ(res(1,1),1);
    EXPECT_DOUBLE_EQ(res(1,2),0);
    EXPECT_DOUBLE_EQ(res(1,3),0);

    EXPECT_DOUBLE_EQ(res(2,0),0);
    EXPECT_DOUBLE_EQ(res(2,1),0);
    EXPECT_DOUBLE_EQ(res(2,2),1);
    EXPECT_DOUBLE_EQ(res(2,3),0);

    EXPECT_DOUBLE_EQ(res(3,0),0);
    EXPECT_DOUBLE_EQ(res(3,1),0);
    EXPECT_DOUBLE_EQ(res(3,2),0);
    EXPECT_DOUBLE_EQ(res(3,3),1);

    res+=b;
    EXPECT_DOUBLE_EQ(b(0,0),1);
    EXPECT_DOUBLE_EQ(b(0,1),0);
    EXPECT_DOUBLE_EQ(b(0,2),0);
    EXPECT_DOUBLE_EQ(b(0,3),0);

    EXPECT_DOUBLE_EQ(b(1,0),0);
    EXPECT_DOUBLE_EQ(b(1,1),1);
    EXPECT_DOUBLE_EQ(b(1,2),0);
    EXPECT_DOUBLE_EQ(b(1,3),0);

    EXPECT_DOUBLE_EQ(b(2,0),0);
    EXPECT_DOUBLE_EQ(b(2,1),0);
    EXPECT_DOUBLE_EQ(b(2,2),1);
    EXPECT_DOUBLE_EQ(b(2,3),0);

    EXPECT_DOUBLE_EQ(b(3,0),0);
    EXPECT_DOUBLE_EQ(b(3,1),0);
    EXPECT_DOUBLE_EQ(b(3,2),0);
    EXPECT_DOUBLE_EQ(b(3,3),1);


    EXPECT_DOUBLE_EQ(res(0,0),2);
    EXPECT_DOUBLE_EQ(res(0,1),0);
    EXPECT_DOUBLE_EQ(res(0,2),0);
    EXPECT_DOUBLE_EQ(res(0,3),0);

    EXPECT_DOUBLE_EQ(res(1,0),0);
    EXPECT_DOUBLE_EQ(res(1,1),2);
    EXPECT_DOUBLE_EQ(res(1,2),0);
    EXPECT_DOUBLE_EQ(res(1,3),0);

    EXPECT_DOUBLE_EQ(res(2,0),0);
    EXPECT_DOUBLE_EQ(res(2,1),0);
    EXPECT_DOUBLE_EQ(res(2,2),2);
    EXPECT_DOUBLE_EQ(res(2,3),0);

    EXPECT_DOUBLE_EQ(res(3,0),0);
    EXPECT_DOUBLE_EQ(res(3,1),0);
    EXPECT_DOUBLE_EQ(res(3,2),0);
    EXPECT_DOUBLE_EQ(res(3,3),2);

    a=b-res;
    EXPECT_DOUBLE_EQ(b(0,0),1);
    EXPECT_DOUBLE_EQ(b(0,1),0);
    EXPECT_DOUBLE_EQ(b(0,2),0);
    EXPECT_DOUBLE_EQ(b(0,3),0);

    EXPECT_DOUBLE_EQ(b(1,0),0);
    EXPECT_DOUBLE_EQ(b(1,1),1);
    EXPECT_DOUBLE_EQ(b(1,2),0);
    EXPECT_DOUBLE_EQ(b(1,3),0);

    EXPECT_DOUBLE_EQ(b(2,0),0);
    EXPECT_DOUBLE_EQ(b(2,1),0);
    EXPECT_DOUBLE_EQ(b(2,2),1);
    EXPECT_DOUBLE_EQ(b(2,3),0);

    EXPECT_DOUBLE_EQ(b(3,0),0);
    EXPECT_DOUBLE_EQ(b(3,1),0);
    EXPECT_DOUBLE_EQ(b(3,2),0);
    EXPECT_DOUBLE_EQ(b(3,3),1);


    EXPECT_DOUBLE_EQ(res(0,0),2);
    EXPECT_DOUBLE_EQ(res(0,1),0);
    EXPECT_DOUBLE_EQ(res(0,2),0);
    EXPECT_DOUBLE_EQ(res(0,3),0);

    EXPECT_DOUBLE_EQ(res(1,0),0);
    EXPECT_DOUBLE_EQ(res(1,1),2);
    EXPECT_DOUBLE_EQ(res(1,2),0);
    EXPECT_DOUBLE_EQ(res(1,3),0);

    EXPECT_DOUBLE_EQ(res(2,0),0);
    EXPECT_DOUBLE_EQ(res(2,1),0);
    EXPECT_DOUBLE_EQ(res(2,2),2);
    EXPECT_DOUBLE_EQ(res(2,3),0);

    EXPECT_DOUBLE_EQ(res(3,0),0);
    EXPECT_DOUBLE_EQ(res(3,1),0);
    EXPECT_DOUBLE_EQ(res(3,2),0);
    EXPECT_DOUBLE_EQ(res(3,3),2);


    EXPECT_DOUBLE_EQ(a(0,0),-1);
    EXPECT_DOUBLE_EQ(a(0,1),0);
    EXPECT_DOUBLE_EQ(a(0,2),0);
    EXPECT_DOUBLE_EQ(a(0,3),0);

    EXPECT_DOUBLE_EQ(a(1,0),0);
    EXPECT_DOUBLE_EQ(a(1,1),-1);
    EXPECT_DOUBLE_EQ(a(1,2),0);
    EXPECT_DOUBLE_EQ(a(1,3),0);

    EXPECT_DOUBLE_EQ(a(2,0),0);
    EXPECT_DOUBLE_EQ(a(2,1),0);
    EXPECT_DOUBLE_EQ(a(2,2),-1);
    EXPECT_DOUBLE_EQ(a(2,3),0);

    EXPECT_DOUBLE_EQ(a(3,0),0);
    EXPECT_DOUBLE_EQ(a(3,1),0);
    EXPECT_DOUBLE_EQ(a(3,2),0);
    EXPECT_DOUBLE_EQ(a(3,3),-1);

    a-=res;
    EXPECT_DOUBLE_EQ(res(0,0),2);
    EXPECT_DOUBLE_EQ(res(0,1),0);
    EXPECT_DOUBLE_EQ(res(0,2),0);
    EXPECT_DOUBLE_EQ(res(0,3),0);

    EXPECT_DOUBLE_EQ(res(1,0),0);
    EXPECT_DOUBLE_EQ(res(1,1),2);
    EXPECT_DOUBLE_EQ(res(1,2),0);
    EXPECT_DOUBLE_EQ(res(1,3),0);

    EXPECT_DOUBLE_EQ(res(2,0),0);
    EXPECT_DOUBLE_EQ(res(2,1),0);
    EXPECT_DOUBLE_EQ(res(2,2),2);
    EXPECT_DOUBLE_EQ(res(2,3),0);

    EXPECT_DOUBLE_EQ(res(3,0),0);
    EXPECT_DOUBLE_EQ(res(3,1),0);
    EXPECT_DOUBLE_EQ(res(3,2),0);
    EXPECT_DOUBLE_EQ(res(3,3),2);

    
    EXPECT_DOUBLE_EQ(a(0,0),-3);
    EXPECT_DOUBLE_EQ(a(0,1),0);
    EXPECT_DOUBLE_EQ(a(0,2),0);
    EXPECT_DOUBLE_EQ(a(0,3),0);

    EXPECT_DOUBLE_EQ(a(1,0),0);
    EXPECT_DOUBLE_EQ(a(1,1),-3);
    EXPECT_DOUBLE_EQ(a(1,2),0);
    EXPECT_DOUBLE_EQ(a(1,3),0);

    EXPECT_DOUBLE_EQ(a(2,0),0);
    EXPECT_DOUBLE_EQ(a(2,1),0);
    EXPECT_DOUBLE_EQ(a(2,2),-3);
    EXPECT_DOUBLE_EQ(a(2,3),0);

    EXPECT_DOUBLE_EQ(a(3,0),0);
    EXPECT_DOUBLE_EQ(a(3,1),0);
    EXPECT_DOUBLE_EQ(a(3,2),0);
    EXPECT_DOUBLE_EQ(a(3,3),-3);

    Matrix m(4,4);
    m(0,0)=5;
    m(0,1)=0;
    m(0,2)=0;
    m(0,3)=0;

    m(1,0)=0;
    m(1,1)=0;
    m(1,2)=0;
    m(1,3)=0;

    m(2,0)=0;
    m(2,1)=0;
    m(2,2)=0;
    m(2,3)=0;

    m(3,0)=0;
    m(3,1)=0;
    m(3,2)=0;
    m(3,3)=0;
    Matrix4x4 c(m);

    res=a*c;
    EXPECT_DOUBLE_EQ(a(0,0),-3);
    EXPECT_DOUBLE_EQ(a(0,1),0);
    EXPECT_DOUBLE_EQ(a(0,2),0);
    EXPECT_DOUBLE_EQ(a(0,3),0);

    EXPECT_DOUBLE_EQ(a(1,0),0);
    EXPECT_DOUBLE_EQ(a(1,1),-3);
    EXPECT_DOUBLE_EQ(a(1,2),0);
    EXPECT_DOUBLE_EQ(a(1,3),0);

    EXPECT_DOUBLE_EQ(a(2,0),0);
    EXPECT_DOUBLE_EQ(a(2,1),0);
    EXPECT_DOUBLE_EQ(a(2,2),-3);
    EXPECT_DOUBLE_EQ(a(2,3),0);

    EXPECT_DOUBLE_EQ(a(3,0),0);
    EXPECT_DOUBLE_EQ(a(3,1),0);
    EXPECT_DOUBLE_EQ(a(3,2),0);
    EXPECT_DOUBLE_EQ(a(3,3),-3);


    EXPECT_DOUBLE_EQ(c(0,0),5);
    EXPECT_DOUBLE_EQ(c(0,1),0);
    EXPECT_DOUBLE_EQ(c(0,2),0);
    EXPECT_DOUBLE_EQ(c(0,3),0);

    EXPECT_DOUBLE_EQ(c(1,0),0);
    EXPECT_DOUBLE_EQ(c(1,1),0);
    EXPECT_DOUBLE_EQ(c(1,2),0);
    EXPECT_DOUBLE_EQ(c(1,3),0);

    EXPECT_DOUBLE_EQ(c(2,0),0);
    EXPECT_DOUBLE_EQ(c(2,1),0);
    EXPECT_DOUBLE_EQ(c(2,2),0);
    EXPECT_DOUBLE_EQ(c(2,3),0);

    EXPECT_DOUBLE_EQ(c(3,0),0);
    EXPECT_DOUBLE_EQ(c(3,1),0);
    EXPECT_DOUBLE_EQ(c(3,2),0);
    EXPECT_DOUBLE_EQ(c(3,3),0);


    EXPECT_DOUBLE_EQ(res(0,0),-15);
    EXPECT_DOUBLE_EQ(res(0,1),0);
    EXPECT_DOUBLE_EQ(res(0,2),0);
    EXPECT_DOUBLE_EQ(res(0,3),0);

    EXPECT_DOUBLE_EQ(res(1,0),0);
    EXPECT_DOUBLE_EQ(res(1,1),0);
    EXPECT_DOUBLE_EQ(res(1,2),0);
    EXPECT_DOUBLE_EQ(res(1,3),0);

    EXPECT_DOUBLE_EQ(res(2,0),0);
    EXPECT_DOUBLE_EQ(res(2,1),0);
    EXPECT_DOUBLE_EQ(res(2,2),0);
    EXPECT_DOUBLE_EQ(res(2,3),0);

    EXPECT_DOUBLE_EQ(res(3,0),0);
    EXPECT_DOUBLE_EQ(res(3,1),0);
    EXPECT_DOUBLE_EQ(res(3,2),0);
    EXPECT_DOUBLE_EQ(res(3,3),0);

    res*=c;
    EXPECT_DOUBLE_EQ(res(0,0),-75);
    EXPECT_DOUBLE_EQ(res(0,1),0);
    EXPECT_DOUBLE_EQ(res(0,2),0);
    EXPECT_DOUBLE_EQ(res(0,3),0);

    EXPECT_DOUBLE_EQ(res(1,0),0);
    EXPECT_DOUBLE_EQ(res(1,1),0);
    EXPECT_DOUBLE_EQ(res(1,2),0);
    EXPECT_DOUBLE_EQ(res(1,3),0);

    EXPECT_DOUBLE_EQ(res(2,0),0);
    EXPECT_DOUBLE_EQ(res(2,1),0);
    EXPECT_DOUBLE_EQ(res(2,2),0);
    EXPECT_DOUBLE_EQ(res(2,3),0);

    EXPECT_DOUBLE_EQ(res(3,0),0);
    EXPECT_DOUBLE_EQ(res(3,1),0);
    EXPECT_DOUBLE_EQ(res(3,2),0);
    EXPECT_DOUBLE_EQ(res(3,3),0);


    EXPECT_DOUBLE_EQ(c(0,0),5);
    EXPECT_DOUBLE_EQ(c(0,1),0);
    EXPECT_DOUBLE_EQ(c(0,2),0);
    EXPECT_DOUBLE_EQ(c(0,3),0);

    EXPECT_DOUBLE_EQ(c(1,0),0);
    EXPECT_DOUBLE_EQ(c(1,1),0);
    EXPECT_DOUBLE_EQ(c(1,2),0);
    EXPECT_DOUBLE_EQ(c(1,3),0);

    EXPECT_DOUBLE_EQ(c(2,0),0);
    EXPECT_DOUBLE_EQ(c(2,1),0);
    EXPECT_DOUBLE_EQ(c(2,2),0);
    EXPECT_DOUBLE_EQ(c(2,3),0);

    EXPECT_DOUBLE_EQ(c(3,0),0);
    EXPECT_DOUBLE_EQ(c(3,1),0);
    EXPECT_DOUBLE_EQ(c(3,2),0);
    EXPECT_DOUBLE_EQ(c(3,3),0);

    res=m;
    EXPECT_DOUBLE_EQ(res(0,0),5);
    EXPECT_DOUBLE_EQ(res(0,1),0);
    EXPECT_DOUBLE_EQ(res(0,2),0);
    EXPECT_DOUBLE_EQ(res(0,3),0);

    EXPECT_DOUBLE_EQ(res(1,0),0);
    EXPECT_DOUBLE_EQ(res(1,1),0);
    EXPECT_DOUBLE_EQ(res(1,2),0);
    EXPECT_DOUBLE_EQ(res(1,3),0);

    EXPECT_DOUBLE_EQ(res(2,0),0);
    EXPECT_DOUBLE_EQ(res(2,1),0);
    EXPECT_DOUBLE_EQ(res(2,2),0);
    EXPECT_DOUBLE_EQ(res(2,3),0);

    EXPECT_DOUBLE_EQ(res(3,0),0);
    EXPECT_DOUBLE_EQ(res(3,1),0);
    EXPECT_DOUBLE_EQ(res(3,2),0);
    EXPECT_DOUBLE_EQ(res(3,3),0);

    a=res;
    EXPECT_DOUBLE_EQ(a(0,0),5);
    EXPECT_DOUBLE_EQ(a(0,1),0);
    EXPECT_DOUBLE_EQ(a(0,2),0);
    EXPECT_DOUBLE_EQ(a(0,3),0);

    EXPECT_DOUBLE_EQ(a(1,0),0);
    EXPECT_DOUBLE_EQ(a(1,1),0);
    EXPECT_DOUBLE_EQ(a(1,2),0);
    EXPECT_DOUBLE_EQ(a(1,3),0);

    EXPECT_DOUBLE_EQ(a(2,0),0);
    EXPECT_DOUBLE_EQ(a(2,1),0);
    EXPECT_DOUBLE_EQ(a(2,2),0);
    EXPECT_DOUBLE_EQ(a(2,3),0);

    EXPECT_DOUBLE_EQ(a(3,0),0);
    EXPECT_DOUBLE_EQ(a(3,1),0);
    EXPECT_DOUBLE_EQ(a(3,2),0);
    EXPECT_DOUBLE_EQ(a(3,3),0);

    Matrix m2(3,3);
    EXPECT_THROW(a=m2, std::exception);
    EXPECT_THROW( Matrix4x4 d(m2), std::exception);

    a.SetToIdentity();
    b.SetToIdentity();

    EXPECT_EQ(a==b,true);
    EXPECT_EQ(a==res,false);
    EXPECT_EQ(a!=res,true);

    EXPECT_THROW(a(-1,0), std::exception);
    EXPECT_THROW(a(5,0), std::exception);
    EXPECT_THROW(a(4,0), std::exception);
}

TEST(Core_Service, Service_1) {
    double d{5.5};
    EXPECT_NEAR (s21::service::converters::DoubleToFloat(d),5.5,1e-7);
    d=std::numeric_limits<float>::max()*1.5;
    EXPECT_NEAR (s21::service::converters::DoubleToFloat(d),std::numeric_limits<float>::max(),1e-7);
    d=std::numeric_limits<float>::lowest()*1.5;
    EXPECT_NEAR (s21::service::converters::DoubleToFloat(d),std::numeric_limits<float>::lowest(),1e-7);
    d=std::numeric_limits<float>::min()/2;
    EXPECT_NEAR (s21::service::converters::DoubleToFloat(d),std::numeric_limits<float>::min(),1e-7);
    d=-std::numeric_limits<float>::min()/2;
    EXPECT_NEAR (s21::service::converters::DoubleToFloat(d),-std::numeric_limits<float>::min(),1e-7);

}