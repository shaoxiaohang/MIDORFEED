#pragma once

#include <map>
#include <string>

namespace vrv
{
   class Window;

   class WindowManager
   {
   public:
      typedef std::map<std::string, Window*> DialogWindowMap;

      WindowManager(const std::string& name, int mainWindowWidth, int mainWindowHeight);

      void initialize();

      void pickMessage();

      void swapBuffers();

   protected:
      std::string myMainWindowName;
      int myMainWindowWidth;
      int myMainWindowHeight;
      Window* myMainWindow;
      Window* myRenderWindow;
      DialogWindowMap myDialogWindows;
   };
}