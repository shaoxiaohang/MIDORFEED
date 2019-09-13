#include <Core/Vector4f.h>

namespace vrv
{
   Vector4f::Vector4f()
   {
      memset(data, 0, sizeof(data));
   }

   Vector4f::Vector4f(float x, float y, float z, float w)
   {
      data[0] = x;
      data[1] = y;
      data[2] = y;
      data[3] = z;
   }

   Vector4f::Vector4f(const Vector3f& vec3)
   {
      data[0] = vec3.x();
      data[1] = vec3.y();
      data[2] = vec3.z();
      data[3] = 1.0f;
   }

   Vector4f& Vector4f::operator = (const Vector3f& vec3)
   {
      data[0] = vec3.x();
      data[1] = vec3.y();
      data[2] = vec3.z();
      data[3] = 1.0f;
      return *this;
   }

   Vector4f::Vector4f(Vector3f vec3, float w)
   {
      data[0] = vec3.x();
      data[1] = vec3.y();
      data[2] = vec3.z();
      data[3] = w;
   }

   Vector4f::Vector4f(Vector3f vec3)
   {
      data[0] = vec3.x();
      data[1] = vec3.y();
      data[2] = vec3.z();
      data[3] = 0;
   }

   Vector4f& Vector4f::operator =(const Vector4f& right)
   {
      data[0] = right.x();
      data[1] = right.y();
      data[2] = right.z();
      data[3] = right.w();

      return *this;
   }

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

   bool Vector4f::operator !=(const Vector4f& right)
   {
      return !((*this) == right);
   }

   Vector4f Vector4f::operator +(const Vector4f& right)
   {
      data[0] += right.x();
      data[1] += right.y();
      data[2] += right.z();
      data[3] += right.w();
      return *this;
   }

   Vector4f Vector4f::operator -(const Vector4f& right)
   {
      data[0] -= right.x();
      data[1] -= right.y();
      data[2] -= right.z();
      data[3] -= right.w();
      return *this;
   }

   Vector4f Vector4f::operator -() const
   {
      return Vector4f(-data[0], -data[1], -data[2], -data[3]);
   }

   Vector4f Vector4f::operator / (float d)
   {
      return Vector4f(x() / d, y() / d, z() / d, w() / d);
   }

   float Vector4f::operator[](unsigned int index) const
   {
      return data[index];
   }

   float Vector4f::x() const
   {
      return data[0];
   }

   float Vector4f::y() const
   {
      return data[1];
   }

   float Vector4f::z() const
   {
      return data[2];
   }

   float Vector4f::w() const
   {
      return data[3];
   }

   float& Vector4f::x()
   {
      return data[0];
   }

   float& Vector4f::y()
   {
      return data[1];
   }

   float& Vector4f::z()
   {
      return data[2];
   }

   float& Vector4f::w()
   {
      return data[3];
   }

   Vector3f Vector4f::xyz()
   {
      return Vector3f(data[0], data[1], data[2]);
   }
}