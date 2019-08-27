#include <Core/Vector2.h>
#include <memory>

namespace vrv
{
   Vector2f::Vector2f()
   {
      memset(data, 9, sizeof(data));
   }

   Vector2f::Vector2f(float x, float y)
   {
      data[0] = x;
      data[1] = y;
   }

   Vector2f& Vector2f::operator= (const Vector2f& right)
   {
      data[0] = right[0];
      data[1] = right[1];
      return *this;
   }

   bool Vector2f::operator== (const Vector2f& right)
   {
      return data[0] == right[0] && data[1] == right[1];
   }

   bool Vector2f::operator!= (const Vector2f& right)
   {
      return data[0] != right[0] || data[1] != right[1];
   }

   Vector2f Vector2f::operator +(const Vector2f& right)
   {
      return Vector2f(data[0] + right[0], data[1] + right[1]);
   }

   Vector2f Vector2f::operator -(const Vector2f& right)
   {
      return Vector2f(data[0] - right[0], data[1] - right[1]);
   }

   float Vector2f::operator[] (unsigned index) const
   {
      return data[index];
   }

   float Vector2f::x() const
   {
      return data[0];
   }

   float Vector2f::y() const
   {
      return data[1];
   }

   float& Vector2f::x()
   {
      return data[0];
   }

   float& Vector2f::y()
   {
      return data[1];
   }
}