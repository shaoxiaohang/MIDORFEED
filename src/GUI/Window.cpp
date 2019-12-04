#include <GUI/Window.h>
#include <GUI/WindowProcedure.h>
#include <GUI/WindowResource.h>
#include <iostream>

namespace vrv
{
   Window::Window(HINSTANCE hInst, const std::string& name, HWND parent, Controller* controller)
      : myInstance(hInst)
      , myTitleName(name)
      , myClassName(name)
      , myParentHandler(parent)
      , myController(controller)
      , myWinStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN)
      , myWinStyleEx(WS_EX_CLIENTEDGE)
      , myX(CW_USEDEFAULT)
      , myY(CW_USEDEFAULT)
      , myWidth(CW_USEDEFAULT)
      , myHeight(CW_USEDEFAULT)
      , myMenuHandler(0)
   {
      registerClasses();
   }

   Window::~Window()
   {

   }

   void Window::setWidth(int w)
   {
      myWidth = w;
   }

   void Window::setHeight(int h)
   {
      myHeight = h;
   }

   void Window::setMenu(WindowResource* menu)
   {
      if (menu)
      {
         myMenuHandler = LoadMenu(myInstance, menu->name());
      }
   }

   void Window::create()
   {
      myHandler = CreateWindowEx(myWinStyleEx,
         myClassName.c_str(), myTitleName.c_str(), myWinStyle, myX, myY, myWidth, myHeight,
         myParentHandler, myMenuHandler, myInstance, (LPVOID)myController);
   }

   HWND Window::handler()
   {
      return myHandler;
   }

   void Window::registerClasses()
   {
      WNDCLASSEX wc;
      wc.cbSize = sizeof(WNDCLASSEX);
      wc.style = myWinStyle;
      wc.lpfnWndProc = windowProcedure;
      wc.cbClsExtra = 0;
      wc.cbWndExtra = 0;
      wc.hInstance = myInstance;
      wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      wc.lpszMenuName = NULL;
      wc.lpszClassName = myClassName.c_str();
      wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

      if (!RegisterClassEx(&wc))
      {
         std::cout << "Failed to register window class" << std::endl;
      }
   }
}