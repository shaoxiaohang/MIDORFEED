#pragma once
#include<memory>

namespace vrv
{
   class Vector2f
   {
   public:
      Vector2f()
      {
         memset(data, 0, sizeof(data));
      }

      Vector2f(float x, float y)
      {
         data[0] = x;
         data[1] = y;
      }


      Vector2f& operator =(const Vector2f& right)
      {
         data[0] = right[0];
         data[1] = right[1];
         return *this;
      }

      bool operator ==(const Vector2f& right)
      {
         return data[0] == right[0] && data[1] == right[1];
      }

      bool operator !=(const Vector2f& right)
      {
         return data[0] != right[0] || data[1] != right[1];
      }

      Vector2f operator +(const Vector2f& right)
      {
         return Vector2f(data[0] + right[0], data[1] + right[1]);
      }

      Vector2f operator -(const Vector2f& right)
      {
         return Vector2f(data[0] - right[0], data[1] - right[1]);
      }

      float operator[] (unsigned index) const
      {
         return data[index];
      }

      float x() const
      {
         return data[0];
      }

      float y() const
      {
         return data[1];
      }

      float& x()
      {
         return data[0];
      }

      float& y()
      {
         return data[1];
      }

   private:
      float data[2];
   };
}
