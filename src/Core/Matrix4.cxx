#include <Core/Matrix4.h>
#include <cstring>
namespace vrv
{
	Matrix4f::Matrix4f()
	{
		m = std::vector<value_type>(16, 0);
		m[0] = 1; m[1] = 0; m[2] = 0; m[3] = 0;
		m[4] = 0; m[5] = 1; m[6] = 0; m[7] = 0;
		m[8] = 0; m[9] = 0; m[10] = 1; m[11] = 0;
		m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
	}

	Matrix4f::Matrix4f(value_type a00, value_type a01, value_type a02, value_type a03,
		value_type a10, value_type a11, value_type a12, value_type a13,
		value_type a20, value_type a21, value_type a22, value_type a23,
		value_type a30, value_type a31, value_type a32, value_type a33)
	{
		m = std::vector<value_type>(16, 0);
		m[0] = a00; m[1] = a01; m[2] = a02; m[3] = a03;
		m[4] = a01; m[5] = a11; m[6] = a12; m[7] = a13;
		m[8] = a20; m[9] = a21; m[10] = a22; m[11] = a23;
		m[12] = a30; m[13] = a31; m[14] = a32; m[15] = a33;
	}

	bool Matrix4f::operator != (const Matrix4f& r)
	{
		return !(*this == r);
	}

	bool Matrix4f::operator == (const Matrix4f& r)
	{
		return m[0]  == r.m[0]  && m[1]  == r.m[1]  && m[2]  == r.m[2]  && m[3]  == r.m[3]  &&
			   m[4]  == r.m[4]  && m[5]  == r.m[5]  && m[6]  == r.m[6]  && m[7]  == r.m[7]  &&
			   m[8]  == r.m[8]  && m[9]  == r.m[9]  && m[10] == r.m[10] && m[11] == r.m[11] &&
		       m[12] == r.m[12] && m[13] == r.m[13] && m[14] == r.m[14] && m[15] == r.m[15];
	}

	Matrix4f Matrix4f::makeTranslate(value_type x, value_type y, value_type z)
	{
		return Matrix4f(1, 0, 0, x,
						0, 1, 0, y,
						0, 0, 1, z,
						0, 0, 0, 1);
	}

	Matrix4f Matrix4f::makeScale(value_type x, value_type y, value_type z)
	{
		return Matrix4f(x, 0, 0, 0,
						0, y, 0, 0,
						0, 0, z, 0,
						0, 0, 0, 1);
	}

	Vector3f Matrix4f::operator*(const Vector3f& vec)
	{
		Vector4f vec4 = (*this)*Vector4f(vec,1);
		return vec4;
	}

	Vector4f Matrix4f::operator*(const Vector4f& vec)
	{
		float x = vec.x;
		float y = vec.y;
		float z = vec.z;
		float w = vec.w;
		return Vector4f(m[0] * x + m[1] * y + m[2] * z + m[3]*w, m[4] * x + m[5] * y + m[6] * z + m[7]*w,
			m[8] * x + m[9] * y + m[10] * z + m[11]*w, m[12] * x + m[13] * y + m[14] * z + m[15]*w);
	}
}