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
		}
		Matrix3(T a00, T a01, T a02,
				T a10, T a11, T a12,
				T a20, T a21, T a22)
		{
			m = new T[9];
			m[0][0] = a00; m[0][1] = a10; m[0][2] = a20;
			m[1][0] = a01; m[1][1] = a11; m[1][2] = a21;
			m[2][0] = a02; m[2][1] = a12; m[2][2] = a22;
		}
	T* m;
	};
	
	typedef Matrix3<int> Matrix3i;
	typedef Matrix3<float> Matrix3f;
	typedef Matrix3<float> Matrix3d;
}