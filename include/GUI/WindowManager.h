#pragma once

#include <map>
#include <string>

namespace vrv
{
   class MainWindow;
   class DisplayEngine;

   class WindowManager
   {
   public:

      WindowManager(DisplayEngine& de, const std::string& name, int mainWindowWidth, int mainWindowHeight);

      void initialize();

      void pickMessage();

      void swapBuffers();

   protected:
      std::string myMainWindowName;
      int myMainWindowWidth;
      int myMainWindowHeight;
      MainWindow* myMainWindow;
      DisplayEngine& de_;
   };
}