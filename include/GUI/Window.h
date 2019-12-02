#pragma once

#include<Windows.h>
#include<string>

namespace vrv
{
   class Controller;

   class Window
   {
   public:

      Window(HINSTANCE hInst, const std::string& name, HWND parent, Controller* controller);

      ~Window();

      void setWidth(int w);

      void setHeight(int h);

      void setMenuName(LPCTSTR name);

      void create();

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
      Controller* myController;
   };
}