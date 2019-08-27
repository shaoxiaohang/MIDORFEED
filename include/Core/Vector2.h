#pragma once

namespace vrv
{
	class Vector2f
	{
	public:
      Vector2f();

      Vector2f(float x, float y);

      Vector2f& operator =(const Vector2f& right);

      bool operator ==(const Vector2f& right);

      bool operator !=(const Vector2f& right);

      Vector2f operator +(const Vector2f& right);

      Vector2f operator -(const Vector2f& right);

      float operator[] (unsigned index) const;

      float x() const;

      float y() const;

      float& x();

      float& y();
 
   private:
      float data[2];
	};
}