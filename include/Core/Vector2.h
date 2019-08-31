#pragma once

namespace vrv
{
   template<typename T>
	class Vector2
	{
	public:
      Vector2();

      Vector2(T x, T y);

      Vector2<T>& operator =(const Vector2<T>& right);

      bool operator ==(const Vector2<T>& right);

      bool operator !=(const Vector2<T>& right);

      Vector2<T> operator +(const Vector2<T>& right);

      Vector2<T> operator -(const Vector2<T>& right);

      T operator[] (unsigned index) const;

      T x() const;

      T y() const;

      T& x();

      T& y();
 
   private:
      T data[2];
	};

   typedef Vector2<float> Vector2f;
   typedef Vector2<double> Vector2d;
   typedef Vector2<int> Vector2i;
}

#include <Core/Vector2.cpp>