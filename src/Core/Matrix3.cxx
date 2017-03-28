#include <Core/Matrix3.h>
#include <cstring>
namespace vrv
{
	Matrix3f::Matrix3f()
	{
		m = new value_type[9];
		memset(m, 0, 9 * sizeof(value_type));
		m[0] = 1; m[1] = 0; m[2] = 0;
		m[3] = 0; m[4] = 1; m[5] = 0;
		m[6] = 0; m[7] = 0; m[8] = 1;
	}

	Matrix3f::Matrix3f(value_type a00, value_type a01, value_type a02,
					 value_type a10, value_type a11, value_type a12,
				     value_type a20, value_type a21, value_type a22)
	{
		m = new value_type[9];
		m[0] = a00; m[1] = a01; m[2] = a02;
		m[3] = a10; m[4] = a11; m[5] = a12;
		m[6] = a20; m[7] = a21; m[8] = a22;
	}

	bool Matrix3f::operator != (const Matrix3f& r)
	{
		return !(*this == r);
	}

	bool Matrix3f::operator == (const Matrix3f& r)
	{
		return m[0] == r.m[0] && m[1] == r.m[1] && m[2] == r.m[2] &&
			   m[3] == r.m[3] && m[4] == r.m[4] && m[5] == r.m[5] &&
			   m[6] == r.m[6] && m[7] == r.m[7] && m[8] == r.m[8];
	}
}