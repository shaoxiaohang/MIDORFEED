#pragma once

namespace vrv
{
	template <typename T>
	class Matrix4
	{
	public:
		Matrix4()
		{
			m = new T[16];
			memset(m, 0, 16 * sizeof(T));
			m[0]  = 1; m[1]  = 0; m[2]  = 0; m[3]  = 0;
			m[4]  = 0; m[5]  = 1; m[6]  = 0; m[7]  = 0;
			m[8]  = 0; m[9]  = 0; m[10] = 1; m[11] = 0;
			m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
		}
		Matrix4(T a00, T a01, T a02, T a03,
				T a10, T a11, T a12, T a13,
				T a20, T a21, T a22, T a23,
				T a30, T a31, T a32, T a33)
		{
			m = new T[16];
			m[0]  = a00; m[1]  = a10; m[2]  = a20; m[3]  = a30;
			m[4]  = a01; m[5]  = a11; m[6]  = a21; m[7]  = a31;
			m[8]  = a02; m[9]  = a12; m[10] = a22; m[11] = a32;
			m[12] = a03; m[13] = a13; m[14] = a23; m[15] = a33;
		}
		T* m;
	};

	typedef Matrix4<int> Matrix4i;
	typedef Matrix4<float> Matrix4f;
	typedef Matrix4<float> Matrix4d;
}