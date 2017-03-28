#pragma once
#include <Core/Vector3.h>
namespace vrv
{
	template<typename T>
	class Vector4
	{
	public:
		Vector4(){}
		Vector4(T _x, T _y, T _z, T _w)
			: x(_x)
			, y(_y)
			, z(_z)
			, w(_w){}
		Vector4(Vector3 vec3, T w)
			: x(vec3.x)
			, y(vec3.y)
			, z(vec3.z)
			, w(w){}

		void operator =(const Vector4<T>& right)
		{
			x = right.x;
			y = right.y;
			z = right.z;
			w = right.w;
		}

		bool operator ==(const Vector4<T>& right)
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

		bool operator !=(const Vector4<T>& right)
		{
			return !((*this) == right);
		}

		T operator +(const Vector4<T>& right)
		{
			x += right.x;
			y += right.y;
			z += right.z;
			w += right.w;
			return *this;
		}

		T operator -(const Vector4<T>& right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
			w -= right.w;
			return *this;
		}

		Vector4 operator / (float d)
		{
			return Vector4<T>(x / d, y / d, z / d, w / d);
		}


		T x;
		T y;
		T z;
		T w;

	};

	typedef Vector4<float> Vector4f;
	typedef Vector4<double> Vector4d;
}