#pragma once

#include <GUI/Widget.h>

namespace vrv
{
   class Button : public Widget
   {
   public: 
      Button(Widget* parent);

      virtual void initialize();
   protected:
    
      virtual void initializeGeometry();
   };
}