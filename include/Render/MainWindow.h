#pragma once

#include <Windows.h>
#include <string>
namespace vrv
{
   class OpenGLContext;
   class Viewer;

   //https://docs.microsoft.com/en-us/windows/desktop/learnwin32/writing-the-window-procedure
   class MainWindow
   {
   public:

      MainWindow(Viewer* viewer);

      void initiailze();

      LRESULT handleNativeWindowingEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

      int width();
      int height();

      void eventLoop();

   protected:

      bool registerWindowClass();

      bool createWindow();

      bool createContext();

      void showWindow();

      void onResize(UINT flag, int width, int height);

      bool swapBuffer();

   protected:
      HWND myWindowHandle;
      HDC myDeviceContext;
      std::string myWindowClassName;
      std::string myWindowName;
      OpenGLContext* myOpenGLContext;
      Viewer* myViewer;
      int myWidth;
      int myHeight;
   };
}