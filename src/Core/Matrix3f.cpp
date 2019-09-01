#include <Core/Matrix3f.h>
#include <Core/Utility.h>
#include <cstring>
namespace vrv
{
   Matrix3f::Matrix3f()
   {
      m.resize(9);
      m[0] = 1; m[1] = 0; m[2] = 0;
      m[3] = 0; m[4] = 1; m[5] = 0;
      m[6] = 0; m[7] = 0; m[8] = 1;
   }

   Matrix3f::Matrix3f(float a00, float a01, float a02,
      float a10, float a11, float a12,
      float a20, float a21, float a22)
   {
      m.resize(9);
      m[0] = a00; m[1] = a10; m[2] = a20;
      m[3] = a01; m[4] = a11; m[5] = a21;
      m[6] = a02; m[7] = a12; m[8] = a22;
   }

   bool Matrix3f::operator != (const Matrix3f& r)
   {
      return !(*this == r);
   }

   bool Matrix3f::operator == (const Matrix3f& r)
   {
      return m[0] == r.m[0] && m[1] == r.m[1] && m[2] == r.m[2] &&
         m[3] == r.m[3] && m[4] == r.m[4] && m[5] == r.m[5] &&
         m[6] == r.m[6] && m[7] == r.m[7] && m[8] == r.m[8];
   }

   Matrix3f Matrix3f::operator*(const Matrix3f& r)
   {
      return Matrix3f
      (m[0] * r.m[0] + m[3] * r.m[1] + m[6] * r.m[2], m[0] * r.m[3] + m[3] * r.m[4] + m[6] * r.m[5], m[0] * r.m[6] + m[3] * r.m[7] + m[6] * r.m[8],
         m[1] * r.m[0] + m[4] * r.m[1] + m[7] * r.m[2], m[1] * r.m[3] + m[4] * r.m[4] + m[7] * r.m[5], m[1] * r.m[6] + m[4] * r.m[7] + m[7] * r.m[8],
         m[2] * r.m[0] + m[5] * r.m[1] + m[8] * r.m[2], m[2] * r.m[3] + m[5] * r.m[4] + m[8] * r.m[5], m[2] * r.m[6] + m[5] * r.m[7] + m[8] * r.m[8]);
   }

   Vector3f Matrix3f::operator*(const Vector3f & r)
   {
      return Vector3f(m[0] * r.x() + m[3] * r.y() + m[6] * r.z(), m[1] * r.x() + m[4] * r.y() + m[7] * r.z(), m[2] * r.x() + m[5] * r.y() + m[8] * r.z());
   }

   Vector3f Matrix3f::operator[] (unsigned index) const
   {
      return Vector3f(m[index * 3], m[index * 3] + 1, m[index * 3] + 2);
   }

   Matrix3f Matrix3f::makeTranslate(float x, float y)
   {
      return Matrix3f(1, 0, x,
         0, 1, y,
         0, 0, 1);
   }

   Matrix3f Matrix3f::makeScale(float x, float y)
   {
      return Matrix3f(x, 0, 0,
         0, y, 0,
         0, 0, 1);
   }

   Matrix3f  Matrix3f::makeWindowingTransformation(float l1, float b1, float r1, float t1,
      float l2, float b2, float r2, float t2)
   {
      return makeTranslate(l2, b2)*makeScale((r2 - l2) / (r1 - l1), (t2 - b2) / (t1 - b1))*makeTranslate(-l1, -b1);
   }

   Matrix3f Matrix3f::makeRotationX(float degree)
   {
      float cos = Utility::cos(degree);
      float sin = Utility::sin(degree);
      return Matrix3f(1, 0, 0, 0, cos, -sin, 0, sin, cos);
   }

   Matrix3f Matrix3f::makeRotationY(float degree)
   {
      float cos = Utility::cos(degree);
      float sin = Utility::sin(degree);
      return Matrix3f(cos, 0, sin, 0, 1, 0, -sin, 0, cos);
   }

   Matrix3f Matrix3f::makeRotationZ(float degree)
   {
      float cos = Utility::cos(degree);
      float sin = Utility::sin(degree);
      return Matrix3f(cos, -sin, 0, sin, cos, 0, 0, 0, 1);
   }
}