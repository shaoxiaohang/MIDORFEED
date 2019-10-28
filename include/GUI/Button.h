#pragma once

#include <GUI/Widget.h>

namespace vrv
{
   class Button : public Widget
   {
   public: 
      Button(Widget* parent);

   protected:
    
      virtual void initializeGeometry();

   protected:
      Geometry* myGeometry;
   };
}