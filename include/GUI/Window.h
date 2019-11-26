#pragma once

#include<Windows.h>
#include<string>

namespace vrv
{
   class Window
   {
   public:

      Window(HINSTANCE hInst, const std::string& name, HWND parent);

      ~Window();

      void setWidth(int w);

      void setHeight(int h);

      void setMenuName(LPCTSTR name);

   protected:

      void registerClasses();

   protected:
      std::string myName;
      int myX;
      int myY;
      int myWidth;
      int myHeight;
      HWND myHandler;
      WNDCLASSEX myWinClass;
      LPCTSTR myMenuName;
      HWND myParentHandler;
      HINSTANCE myInstance;
   };
}