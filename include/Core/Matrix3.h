#pragma once

namespace vrv
{
	class Matrix3f
	{
		typedef float value_type;
	public:
		Matrix3f();
		Matrix3f(value_type a00, value_type a01, value_type a02,
			     value_type a10, value_type a11, value_type a12,
			     value_type a20, value_type a21, value_type a22);
		bool operator != (const Matrix3f& r);
		bool operator == (const Matrix3f& r);
	public:
		value_type* m;
	};
}