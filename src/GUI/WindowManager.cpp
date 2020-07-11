#include <GUI/WindowManager.h>
#include <GUI/Window.h>
#include <GUI/MainWindow.h>

namespace vrv
{
   WindowManager::WindowManager(DisplayEngine& de, const std::string& name, int mainWindowWidth, int mainWindowHeight)
      : myMainWindow(0)
      , de_(de)
      , myMainWindowName(name)
      , myMainWindowWidth(mainWindowWidth)
      , myMainWindowHeight(mainWindowHeight)
   {
   }


   void WindowManager::initialize()
   {
      myMainWindow = new MainWindow(de_, myMainWindowName, myMainWindowWidth, myMainWindowHeight);
      myMainWindow->create();
      myMainWindow->Initialize();
   }

   void WindowManager::pickMessage()
   {
      MSG msg = {};
      GetMessage(&msg, NULL, 0, 0);
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   void WindowManager::swapBuffers()
   {
      if (myMainWindow)
         myMainWindow->swapBuffer();
   }
}