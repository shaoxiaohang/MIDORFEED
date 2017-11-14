#include <Core/Vector3.h>
#include <Core/Utility.h>
namespace vrv
{
	Vector3f::Vector3f()
		: x(0)
		, y(0)
		, z(0)
	{}

	Vector3f::Vector3f(Vector2f vec)
		: x(vec.x)
		, y(vec.y)
		, z(0)
	{}

	Vector3f::Vector3f(float _x, float _y, float _z)
		: x(_x)
		, y(_y)
		, z(_z)
	{}

	void Vector3f::operator =(const Vector3f& right)
	{
		x = right.x;
		y = right.y;
		z = right.z;
	}

	bool Vector3f::operator ==(const Vector3f& right)
	{
		if (x == right.x && y == right.y && z == right.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Vector3f::operator !=(const Vector3f& right)
	{
		return !((*this) == right);
	}

	Vector3f Vector3f::operator +=(const Vector3f& right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	}

	Vector3f Vector3f::operator -=(const Vector3f& right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	Vector3f Vector3f::operator +(const Vector3f& right)
	{
		return Vector3f(x + right.x, y + right.y, z + right.z);
	}

	Vector3f Vector3f::operator -(const Vector3f& right)
	{
		return Vector3f(x - right.x, y - right.y, z - right.z);
	}

	Vector3f Vector3f::operator /(float mag)
	{
		return Vector3f(x/mag, y/mag, z/mag);
	}

	Vector3f Vector3f::operator -()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	Vector3f Vector3f::operator *(float mag)
	{
		return Vector3f(x * mag, y * mag, z * mag);
	}

	Vector3f Vector3f::normalize()
	{
		float mag = Utility::sqrt(x*x + y*y + z*z);
		return (*this) / mag;
	}

	Vector3f Vector3f::crossProduct(const Vector3f& right)
	{
		return Vector3f(y*right.z - z*right.y, z*right.x - x*right.z, x*right.y - y*right.x);
	}

	float Vector3f::distanceSquare(const Vector3f& right)
	{
		return (x - right.x)*(x - right.x) + (y - right.y)*(y - right.y)+(z - right.z)* (z - right.z);
	}
}