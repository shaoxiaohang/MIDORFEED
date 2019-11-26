#include <GUI/Window.h>

namespace vrv
{
   Window::Window(HINSTANCE hInst, const std::string& name, HWND parent)
      : myInstance(hInst)
      , myName(name)
      , myParentHandler(parent)
   {

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

   void Window::setMenuName(LPCTSTR name)
   {
      
   }

   void Window::registerClasses()
   {

   }
}