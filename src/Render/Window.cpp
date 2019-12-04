//#include <Render/Window.h>
//#include <Render/OpenGLContext.h>
//#include <Render/Viewer.h>
//#include <Core/WindowEvent.h>
//#include <iostream>
//#include <map>
//
//namespace vrv
//{
//   class Win32WindowingSystem
//   {
//   public:
//
//      static Win32WindowingSystem* instance()
//      {
//         static Win32WindowingSystem s_system;
//         return &s_system;
//      }
//
//      void registerWindow(HWND hwnd, Window* window)
//      {
//         if (myWindowHandles.find(hwnd) == myWindowHandles.end())
//         {
//            myWindowHandles[hwnd] = window;
//         }
//      }
//
//      Window* getWindow(HWND hwnd)
//      {
//         if (myWindowHandles.find(hwnd) != myWindowHandles.end())
//         {
//            return myWindowHandles[hwnd];
//         }
//
//         return 0;
//      }
//
//   protected:
//      typedef std::map<  HWND, Window* >  WindowHandles;
//      WindowHandles myWindowHandles;
//   };
//
//   LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//   {
//      Window* window = Win32WindowingSystem::instance()->getWindow(hwnd);
//      if (window)
//      {
//         return window->handleNativeWindowingEvent(hwnd, uMsg, wParam, lParam);
//      }
//      else
//      {
//         return DefWindowProc(hwnd, uMsg, wParam, lParam);
//      }
//   }
//
//   Window::Window(Viewer* viewer)
//      : myWindowHandle(0)
//      , myDeviceContext(0)
//      , myOpenGLContext(0)
//      , myWindowClassName("WindowClass")
//      , myWindowName("Window")
//      , myWidth(800)
//      , myHeight(600)
//      , myViewer(viewer)
//   {
//
//   }
//
//   int Window::width()
//   {
//      return myWidth;
//   }
//
//   int Window::height()
//   {
//      return myHeight;
//   }
//
//   void Window::pickMessage()
//   {
//      MSG msg = {};
//      GetMessage(&msg, NULL, 0, 0);
//      TranslateMessage(&msg);
//      DispatchMessage(&msg);
//   }
//
//   void Window::initiailze()
//   {
//      registerWindowClass();
//      createWindow();
//      createContext();
//      showWindow();
//   }
//
//   LRESULT Window::handleNativeWindowingEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//   {
//      switch (uMsg)
//      {
//      case WM_SIZE:
//      {
//         int width = LOWORD(lParam);
//         int height = HIWORD(lParam);
//
//         onResize(uMsg, width, height);
//
//         return 0;
//      }
//      case WM_CLOSE:
//      {
//         DestroyWindow(hwnd);
//         return 0;
//      }
//      case WM_DESTROY:
//      {
//         PostQuitMessage(0);
//         return 0;
//      }
//      case WM_MOUSEMOVE:
//      {
//         WindowEvent e;
//         e.setEventType(WindowEvent::MouseMove);
//         int x = LOWORD(lParam);
//         int y = HIWORD(lParam);
//         e.setMousePosition(x, y);
//         if (wParam & MK_LBUTTON)
//         {
//            e.setMouseButton(WindowEvent::LeftMouseButton);
//         }
//         else if (wParam & MK_RBUTTON)
//         {
//            e.setMouseButton(WindowEvent::RightMouseButton);
//         }
//         else
//         {
//            e.setMouseButton(WindowEvent::NoneMouseButton);
//         }
//         myViewer->handleWindowEvent(e);
//         return 0;
//      }
//      case WM_LBUTTONDOWN:
//      {
//         WindowEvent e;
//         e.setEventType(WindowEvent::MouseDown);
//         e.setMouseButton(WindowEvent::LeftMouseButton);
//         int x = LOWORD(lParam);
//         int y = HIWORD(lParam);
//         e.setMousePosition(x, y);
//         myViewer->handleWindowEvent(e);
//         return 0;
//      }
//      case WM_LBUTTONUP:
//      {
//         WindowEvent e;
//         e.setEventType(WindowEvent::MouseUp);
//         e.setMouseButton(WindowEvent::LeftMouseButton);
//         int x = LOWORD(lParam);
//         int y = HIWORD(lParam);
//         e.setMousePosition(x, y);
//         myViewer->handleWindowEvent(e);
//         return 0;
//      }
//      case WM_RBUTTONDOWN:
//      {
//         WindowEvent e;
//         e.setEventType(WindowEvent::MouseDown);
//         e.setMouseButton(WindowEvent::RightMouseButton);
//         int x = LOWORD(lParam);
//         int y = HIWORD(lParam);
//         e.setMousePosition(x, y);
//         myViewer->handleWindowEvent(e);
//         return 0;
//      }
//      case WM_RBUTTONUP:
//      {
//         WindowEvent e;
//         e.setEventType(WindowEvent::MouseUp);
//         e.setMouseButton(WindowEvent::RightMouseButton);
//         int x = LOWORD(lParam);
//         int y = HIWORD(lParam);
//         e.setMousePosition(x, y);
//         myViewer->handleWindowEvent(e);
//         return 0;
//      }
//      case WM_KEYDOWN:
//      {
//         WindowEvent e;
//         e.setEventType(WindowEvent::KeyBoardDown);
//         e.setKeyButton((WindowEvent::KeyButton)wParam);
//         myViewer->handleWindowEvent(e);
//         return 0;
//      }
//      case WM_KEYUP:
//      {
//         WindowEvent e;
//         e.setEventType(WindowEvent::KeyBoardUp);
//         e.setKeyButton((WindowEvent::KeyButton)wParam);
//         myViewer->handleWindowEvent(e);
//         return 0;
//      }
//      case WM_MOUSEWHEEL:
//      {
//         short zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
//         WindowEvent e;
//         e.setEventType(WindowEvent::Wheel);
//         e.setWheelDelta(zDelta);
//         myViewer->handleWindowEvent(e);
//      }
//      default:
//         return DefWindowProc(hwnd, uMsg, wParam, lParam);
//         break;
//      }
//   }
//
//   bool Window::registerWindowClass()
//   {
//      HINSTANCE hinst = GetModuleHandle(NULL);
//
//      WNDCLASSEX wc;
//      wc.cbSize = sizeof(WNDCLASSEX);
//      wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
//      wc.lpfnWndProc = WindowProc;
//      wc.cbClsExtra = 0;
//      wc.cbWndExtra = 0;
//      wc.hInstance = hinst;
//      wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//      wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//      wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//      wc.lpszMenuName = NULL;
//      wc.lpszClassName = myWindowClassName.c_str();
//      wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//      if (!RegisterClassEx(&wc))
//      {
//         std::cout << "Failed to register window class" << std::endl;
//         return false;
//      }
//   }
//
//   bool Window::createWindow()
//   {
//      HINSTANCE hinst = GetModuleHandle(NULL);
//
//      HMENU menu = LoadMenu(hinst, MAKEINTRESOURCE(IDR_MENU1));
//
//      myWindowHandle = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
//         myWindowClassName.c_str(),
//         myWindowName.c_str(),
//         WS_OVERLAPPEDWINDOW,
//         CW_USEDEFAULT, CW_USEDEFAULT, myWidth, myHeight, NULL, menu, hinst, NULL);
//
//      if (!myWindowHandle)
//      {
//         std::cout << "Failed to create window" << std::endl;
//         return false;
//      }
//
//
//      HWND button = CreateWindow("BUTTON", "OK", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
//         10, 10, 100, 100, myWindowHandle, NULL, hinst, NULL);
//
//
//      Win32WindowingSystem::instance()->registerWindow(myWindowHandle, this);
//
//      myDeviceContext = GetDC(myWindowHandle);
//      if (myDeviceContext == 0)
//      {
//         std::cout << "Unable to get window device context" << std::endl;
//         return false;
//      }
//
//      return true;
//   }
//
//   bool Window::createContext()
//   {
//      myOpenGLContext = new OpenGLContext(myWindowHandle);
//      myOpenGLContext->initialize();
//      if (!myOpenGLContext)
//      {
//         return false;
//      }
//      return true;
//   }
//
//   void Window::showWindow()
//   {
//      ShowWindow(myWindowHandle, 10);
//   }
//
//   void Window::onResize(UINT flag, int width, int height)
//   {
//      myWidth = width;
//      myHeight = height;
//      glViewport(0, 0, myWidth, myHeight);
//   }
//
//   bool Window::swapBuffer()
//   {
//      return SwapBuffers(myDeviceContext);
//   }
//}