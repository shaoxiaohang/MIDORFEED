#include <Core/Vector4.h>

namespace vrv
{
	Vector4f::Vector4f()
		: x(0)
		, y(0)
		, z(0)
		, w(0)
	{}

	Vector4f::Vector4f(float _x, float _y, float _z, float _w)
		: x(_x)
		, y(_y)
		, z(_z)
		, w(_w)
	{
	}

	Vector4f::Vector4f(Vector3f vec3, float w)
		: x(vec3.x)
		, y(vec3.y)
		, z(vec3.z)
		, w(w)
	{}

	Vector4f::Vector4f(Vector3f vec3)
		: x(vec3.x)
		, y(vec3.y)
		, z(vec3.z)
		, w(1){}

	Vector4f::operator Vector3f()
	{
		return Vector3f(x, y, z);
	}

	void Vector4f::operator =(const Vector4f& right)
	{
		x = right.x;
		y = right.y;
		z = right.z;
		w = right.w;
	}

	bool Vector4f::operator ==(const Vector4f& right)
	{
		if (x == right.x && y == right.y && z == right.z && w == right.w)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Vector4f::operator !=(const Vector4f& right)
	{
		return !((*this) == right);
	}

	Vector4f Vector4f::operator +(const Vector4f& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		w += right.w;
		return *this;
	}

	Vector4f Vector4f::operator -(const Vector4f& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		w -= right.w;
		return *this;
	}

	Vector4f Vector4f::operator -()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		return *this;
	}

	Vector4f Vector4f::operator / (float d)
	{
		return Vector4f(x / d, y / d, z / d, w / d);
	}

}