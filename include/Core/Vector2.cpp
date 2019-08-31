#include <Core/Vector2.h>
#include <memory>

namespace vrv
{
   template <typename T>
   Vector2<T>::Vector2<T>()
   {
      memset(data, 0, sizeof(data));
   }

   template <typename T>
   Vector2<T>::Vector2<T>(T x, T y)
   {
      data[0] = x;
      data[1] = y;
   }

   template <typename T>
   Vector2<T>& Vector2<T>::operator= (const Vector2<T>& right)
   {
      data[0] = right[0];
      data[1] = right[1];
      return *this;
   }

   template <typename T>
   bool Vector2<T>::operator== (const Vector2<T>& right)
   {
      return data[0] == right[0] && data[1] == right[1];
   }

   template <typename T>
   bool Vector2<T>::operator!= (const Vector2<T>& right)
   {
      return data[0] != right[0] || data[1] != right[1];
   }

   template <typename T>
   Vector2<T> Vector2<T>::operator +(const Vector2& right)
   {
      return Vector2<T>(data[0] + right[0], data[1] + right[1]);
   }

   template <typename T>
   Vector2<T> Vector2<T>::operator -(const Vector2<T>& right)
   {
      return Vector2<T>(data[0] - right[0], data[1] - right[1]);
   }

   template <typename T>
   T Vector2<T>::operator[] (unsigned index) const
   {
      return data[index];
   }

   template <typename T>
   T Vector2<T>::x() const
   {
      return data[0];
   }

   template <typename T>
   T Vector2<T>::y() const
   {
      return data[1];
   }

   template <typename T>
   T& Vector2<T>::x()
   {
      return data[0];
   }

   template <typename T>
   T& Vector2<T>::y()
   {
      return data[1];
   }
}