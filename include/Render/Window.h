//#pragma once
//
//#include <Windows.h>
//#include <string>
//namespace vrv
//{
//   class OpenGLContext;
//   class Viewer;
//
//   //https://docs.microsoft.com/en-us/windows/desktop/learnwin32/writing-the-window-procedure
//   class Window
//   {
//   public:
//
//      Window(Viewer* viewer);
//
//      void initiailze();
//
//      LRESULT handleNativeWindowingEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//      int width();
//      int height();
//
//      void pickMessage();
//
//      bool swapBuffer();
//
//   protected:
//
//      bool registerWindowClass();
//
//      bool createWindow();
//
//      bool createContext();
//
//      void showWindow();
//
//      void onResize(UINT flag, int width, int height);
//
// 
//
//   protected:
//      HWND myWindowHandle;
//      HDC myDeviceContext;
//      std::string myWindowClassName;
//      std::string myWindowName;
//      OpenGLContext* myOpenGLContext;
//      Viewer* myViewer;
//      int myWidth;
//      int myHeight;
//      std::string myName;
//   };
//}