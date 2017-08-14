#pragma once

namespace vrv
{
	class Vector3f
	{
	public:
		Vector3f();
		Vector3f(float _x, float _y, float _z);
		void operator =(const Vector3f& right);
		bool operator ==(const Vector3f& right);
		bool operator !=(const Vector3f& right);
		Vector3f operator +=(const Vector3f& right);
		Vector3f operator -=(const Vector3f& right);
		Vector3f operator +(const Vector3f& right);
		Vector3f operator -(const Vector3f& right);
		Vector3f operator /(float mag);
		Vector3f operator -();
		Vector3f operator *(float);
		Vector3f normalize();

		Vector3f crossProduct(const Vector3f& right);
		float distanceSquare(const Vector3f& right);

		float x;
		float y;
		float z;

	};

}