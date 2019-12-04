#include <GUI/WindowManager.h>
#include <GUI/ControllerMain.h>
#include <GUI/Window.h>

namespace vrv
{
   WindowManager::WindowManager(int mainWindowWidth, int mainWindowHeight)
      : myMainWindow(0)
      , myRenderWindow(0)
      , myMainWindowWidth(mainWindowWidth)
      , myMainWindowHeight(mainWindowHeight)
   {
      initialize();
   }


   void WindowManager::initialize()
   {
      myMainWindow = new ()
   }
}