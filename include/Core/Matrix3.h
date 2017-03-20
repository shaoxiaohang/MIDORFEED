#pragma once

namespace vrv
{
	template <typename T>
	class Matrix3
	{
	public:
		Matrix3()
		{
			m = new T[9];
			memset(m, 0, 9 * sizeof(T));
			m[0] = 1; m[1] = 0; m[2] = 0;
			m[3] = 0; m[4] = 1; m[5] = 0;
			m[6] = 0; m[7] = 0; m[8] = 1;
		}
		Matrix3(T a00, T a01, T a02,
				T a10, T a11, T a12,
				T a20, T a21, T a22)
		{
			m = new T[9];
			m[0] = a00; m[1] = a10; m[2] = a20;
			m[3] = a01; m[4] = a11; m[5] = a21;
			m[6] = a02; m[7] = a12; m[8] = a22;
		}
	T* m;
	};
	
	typedef Matrix3<int> Matrix3i;
	typedef Matrix3<float> Matrix3f;
	typedef Matrix3<float> Matrix3d;
}