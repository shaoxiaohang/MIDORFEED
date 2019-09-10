#include <Core/Bound.h>

namespace vrv
{
   Bound::Bound()
   {

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
}