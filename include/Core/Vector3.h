#pragma once

namespace vrv
{
	template<typename T>
	class Vector3
	{
	public:
		Vector3(){}
		Vector3(T _x, T _y, T _z, T _w)
			: x(_x)
			, y(_y)
			, z(_z)
			{}

		void operator =(const Vector3<T>& right)
		{
			x = right.x;
			y = right.y;
			z = right.z;
		}

		bool operator ==(const Vector3<T>& right)
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

		bool operator !=(const Vector3<T>& right)
		{
			return !((*this) == right);
		}

		T operator +(const Vector3<T>& right)
		{
			x += right.x;
			y += right.y;
			z += right.z;
			return *this;
		}

		T operator -(const Vector3<T>& right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
			return *this;
		}


		T x;
		T y;
		T z;

	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
}