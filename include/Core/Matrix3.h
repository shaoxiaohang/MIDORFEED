#pragma once

#include<vector>
#include<Core/Vector3.h>
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
		Matrix3f operator*(const Matrix3f& r);
		Vector3f operator*(const Vector3f& r);
		static Matrix3f makeTranslate(value_type x, value_type y);
		static Matrix3f makeScale(value_type x, value_type y);
		static Matrix3f makeWindowingTransformation(value_type l1, value_type b1, value_type r1, value_type t1,
													value_type l2, value_type b2, value_type r2,value_type t2);
	public:
		std::vector<value_type> m;
	};
}