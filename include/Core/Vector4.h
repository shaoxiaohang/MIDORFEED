#pragma once
#include <Core/Vector3.h>
namespace vrv
{
	class Vector4f
	{
	public:
		Vector4f();
		Vector4f(float _x, float _y, float _z, float _w);
		Vector4f(Vector3f vec3, float w);
		Vector4f(Vector3f vec3);
		operator Vector3f();
		void operator =(const Vector4f& right);
		bool operator ==(const Vector4f& right);
		bool operator !=(const Vector4f& right);
		Vector4f operator +(const Vector4f& right);
		Vector4f operator -(const Vector4f& right);
		Vector4f operator -();
		Vector4f operator / (float d);

		float x;
		float y;
		float z;
		float w;

	};

}