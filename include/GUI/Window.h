#pragma once

#include<Windows.h>
#include<string>

namespace vrv
{
   class WindowEventHandler;
   class WindowResource;

   class Window
   {
   public:

      Window(HINSTANCE hInst, const std::string& name, HWND parent, WindowEventHandler* handler = 0);

      ~Window();

      void setWidth(int w);

      void setHeight(int h);

      void setMenu(WindowResource* menu);

      void create();

      HWND handler();

      void swapBuffer();

   protected:

      void registerClasses();

   protected:
      std::string myTitleName;
      std::string myClassName;
      int myX;
      int myY;
      int myWidth;
      int myHeight;
      DWORD myWinStyle;
      DWORD myWinStyleEx;
      HWND myHandler;
      WNDCLASSEX myWinClass;
      HMENU myMenuHandler;
      HWND myParentHandler;
      HINSTANCE myInstance;
      HDC myDeviceContext;
      WindowEventHandler* myEventHandler;
   };
}