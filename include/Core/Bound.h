#pragma once

#include<Core/Vector3f.h>
namespace vrv
{
   class Bound
   {
   public:
      Bound();
      
      void setMinVector(Vector3f);

      void setMaxVector(Vector3f);

      Vector3f minVector() const;

      Vector3f maxVector() const;

      float radius();

      void expand(const Bound& bound);


   protected:

      Vector3f myMinVector;
      Vector3f myMaxVector;
   };
}