#pragma once
#include <Core/Vector2.h>
namespace vrv
{
   template<typename T>
	class Vector3
	{
	public:
      Vector3();

      Vector3(T);

      Vector3(Vector2<T>);

      Vector3(T x, T y, T z);

      Vector3<T>& operator =(const Vector3<T>& right);

      bool operator ==(const Vector3<T>& right);

      bool operator !=(const Vector3<T>& right);

      Vector3<T> operator +=(const Vector3<T>& right);

      Vector3<T> operator -=(const Vector3<T>& right);

      Vector3<T> operator +(const Vector3<T>& right);

      Vector3<T> operator -(const Vector3<T>& right);

      Vector3<T> operator *(const Vector3<T>& right);

      Vector3<T> operator /(T mag) const;

      Vector3<T> operator -() const;

      Vector3<T> operator *(T);

      T x() const;

      T y() const;

      T z() const;

      T& x();

      T& y();

      T& z();

      T operator[] (unsigned int) const;

		void normalize();

      Vector3<T> normalizedVector() const;

      T dotProduct(const Vector3<T>& right);

      Vector3<T> crossProduct(const Vector3<T>& right);

      T distanceSquare(const Vector3<T>& right);

      T length();

      T angelBetween(const Vector3<T>& right);

      Vector3<T> rotateAroundAxis(Vector3<T> axis, float degree);

   private:
      T data[3];

	};


   typedef Vector3<float> Vector3f;
   typedef Vector3<int> Vector3i;
   typedef Vector3<double> Vector3d;
}

#include <Core/Vector3.cpp>