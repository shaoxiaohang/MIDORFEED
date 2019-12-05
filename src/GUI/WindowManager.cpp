#include <GUI/WindowManager.h>
#include <GUI/ControllerMain.h>
#include <GUI/Window.h>
#include <GUI/MainWindow.h>

namespace vrv
{
   WindowManager::WindowManager(const std::string& name, int mainWindowWidth, int mainWindowHeight)
      : myMainWindow(0)
      , myRenderWindow(0)
      , myMainWindowName(name)
      , myMainWindowWidth(mainWindowWidth)
      , myMainWindowHeight(mainWindowHeight)
   {
   }


   void WindowManager::initialize()
   {
      myMainWindow = new MainWindow(myMainWindowName, myMainWindowWidth, myMainWindowHeight);
      myMainWindow->create();
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
      if(myRenderWindow)
         myRenderWindow->swapBuffer();
      DialogWindowMap::iterator iter = myDialogWindows.begin();
      DialogWindowMap::iterator end = myDialogWindows.end();
      for (; iter != end; ++iter)
      {
         iter->second->swapBuffer();
      }
   }
}