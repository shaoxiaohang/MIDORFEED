#pragma once
#include <Core/Vector2.h>
namespace vrv
{
	class Vector3f
	{
	public:
		Vector3f();

		Vector3f(float);

		Vector3f(Vector2f);

		Vector3f(float x, float y, float z);

      Vector3f& operator =(const Vector3f& right);

		bool operator ==(const Vector3f& right);

		bool operator !=(const Vector3f& right);

		Vector3f operator +=(const Vector3f& right);

		Vector3f operator -=(const Vector3f& right);

		Vector3f operator +(const Vector3f& right);

		Vector3f operator -(const Vector3f& right);

		Vector3f operator *(const Vector3f& right);

		Vector3f operator /(float mag) const;

		Vector3f operator -() const;

		Vector3f operator *(float);

      float x() const;

      float y() const;

      float z() const;

      float& x() ;

      float& y() ;

      float& z() ;

      float operator[] (unsigned int) const;

		void normalize();

      Vector3f normalizedVector() const;

		float dotProduct(const Vector3f& right);

		Vector3f crossProduct(const Vector3f& right);

		float distanceSquare(const Vector3f& right);

		float magnitude();

		float angelBetween(const Vector3f& right);

		Vector3f Vector3f::rotateAroundAxis(Vector3f axis, double degree);

   private:
      float data[3];

	};

}