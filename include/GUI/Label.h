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

      void setFontSize(int size);
      int fontSize();

      void setPosition(float x, float y);

   protected:
      void initializeGeometry();

   protected:
      std::string myText;
      int myFontSize;
      float myPositionX;
      float myPositionY;
   };
}