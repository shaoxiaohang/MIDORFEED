#pragma once
#include <vector>
#include <Core/Vector3.h>
#include <Core/Vector4.h>
namespace vrv
{
	class Matrix4f
	{
		typedef float value_type;
	public:
		Matrix4f();
		Matrix4f(value_type a00, value_type a01, value_type a02, value_type a03,
				 value_type a10, value_type a11, value_type a12, value_type a13,
				 value_type a20, value_type a21, value_type a22, value_type a23,
				 value_type a30, value_type a31, value_type a32, value_type a33);
		bool operator != (const Matrix4f& r);
		bool operator == (const Matrix4f& r);
		static Matrix4f makeTranslate(value_type x, value_type y, value_type z);
		static Matrix4f makeScale(value_type x, value_type y, value_type z);
		Vector3f operator*(const Vector3f& vec);
		Vector4f operator*(const Vector4f& vec);
	public:
		std::vector<float> m;
	};

}