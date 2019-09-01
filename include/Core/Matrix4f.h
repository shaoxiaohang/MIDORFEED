#pragma once
#include <vector>
#include <Core/Vector3f.h>
#include <Core/Vector4f.h>
namespace vrv
{
   class Matrix3f;
   class Matrix4f
   {
   public:

      Matrix4f();

      Matrix4f(float a00, float a01, float a02, float a03,
         float a10, float a11, float a12, float a13,
         float a20, float a21, float a22, float a23,
         float a30, float a31, float a32, float a33);

      Matrix4f(const Matrix3f& m);

      bool operator != (const Matrix4f& r);

      bool operator == (const Matrix4f& r);

      Vector4f operator[] (unsigned int index) const;

      void setColumn(int column, Vector4f vec);

      static Matrix4f makeTranslate(Vector3f);

      static Matrix4f makeTranslate(float x, float y, float z);

      static Matrix4f makeScale(float x, float y, float z);

      static Matrix4f makeRotateX(float degree);

      static Matrix4f makeRotateY(float degree);

      static Matrix4f makeRotateZ(float degree);

      void scale(float uniformScale);

      void scale(float x, float y, float z);

      Vector4f operator*(const Vector3f& vec);

      Vector4f operator*(const Vector4f& vec);

      Matrix4f operator*(const Matrix4f& r);

      static Matrix4f makeWindowingTransformation(float l1, float b1, float n1,
         float r1, float t1, float f1,
         float l2, float b2, float n2,
         float r2, float t2, float f2);

      static Matrix4f makeProjection(float l, float r, float b, float t, float n, float f);

      static Matrix4f makeProjection(float verticalFieldOfView, float ratioWDivedeH, float n, float f);

      static Matrix4f makeFrameToCanonical(Vector3f e, Vector3f u, Vector3f v, Vector3f w);

      static Matrix4f makeCanonicalToFrame(Vector3f e, Vector3f u, Vector3f v, Vector3f w);

      static Matrix4f makeLookAtMatrix(Vector3f pos, Vector3f center, Vector3f up);

      static Matrix4f makeOrthoMatrix(float l, float r, float b, float t, float n, float f);

      Vector3f getTranslation() const;
   public:
      std::vector<float> m;
   };

}