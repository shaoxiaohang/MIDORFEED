#include <Core/Bound.h>

namespace vrv
{
   Bound::Bound()
   {

   }

   Bound::Bound(Vector3f min, Vector3f max)
   {
      myMinVector = min;
      myMaxVector = max;
   }

   void Bound::setMinVector(Vector3f v)
   {
      myMinVector = v;
   }

   void Bound::setMaxVector(Vector3f v)
   {
      myMaxVector = v;
   }

   Vector3f Bound::minVector() const
   {
      return myMinVector;
   }

   Vector3f Bound::maxVector() const
   {
      return myMaxVector;
   }

   float Bound::radius()
   {
      Vector3f l = myMaxVector - myMinVector;
      return l.length() / 2;
   }

   void Bound::expand(const Bound& bound)
   {
      myMinVector.x() = std::min(myMinVector.x(), bound.minVector().x());
      myMinVector.y() = std::min(myMinVector.y(), bound.minVector().y());
      myMinVector.z() = std::min(myMinVector.z(), bound.minVector().z());

      myMaxVector.x() = std::max(myMaxVector.x(), bound.maxVector().x());
      myMaxVector.y() = std::max(myMaxVector.y(), bound.maxVector().y());
      myMaxVector.z() = std::max(myMaxVector.z(), bound.maxVector().z());
   }

   Bound Bound::scale(Matrix4f m)
   {
      return Bound((m * myMinVector).xyz(), (m * myMaxVector).xyz());
   }

   Bound Bound::scale(float scalar)
   {
      return Bound(myMinVector*scalar, myMaxVector * scalar);
   }

   Bound Bound::scale(Vector3f scalar)
   {
      return Bound(myMinVector*scalar, myMaxVector * scalar);
   }

   Vector3f Bound::center()
   {
      return (myMinVector + myMaxVector) / 2;
   }
}