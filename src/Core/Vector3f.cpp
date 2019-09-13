#include <Core/Vector3f.h>
#include <Core/Vector4f.h>

namespace vrv
{
   Vector3f::Vector3f()
   {
      memset(data, 0, sizeof(data));
   }

   Vector3f::Vector3f(float scalar)
   {
      data[0] = scalar;
      data[1] = scalar;
      data[2] = scalar;
   }

   Vector3f::Vector3f(Vector2f vec)
   {
      data[0] = vec[0];
      data[1] = vec[1];
      data[2] = 0;
   }

   Vector3f::Vector3f(float x, float y, float z)
   {
      data[0] = x;
      data[1] = y;
      data[2] = z;
   }

   Vector3f& Vector3f::operator =(const Vector3f& right)
   {
      data[0] = right[0];
      data[1] = right[1];
      data[2] = right[2];

      return *this;
   }

   Vector3f& Vector3f::operator = (const Vector4f& vec4)
   {
      data[0] = vec4.x();
      data[1] = vec4.y();
      data[2] = vec4.z();
      return *this;
   }

   bool Vector3f::operator ==(const Vector3f& right)
   {
      if (data[0] == right[0] && data[1] == right[1] && data[2] == right[2])
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   bool Vector3f::operator !=(const Vector3f& right)
   {
      return !((*this) == right);
   }

   Vector3f Vector3f::operator +=(const Vector3f& right)
   {
      data[0] += right[0];
      data[1] += right[1];
      data[2] += right[2];
      return *this;
   }

   Vector3f Vector3f::operator -=(const Vector3f& right)
   {
      data[0] -= right[0];
      data[1] -= right[1];
      data[2] -= right[2];
      return *this;
   }

   Vector3f Vector3f::operator +(const Vector3f& right)
   {
      return Vector3f(data[0] + right[0], data[1] + right[1], data[2] + right[2]);
   }

   Vector3f Vector3f::operator -(const Vector3f& right)
   {
      return Vector3f(data[0] - right[0], data[1] - right[1], data[2] - right[2]);
   }

   Vector3f Vector3f::operator *(const Vector3f& right)
   {
      return Vector3f(data[0] * right[0], data[1] * right[1], data[2] * right[2]);
   }

   Vector3f Vector3f::operator /(float mag) const
   {
      return Vector3f(data[0] / mag, data[1] / mag, data[2] / mag);
   }

   Vector3f Vector3f::operator -() const
   {
      return Vector3f(-data[0], -data[1], -data[2]);
   }

   Vector3f Vector3f::operator *(float mag)
   {
      return Vector3f(data[0] * mag, data[1] * mag, data[2] * mag);
   }

   float Vector3f::operator[] (unsigned int index) const
   {
      return data[index];
   }

   float Vector3f::x() const
   {
      return data[0];
   }

   float Vector3f::y() const
   {
      return data[1];
   }

   float Vector3f::z() const
   {
      return data[2];
   }

   float& Vector3f::x()
   {
      return data[0];
   }

   float& Vector3f::y()
   {
      return data[1];
   }

   float& Vector3f::z()
   {
      return data[2];
   }

   void Vector3f::normalize()
   {
      float mag = Utility::sqrt(x()*x() + y()*y() + z()*z());
      if (mag == 0)
      {
         VRV_ERROR("DIVIDE by 0")
      }
      (*this) = (*this) / mag;
   }

   Vector3f Vector3f::normalizedVector() const
   {
      float mag = Utility::sqrt(x()*x() + y() * y() + z() * z());
      if (mag == 0)
      {
         VRV_ERROR("DIVIDE by 0")
      }
      Vector3f ret = (*this) / mag;

      return ret;
   }

   float Vector3f::dotProduct(const Vector3f& right)
   {
      return data[0] * right.x() + data[1] * right.y() + data[2] * right.z();
   }

   Vector3f Vector3f::crossProduct(const Vector3f& right)
   {
      return Vector3f(data[1] * right.z() - data[2] * right.y(),
         data[2] * right.x() - data[0] * right.z(), data[0] * right.y() - data[1] * right.x());
   }

   float Vector3f::distanceSquare(const Vector3f& right)
   {
      return (data[0] - right.x())*(data[0] - right.x())
         + (data[1] - right.y())*(data[1] - right.y()) + (data[2] - right.z())* (data[2] - right.z());
   }

   float Vector3f::length()
   {
      return Utility::sqrt(x()*x() + y()*y() + z()*z());
   }

   float Vector3f::angelBetween(const Vector3f& right)
   {
      return Utility::acos(normalizedVector().dotProduct(right.normalizedVector()));
   }

   Vector3f Vector3f::rotateAroundAxis(Vector3f axis, float degree)
   {
      float u = axis.x();
      float v = axis.y();
      float w = axis.z();

      float cosTheta = Utility::cos(degree);
      float sinTheta = Utility::sin(degree);

      float ms = axis.length()*axis.length();
      float m = Utility::sqrt(ms);

      float x = data[0];
      float y = data[1];
      float z = data[2];

      return Vector3f(
         ((u * (u * x + v * y + w * z)) +
         (((x * (v * v + w * w)) - (u * (v * y + w * z))) * cosTheta) +
            (m * ((-w * y) + (v * z)) * sinTheta)) / ms,

            ((v * (u * x + v * y + w * z)) +
         (((y * (u * u + w * w)) - (v * (u * x + w * z))) * cosTheta) +
               (m * ((w * x) - (u * z)) * sinTheta)) / ms,

               ((w * (u * x + v * y + w * z)) +
         (((z * (u * u + v * v)) - (w * (u * x + v * y))) * cosTheta) +
                  (m * (-(v * x) + (u * y)) * sinTheta)) / ms);
   }
}