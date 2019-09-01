#pragma once
#include <Core/Vector3.h>
namespace vrv
{
   template<typename T>
	class Vector4
	{
   public:

      template<typename T>
      Vector4<T>::Vector4()
      {
         memset(data, 0, sizeof(data));
      }

      template<typename T>
      Vector4<T>::Vector4(T x, T y, T z, T w)
      {
         data[0] = x;
         data[1] = y;
         data[2] = y;
         data[3] = z;
      }

      template<typename T>
      Vector4<T>::Vector4(Vector3<T> vec3, T w)
      {
         data[0] = vec3.x();
         data[1] = vec3.y();
         data[2] = vec3.z();
         data[3] = w;
      }

      template<typename T>
      Vector4<T>::Vector4(Vector3<T> vec3)
      {
         data[0] = vec3.x();
         data[1] = vec3.y();
         data[2] = vec3.z();
         data[3] = 0;
      }

      template<typename T>
      Vector4<T>& Vector4<T>::operator =(const Vector4<T>& right)
      {
         data[0] = right.x();
         data[1] = right.y();
         data[2] = right.z();
         data[3] = right.w();

         return *this;
      }

      template<typename T>
      bool Vector4<T>::operator ==(const Vector4<T>& right)
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
      bool Vector4<T>::operator !=(const Vector4<T>& right)
      {
         return !((*this) == right);
      }

      template<typename T>
      Vector4<T> Vector4<T>::operator +(const Vector4<T>& right)
      {
         data[0] += right.x();
         data[1] += right.y();
         data[2] += right.z();
         data[3] += right.w();
         return *this;
      }

      template<typename T>
      Vector4<T> Vector4<T>::operator -(const Vector4<T>& right)
      {
         data[0] -= right.x();
         data[1] -= right.y();
         data[2] -= right.z();
         data[3] -= right.w();
         return *this;
      }

      template<typename T>
      Vector4<T> Vector4<T>::operator -() const
      {
         return Vector4<T>(-data[0], -data[1], -data[2], -data[3]);
      }

      template<typename T>
      Vector4<T> Vector4<T>::operator / (float d)
      {
         return Vector4<T>(x() / d, y() / d, z() / d, w() / d);
      }

      template<typename T>
      T Vector4<T>::operator[](unsigned int index) const
      {
         return data[index];
      }

      template<typename T>
      T Vector4<T>::x() const
      {
         return data[0];
      }

      template<typename T>
      T Vector4<T>::y() const
      {
         return data[1];
      }

      template<typename T>
      T Vector4<T>::z() const
      {
         return data[2];
      }

      template<typename T>
      T Vector4<T>::w() const
      {
         return data[3];
      }

      template<typename T>
      T& Vector4<T>::x()
      {
         return data[0];
      }

      template<typename T>
      T& Vector4<T>::y()
      {
         return data[1];
      }

      template<typename T>
      T& Vector4<T>::z()
      {
         return data[2];
      }

      template<typename T>
      T& Vector4<T>::w()
      {
         return data[3];
      }

   protected:

      T data[4];

	};

   typedef Vector4<float> Vector4f;
   typedef Vector4<int> Vector4i;
   typedef Vector4<double> Vector4d;

}