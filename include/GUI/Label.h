#pragma once

#include <GUI/Widget.h>
#include <string>
namespace vrv
{
   class Label : public Widget
   {
   public:

      Label(Widget* parent);

      void setText(const std::string& text);

   protected:
      void initializeGeometry();

   protected:
      std::string myText;
   };
}