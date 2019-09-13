#pragma once
#include <Core/Vector3f.h>
namespace vrv
{
   class Vector4f
   {
   public:
      Vector4f::Vector4f();

      Vector4f::Vector4f(float x, float y, float z, float w);

      Vector4f::Vector4f(const Vector3f& vec3);

      Vector4f& Vector4f::operator = (const Vector3f& vec3);

      Vector4f::Vector4f(Vector3f vec3, float w);

      Vector4f::Vector4f(Vector3f vec3);

      Vector4f& Vector4f::operator =(const Vector4f& right);

      bool Vector4f::operator ==(const Vector4f& right);

      bool Vector4f::operator !=(const Vector4f& right);

      Vector4f Vector4f::operator +(const Vector4f& right);

      Vector4f Vector4f::operator -(const Vector4f& right);

      Vector4f Vector4f::operator -() const;

      Vector4f Vector4f::operator / (float d);

      float Vector4f::operator[](unsigned int index) const;

      float Vector4f::x() const;

      float Vector4f::y() const;

      float Vector4f::z() const;

      float Vector4f::w() const;

      float& Vector4f::x();

      float& Vector4f::y();

      float& Vector4f::z();

      float& Vector4f::w();

      Vector3f xyz();

   protected:

      float data[4];

   };

}