#pragma once

namespace vrv
{
	class Vector2f
	{
	public:
		Vector2f()
			: x(0)
			, y(0)
		{}

		Vector2f(float _x, float _y)
			: x(_x)
			, y(_y)
		{}

		void operator =(const Vector2f& right)
		{
			x = right.x;
			y = right.y;
		}

		bool operator ==(const Vector2f& right)
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

		bool operator !=(const Vector2f& right)
		{
			return !((*this) == right);
		}

		Vector2f operator +(const Vector2f& right)
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		Vector2f operator -(const Vector2f& right)
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		float x;
		float y;
	};
}