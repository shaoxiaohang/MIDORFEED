#pragma once

#include <Core/Vector3f.h>
#include <Core/Matrix4f.h>
namespace vrv
{
   class Bound
   {
   public:
      Bound(Vector3f min, Vector3f max);

      Bound();
      
      void setMinVector(Vector3f);

      void setMaxVector(Vector3f);

      Vector3f minVector() const;

      Vector3f maxVector() const;

      float radius();

      void expand(const Bound& bound);

      Bound scale(Matrix4f m);

      Bound scale(float scalar);

      Bound scale(Vector3f scalar);
   protected:

      Vector3f myMinVector;
      Vector3f myMaxVector;
   };
}