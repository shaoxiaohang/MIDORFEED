#pragma once
#include <Core/Vector3i.h>
namespace vrv
{
	class Vector4i
	{
   public:
      Vector4i::Vector4i()
      {
         memset(data, 0, sizeof(data));
      }

      Vector4i::Vector4i(int x, int y, int z, int w)
      {
         data[0] = x;
         data[1] = y;
         data[2] = y;
         data[3] = z;
      }

      Vector4i::Vector4i(Vector3i vec3, int w)
      {
         data[0] = vec3.x();
         data[1] = vec3.y();
         data[2] = vec3.z();
         data[3] = w;
      }

      Vector4i::Vector4i(Vector3i vec3)
      {
         data[0] = vec3.x();
         data[1] = vec3.y();
         data[2] = vec3.z();
         data[3] = 0;
      }

      Vector4i& Vector4i::operator =(const Vector4i& right)
      {
         data[0] = right.x();
         data[1] = right.y();
         data[2] = right.z();
         data[3] = right.w();

         return *this;
      }

      bool Vector4i::operator ==(const Vector4i& right)
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

      bool Vector4i::operator !=(const Vector4i& right)
      {
         return !((*this) == right);
      }

      Vector4i Vector4i::operator +(const Vector4i& right)
      {
         data[0] += right.x();
         data[1] += right.y();
         data[2] += right.z();
         data[3] += right.w();
         return *this;
      }

      Vector4i Vector4i::operator -(const Vector4i& right)
      {
         data[0] -= right.x();
         data[1] -= right.y();
         data[2] -= right.z();
         data[3] -= right.w();
         return *this;
      }

      Vector4i Vector4i::operator -() const
      {
         return Vector4i(-data[0], -data[1], -data[2], -data[3]);
      }

      Vector4i Vector4i::operator / (float d)
      {
         return Vector4i(x() / d, y() / d, z() / d, w() / d);
      }

      int Vector4i::operator[](unsigned int index) const
      {
         return data[index];
      }

      int Vector4i::x() const
      {
         return data[0];
      }

      int Vector4i::y() const
      {
         return data[1];
      }

      int Vector4i::z() const
      {
         return data[2];
      }

      int Vector4i::w() const
      {
         return data[3];
      }

      int& Vector4i::x()
      {
         return data[0];
      }

      int& Vector4i::y()
      {
         return data[1];
      }

      int& Vector4i::z()
      {
         return data[2];
      }

      int& Vector4i::w()
      {
         return data[3];
      }

   protected:

      int data[4];

	};

}