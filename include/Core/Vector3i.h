#pragma once
#include <Core/Vector2.h>
namespace vrv
{
   template<typename T>
	class Vector3
	{
	public:
      Vector3()
      {
         memset(data, 0, sizeof(data));
      }

      Vector3(T)
      {
         data[0] = scalar;
         data[1] = scalar;
         data[2] = scalar;
      }

      Vector3(Vector2<T> vec)
      {
         data[0] = vec[0];
         data[1] = vec[1];
         data[2] = 0;
      }

      Vector3(T x, T y, T z)
      {
         data[0] = x;
         data[1] = y;
         data[2] = z;
      }

      Vector3<T>& operator =(const Vector3<T>& right)
      {
         data[0] = right[0];
         data[1] = right[1];
         data[2] = right[2];

         return *this;
      }

      bool operator ==(const Vector3<T>& right)
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

      bool operator !=(const Vector3<T>& right)
      {
         return !((*this) == right);
      }

      Vector3<T> operator +=(const Vector3<T>& right)
      {
         data[0] += right[0];
         data[1] += right[1];
         data[2] += right[2];
         return *this;
      }

      Vector3<T> operator -=(const Vector3<T>& right)
      {
         data[0] -= right[0];
         data[1] -= right[1];
         data[2] -= right[2];
         return *this;
      }

      Vector3<T> operator +(const Vector3<T>& right)
      {
         return Vector3(data[0] + right[0], data[1] + right[1], data[2] + right[2]);
      }

      Vector3<T> operator -(const Vector3<T>& right)
      {
         return Vector3<T>(data[0] - right[0], data[1] - right[1], data[2] - right[2]);
      }

      Vector3<T> operator *(const Vector3<T>& right)
      {
         return Vector3<T>(data[0] * right[0], data[1] * right[1], data[2] * right[2]);
      }

      Vector3<T> operator /(T mag) const
      {
         return Vector3<T>(data[0] / mag, data[1] / mag, data[2] / mag);
      }

      Vector3<T> operator -() const
      {
         return Vector3<T>(-data[0], -data[1], -data[2]);
      }

      Vector3<T> operator *(T)
      {
         return Vector3<T>(data[0] * mag, data[1] * mag, data[2] * mag);
      }

      template<typename T>
      T Vector3<T>::operator[] (unsigned int index) const
      {
         return data[index];
      }


      template<typename T>
      T Vector3<T>::x() const
      {
         return data[0];
      }

      template<typename T>
      T Vector3<T>::y() const
      {
         return data[1];
      }

      template<typename T>
      T Vector3<T>::z() const
      {
         return data[2];
      }

      template<typename T>
      T& Vector3<T>::x()
      {
         return data[0];
      }

      template<typename T>
      T& Vector3<T>::y()
      {
         return data[1];
      }

      template<typename T>
      T& Vector3<T>::z()
      {
         return data[2];
      }

      template<typename T>
      void Vector3<T>::normalize()
      {
         T mag = Utility::sqrt(x()*x() + y()*y() + z()*z());
         if (mag == 0)
         {
            VRV_ERROR("DIVIDE by 0")
         }
         (*this) = (*this) / mag;
      }

      template<typename T>
      Vector3<T> Vector3<T>::normalizedVector() const
      {
         T mag = Utility::sqrt(x()*x() + y() * y() + z() * z());
         if (mag == 0)
         {
            VRV_ERROR("DIVIDE by 0")
         }
         Vector3<T> ret = (*this) / mag;

         return ret;
      }

      template<typename T>
      T Vector3<T>::dotProduct(const Vector3& right)
      {
         return data[0] * right.x() + data[1] * right.y() + data[2] * right.z();
      }

      template<typename T>
      Vector3<T> Vector3<T>::crossProduct(const Vector3& right)
      {
         return Vector3<T>(data[1] * right.z() - data[2] * right.y(),
            data[2] * right.x() - data[0] * right.z(), data[0] * right.y() - data[1] * right.x());
      }

      template<typename T>
      T Vector3<T>::distanceSquare(const Vector3& right)
      {
         return (data[0] - right.x())*(data[0] - right.x())
            + (data[1] - right.y())*(data[1] - right.y()) + (data[2] - right.z())* (data[2] - right.z());
      }

      template<typename T>
      T Vector3<T>::length()
      {
         return Utility::sqrt(x()*x() + y()*y() + z()*z());
      }

      template<typename T>
      T Vector3<T>::angelBetween(const Vector3<T>& right)
      {
         return Utility::acos(normalizedVector().dotProduct(right.normalizedVector()));
      }

      template<typename T>
      Vector3<T> Vector3<T>::rotateAroundAxis(Vector3<T> axis, float degree)
      {
         T u = axis.x();
         T v = axis.y();
         T w = axis.z();

         float cosTheta = Utility::cos(degree);
         float sinTheta = Utility::sin(degree);

         T ms = axis.length()*axis.length();
         T m = Utility::sqrt(ms);

         T x = data[0];
         T y = data[1];
         T z = data[2];

         return Vector3<T>(
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
      T data[3];

	};


   typedef Vector3<float> Vector3f;
   typedef Vector3<int> Vector3i;
   typedef Vector3<double> Vector3d;
}
