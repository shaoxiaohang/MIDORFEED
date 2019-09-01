#pragma once

#include<vector>
#include<Core/Vector3f.h>
namespace vrv
{
   class Matrix3f
   {
   public:
      Matrix3f();

      Matrix3f(float a00, float a01, float a02,
         float a10, float a11, float a12,
         float a20, float a21, float a22);

      bool operator != (const Matrix3f& r);

      bool operator == (const Matrix3f& r);

      Matrix3f operator*(const Matrix3f& r);

      Vector3f operator*(const Vector3f& r);

      Vector3f operator[] (unsigned index) const;

      static Matrix3f makeTranslate(float x, float y);

      static Matrix3f makeScale(float x, float y);

      static Matrix3f makeWindowingTransformation(float l1, float b1, float r1, float t1,
         float l2, float b2, float r2, float t2);

      static Matrix3f makeRotationX(float degree);

      static Matrix3f makeRotationY(float degree);

      static Matrix3f makeRotationZ(float degree);

   public:
      std::vector<float> m;
   };
}