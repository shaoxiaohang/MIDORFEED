#pragma once
#include <Core/Vector2i.h>
#include <Core/Utility.h>
namespace vrv
{
	class Vector3i
	{
	public:
      Vector3i()
      {
         memset(data, 0, sizeof(data));
      }

      Vector3i(int scalar)
      {
         data[0] = scalar;
         data[1] = scalar;
         data[2] = scalar;
      }

      Vector3i(Vector2i vec)
      {
         data[0] = vec[0];
         data[1] = vec[1];
         data[2] = 0;
      }

      Vector3i(int x, int y, int z)
      {
         data[0] = x;
         data[1] = y;
         data[2] = z;
      }

      Vector3i& operator =(const Vector3i& right)
      {
         data[0] = right[0];
         data[1] = right[1];
         data[2] = right[2];

         return *this;
      }

      bool operator ==(const Vector3i& right)
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

      bool operator !=(const Vector3i& right)
      {
         return !((*this) == right);
      }

      Vector3i operator +=(const Vector3i& right)
      {
         data[0] += right[0];
         data[1] += right[1];
         data[2] += right[2];
         return *this;
      }

      Vector3i operator -=(const Vector3i& right)
      {
         data[0] -= right[0];
         data[1] -= right[1];
         data[2] -= right[2];
         return *this;
      }

      Vector3i operator +(const Vector3i& right)
      {
         return Vector3i(data[0] + right[0], data[1] + right[1], data[2] + right[2]);
      }

      Vector3i operator -(const Vector3i& right)
      {
         return Vector3i(data[0] - right[0], data[1] - right[1], data[2] - right[2]);
      }

      Vector3i operator *(const Vector3i& right)
      {
         return Vector3i(data[0] * right[0], data[1] * right[1], data[2] * right[2]);
      }

      Vector3i operator /(int mag) const
      {
         return Vector3i(data[0] / mag, data[1] / mag, data[2] / mag);
      }

      Vector3i operator -() const
      {
         return Vector3i(-data[0], -data[1], -data[2]);
      }

      Vector3i operator *(int mag)
      {
         return Vector3i(data[0] * mag, data[1] * mag, data[2] * mag);
      }

      int Vector3i::operator[] (unsigned int index) const
      {
         return data[index];
      }

      int Vector3i::x() const
      {
         return data[0];
      }

      int Vector3i::y() const
      {
         return data[1];
      }

      int Vector3i::z() const
      {
         return data[2];
      }

      int& Vector3i::x()
      {
         return data[0];
      }

      int& Vector3i::y()
      {
         return data[1];
      }

      int& Vector3i::z()
      {
         return data[2];
      }

      void Vector3i::normalize()
      {
         int mag = Utility::sqrt(x()*x() + y()*y() + z()*z());
         if (mag == 0)
         {
            VRV_ERROR("DIVIDE by 0")
         }
         (*this) = (*this) / mag;
      }

      Vector3i Vector3i::normalizedVector() const
      {
         int mag = Utility::sqrt(x()*x() + y() * y() + z() * z());
         if (mag == 0)
         {
            VRV_ERROR("DIVIDE by 0")
         }
         Vector3i ret = (*this) / mag;

         return ret;
      }

      int Vector3i::dotProduct(const Vector3i& right)
      {
         return data[0] * right.x() + data[1] * right.y() + data[2] * right.z();
      }

      Vector3i Vector3i::crossProduct(const Vector3i& right)
      {
         return Vector3i(data[1] * right.z() - data[2] * right.y(),
            data[2] * right.x() - data[0] * right.z(), data[0] * right.y() - data[1] * right.x());
      }

      int Vector3i::distanceSquare(const Vector3i& right)
      {
         return (data[0] - right.x())*(data[0] - right.x())
            + (data[1] - right.y())*(data[1] - right.y()) + (data[2] - right.z())* (data[2] - right.z());
      }

      int Vector3i::length()
      {
         return Utility::sqrt(x()*x() + y()*y() + z()*z());
      }

      int Vector3i::angelBetween(const Vector3i& right)
      {
         return Utility::acos(normalizedVector().dotProduct(right.normalizedVector()));
      }

      Vector3i Vector3i::rotateAroundAxis(Vector3i axis, float degree)
      {
         int u = axis.x();
         int v = axis.y();
         int w = axis.z();

         float cosTheta = Utility::cos(degree);
         float sinTheta = Utility::sin(degree);

         int ms = axis.length()*axis.length();
         float m = Utility::sqrt(ms);

         int x = data[0];
         int y = data[1];
         int z = data[2];

         return Vector3i(
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

   private:
      int data[3];

	};

}
