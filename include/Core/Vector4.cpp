#include <Core/Vector4.h>
#include <string>

namespace vrv
{
   template<typename T>
   Vector4<T>::Vector4<T>()
   {
      memset(data, 0, sizeof(data));
   }

   template<typename T>
	Vector4f::Vector4f(float x, float y, float z, float w)
   {
      data[0] = x;
      data[1] = y;
      data[2] = y;
      data[3] = z;
	}

   template<typename T>
	Vector4f::Vector4f(Vector3f vec3, float w)
	{
      data[0] = vec3.x();
      data[1] = vec3.y();
      data[2] = vec3.z();
      data[3] = w;
   }

   template<typename T>
	Vector4f::Vector4f(Vector3f vec3)
   {
      data[0] = vec3.x();
      data[1] = vec3.y();
      data[2] = vec3.z();
      data[3] = 0;
   }

   template<typename T>
   Vector4f& Vector4f::operator =(const Vector4f& right)
	{
      data[0] = right.x();
      data[1] = right.y();
      data[2] = right.z();
      data[3] = right.w();

      return *this;
	}

   template<typename T>
	bool Vector4f::operator ==(const Vector4f& right)
	{
		if (x() == right.x() && y() == right.y() && z() == right.z() && w() == right.w())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

   template<typename T>
	bool Vector4f::operator !=(const Vector4f& right)
	{
		return !((*this) == right);
	}

   template<typename T>
	Vector4f Vector4f::operator +(const Vector4f& right)
	{
		data[0] += right.x();
      data[1] += right.y();
      data[2] += right.z();
      data[3] += right.w();
		return *this;
	}

   template<typename T>
	Vector4f Vector4f::operator -(const Vector4f& right)
	{
      data[0] -= right.x();
      data[1] -= right.y();
      data[2] -= right.z();
      data[3] -= right.w();
		return *this;
	}

   template<typename T>
	Vector4f Vector4f::operator -() const
	{
      return Vector4f(-data[0], -data[1], -data[2], -data[3]);
	}

   template<typename T>
	Vector4f Vector4f::operator / (float d)
	{
		return Vector4f(x() / d, y() / d, z() / d, w() / d);
	}

   template<typename T>
   float Vector4f::operator[](unsigned int index) const
   {
      return data[index];
   }

   template<typename T>
   float Vector4f::x() const
   {
      return data[0];
   }

   template<typename T>
   float Vector4f::y() const
   {
      return data[1];
   }

   template<typename T>
   float Vector4f::z() const
   {
      return data[2];
   }

   template<typename T>
   float Vector4f::w() const
   {
      return data[3];
   }

   template<typename T>
   float Vector4f::x()
   {
      return data[0];
   }

   template<typename T>
   float Vector4f::y()
   {
      return data[1];
   }

   template<typename T>
   float Vector4f::z()
   {
      return data[2];
   }

   template<typename T>
   float Vector4f::w()
   {
      return data[3];
   }

}