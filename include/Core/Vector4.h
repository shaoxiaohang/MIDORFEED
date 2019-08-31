#pragma once
#include <Core/Vector3.h>
namespace vrv
{
   template<typename T>
	class Vector4
	{
	public:
      Vector4();

      Vector4(float _x, float _y, float _z, float _w);

      Vector4(Vector3 vec3, float w);

      Vector4(Vector3 vec3);

      Vector4& operator =(const Vector4& right);

      bool operator ==(const Vector4& right);

      bool operator !=(const Vector4& right);

      Vector4 operator +(const Vector4& right);

      Vector4 operator -(const Vector4& right);

      Vector4 operator -() const;

      Vector4 operator / (float d);

      T operator[](unsigned int index) const;

      T x() const;

      T y() const;

      T z() const;

      T w() const;

   protected:

      T data[4];

	};

}