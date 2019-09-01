#pragma once
#include<memory>

namespace vrv
{
	class Vector2i
	{
	public:
      Vector2i()
      {
         memset(data, 0, sizeof(data));
      }

      Vector2i(int x, int y)
      {
         data[0] = x;
         data[1] = y;
      }


      Vector2i& operator =(const Vector2i& right)
      {
         data[0] = right[0];
         data[1] = right[1];
         return *this;
      }

      bool operator ==(const Vector2i& right)
      {
         return data[0] == right[0] && data[1] == right[1];
      }

      bool operator !=(const Vector2i& right)
      {
         return data[0] != right[0] || data[1] != right[1];
      }

      Vector2i operator +(const Vector2i& right)
      {
         return Vector2i(data[0] + right[0], data[1] + right[1]);
      }

      Vector2i operator -(const Vector2i& right)
      {
         return Vector2i(data[0] - right[0], data[1] - right[1]);
      }

      int operator[] (unsigned index) const
      {
         return data[index];
      }

      int x() const
      {
         return data[0];
      }

      int y() const
      {
         return data[1];
      }

      int& x()
      {
         return data[0];
      }

      int& y()
      {
         return data[1];
      }
 
   private:
      int data[2];
	};
}
