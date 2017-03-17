#pragma once

namespace vrv
{
	template<typename T>
	class Vector2
	{
	public:
		Vector2(){}
		Vector2(T _x, T _y)
			: x(_x)
			, y(_y)
		{}

		void operator =(const Vector2<T>& right)
		{
			x = right.x;
			y = right.y;
		}

		bool operator ==(const Vector2<T>& right)
		{
			if (x == right.x && y == right.y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		bool operator !=(const Vector2<T>& right)
		{
			return !((*this) == right);
		}

		T operator +(const Vector2<T>& right)
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		T operator -(const Vector2<T>& right)
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		T x;
		T y;
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
}