#include <GUI/WindowManager.h>
#include <GUI/ControllerMain.h>
#include <GUI/Window.h>

namespace vrv
{
   WindowManager::WindowManager()
      : myMainWindow(0)
      , myRenderWindow(0)
   {
      initialize();
   }


   void WindowManager::initialize()
   {
      HINSTANCE hinst = GetModuleHandle(NULL);

      ControllerMain mainCtrl;
      myMainWindow = new Window(hinst, "MainWindow", 0, &mainCtrl);

      myRenderWindow = new Window(hinst, "RenderWindow", myMainWindow->handler(), )
   }
}