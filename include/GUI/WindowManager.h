#pragma once

#include <map>
#include <string>

namespace vrv
{
   class Window;

   class WindowManager
   {
   public:
      WindowManager();

   protected:

      void initialize();

   protected:

      Window* myMainWindow;
      Window* myRenderWindow;
      std::map<std::string, Window*> myDialogWindows;

   };
}