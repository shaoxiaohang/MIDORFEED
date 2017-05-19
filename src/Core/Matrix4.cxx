#include <Core/Matrix4.h>
#include <Core/Utility.h>
#include <cstring>
namespace vrv
{
	Matrix4f::Matrix4f()
	{
		m.resize(16);
		m[0]  = 1; m[1]  = 0;  m[2]  = 0; m[3]  = 0;
		m[4]  = 0; m[5]  = 1;  m[6]  = 0; m[7]  = 0;
		m[8]  = 0; m[9]  = 0;  m[10] = 1; m[11] = 0;
		m[12] = 0; m[13] = 0;  m[14] = 0; m[15] = 1;
	}

	Matrix4f::Matrix4f(value_type a00, value_type a01, value_type a02, value_type a03,
					   value_type a10, value_type a11, value_type a12, value_type a13,
					   value_type a20, value_type a21, value_type a22, value_type a23,
		               value_type a30, value_type a31, value_type a32, value_type a33)
	{
		m.resize(16);
		m[0]  = a00; m[1]  = a10; m[2]  = a20; m[3] = a30;
		m[4]  = a01; m[5]  = a11; m[6]  = a21; m[7] = a31;
		m[8]  = a02; m[9]  = a12; m[10] = a22; m[11] = a32;
		m[12] = a03; m[13] = a13; m[14] = a23; m[15] = a33;
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

	Vector4f Matrix4f::operator*(const Vector3f& vec)
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
		return Vector4f(m[0] * x + m[4] * y + m[8] * z + m[12]*w, m[1] * x + m[5] * y + m[9] * z + m[13]*w,
			m[2] * x + m[6] * y + m[10] * z + m[14]*w, m[3] * x + m[7] * y + m[11] * z + m[15]*w);
	}

	Matrix4f Matrix4f::operator*(const Matrix4f& r)
	{
		return Matrix4f
			(m[0] * r.m[0] + m[4] * r.m[1] + m[8]  * r.m[2] + m[12] * r.m[3], m[0] * r.m[4] + m[4] * r.m[5] + m[8]  * r.m[6] + m[12] * r.m[7], m[0] * r.m[8] + m[4] * r.m[9] + m[8]  * r.m[10] + m[12]  * r.m[11], m[0] * r.m[12] + m[4] * r.m[13] + m[8]  * r.m[14] + m[12] * r.m[15],
			 m[1] * r.m[0] + m[5] * r.m[1] + m[9]  * r.m[2] + m[13] * r.m[3], m[1] * r.m[4] + m[5] * r.m[5] + m[9]  * r.m[6] + m[13] * r.m[7], m[1] * r.m[8] + m[5] * r.m[9] + m[9]  * r.m[10] + m[13]  * r.m[11], m[1] * r.m[12] + m[5] * r.m[13] + m[9]  * r.m[14] + m[13] * r.m[15],
			 m[2] * r.m[0] + m[6] * r.m[1] + m[10] * r.m[2] + m[14] * r.m[3], m[2] * r.m[4] + m[6] * r.m[5] + m[10] * r.m[6] + m[14] * r.m[7], m[2] * r.m[8] + m[6] * r.m[9] + m[10] * r.m[10] + m[14]  * r.m[11], m[2] * r.m[12] + m[6] * r.m[13] + m[10] * r.m[14] + m[14] * r.m[15],
			 m[3] * r.m[0] + m[7] * r.m[1] + m[11] * r.m[2] + m[15] * r.m[3], m[3] * r.m[4] + m[7] * r.m[5] + m[11] * r.m[6] + m[15] * r.m[7], m[3] * r.m[8] + m[7] * r.m[9] + m[11] * r.m[10] + m[15]  * r.m[11], m[3] * r.m[12] + m[7] * r.m[13] + m[11] * r.m[14] + m[15] * r.m[15]);
	}

	Matrix4f Matrix4f::makeWindowingTransformation(value_type l1, value_type b1, value_type n1,
												   value_type r1, value_type t1, value_type f1,
							                       value_type l2, value_type b2, value_type n2,
		                                           value_type r2, value_type t2, value_type f2)
	{
		return makeTranslate(l2, b2, n2)*makeScale((r2-l2)/(r1-l1), (t2-b2)/(t1-b1),(f2-n2)/(f1-n1))*makeTranslate(-l1,-b1,-n1);
	}

	Matrix4f Matrix4f::makeProjection(value_type l, value_type r, value_type b, value_type t, value_type n, value_type f)
	{
		return Matrix4f(2.0f*n / (r - l), 0, (r + l) / (r - l), 0,
						0, 2.0f*n / (t - b), (t + b) / (t - b), 0,
						0, 0, (n + f) / (n - f), 2.0f*n*f / (n - f),
						0, 0, -1, 0);

	}

	Matrix4f Matrix4f::makeProjection(value_type verticalFieldOfView, value_type ratioWDivedeH, value_type n, value_type f)
	{
		float tanHalfTheta = Utility::tan(verticalFieldOfView / 2.0f);
		float t = tanHalfTheta*n;
		float b = -t;
		float r = ratioWDivedeH*t;
		float l = -r;
		return makeProjection(l, r, b, t, n, f);
	}

	Matrix4f Matrix4f::makeFrameToCanonical(Vector3f e, Vector3f u, Vector3f v, Vector3f w)
	{
		return Matrix4f(u.x, v.x, w.x, e.x,
						u.y, v.y, w.y, e.y,
						u.z, v.z, w.z, e.z,
						0, 0, 0, 1);
	}

	Matrix4f Matrix4f::makeCanonicalToFrame(Vector3f e, Vector3f u, Vector3f v, Vector3f w)
	{
		return Matrix4f(u.x, u.y, u.z, 0,
			v.x, v.y, v.z, 0,
			w.x, w.y, w.z, 0,
			0, 0, 0, 1) * makeTranslate(-e.x, -e.y, -e.z);
	}
}