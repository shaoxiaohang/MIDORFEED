#pragma once
#include <Core/Vector2f.h>
#include <Core/Utility.h>
namespace vrv
{
   class Vector4f;
   class Vector3f
   {
   public:
      Vector3f();

      Vector3f(float scalar);

      Vector3f(Vector2f vec);

      Vector3f(float x, float y, float z);

      Vector3f& operator =(const Vector3f& right);

      Vector3f& Vector3f::operator = (const Vector4f& vec4);

      bool operator ==(const Vector3f& right);

      bool operator !=(const Vector3f& right);

      Vector3f operator +=(const Vector3f& right);

      Vector3f operator -=(const Vector3f& right);

      Vector3f operator +(const Vector3f& right);

      Vector3f operator -(const Vector3f& right);

      Vector3f operator *(const Vector3f& right);

      Vector3f operator /(float mag) const;

      Vector3f operator -() const;

      Vector3f operator *(float mag);

      float Vector3f::operator[] (unsigned int index) const;

      float Vector3f::x() const;

      float Vector3f::y() const;

      float Vector3f::z() const;

      float& Vector3f::x();

      float& Vector3f::y();

      float& Vector3f::z();

      void Vector3f::normalize();

      Vector3f Vector3f::normalizedVector() const;

      float Vector3f::dotProduct(const Vector3f& right);

      Vector3f Vector3f::crossProduct(const Vector3f& right);

      float Vector3f::distanceSquare(const Vector3f& right);

      float Vector3f::length();

      float Vector3f::angelBetween(const Vector3f& right);

      Vector3f Vector3f::rotateAroundAxis(Vector3f axis, float degree);

   private:
      float data[3];

   };

}
