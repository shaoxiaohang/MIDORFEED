#pragma once

namespace vrv
{
   template<typename T>
	class Vector2
	{
	public:
      Vector2()
      {
         memset(data, 0, sizeof(data));
      }

      Vector2(T x, T y)
      {
         data[0] = x;
         data[1] = y;
      }


      Vector2<T>& operator =(const Vector2<T>& right)
      {
         data[0] = right[0];
         data[1] = right[1];
         return *this;
      }

      bool operator ==(const Vector2<T>& right)
      {
         return data[0] == right[0] && data[1] == right[1];
      }

      bool operator !=(const Vector2<T>& right)
      {
         return data[0] != right[0] || data[1] != right[1];
      }

      Vector2<T> operator +(const Vector2<T>& right)
      {
         return Vector2<T>(data[0] + right[0], data[1] + right[1]);
      }

      Vector2<T> operator -(const Vector2<T>& right)
      {
         return Vector2<T>(data[0] - right[0], data[1] - right[1]);
      }

      T operator[] (unsigned index) const
      {
         return data[index];
      }

      T x() const
      {
         return data[0];
      }

      T y() const
      {
         return data[1];
      }

      T& x()
      {
         return data[0];
      }

      T& y()
      {
         return data[1];
      }
 
   private:
      T data[2];
	};

   typedef Vector2<float> Vector2f;
   typedef Vector2<double> Vector2d;
   typedef Vector2<int> Vector2i;
}
