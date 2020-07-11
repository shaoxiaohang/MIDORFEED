#include <GUI/Window.h>
#include <GUI/WindowProcedure.h>
#include <GUI/WindowResource.h>
#include <iostream>

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  return DefWindowProc(hwnd, msg, wParam, lParam);
}

namespace vrv {

  Window::Window(DisplayEngine& de, HINSTANCE hInst, const std::string& name, HWND parent, WindowEventHandler* handler)
    : myInstance(hInst)
    , de_(de)
    , myTitleName(name)
    , myClassName(name)
    , myParentHandler(parent)
    , myEventHandler(handler)
    , myWinStyle(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN)
    , myWinStyleEx(WS_EX_CLIENTEDGE)
    , myX(CW_USEDEFAULT)
    , myY(CW_USEDEFAULT)
    , myWidth(CW_USEDEFAULT)
    , myHeight(CW_USEDEFAULT)
    , myMenuHandler(0)
  {
    registerClasses();
  }

  Window::~Window()
  {

  }

  void Window::setWidth(int w)
  {
    myWidth = w;
  }

  void Window::setHeight(int h)
  {
    myHeight = h;
  }

  void Window::create()
  {
    myHandler = CreateWindowEx(myWinStyleEx,
      myClassName.c_str(), myTitleName.c_str(), myWinStyle, myX, myY, myWidth, myHeight,
      myParentHandler, myMenuHandler, myInstance, (LPVOID)myEventHandler);

    myDeviceContext = GetDC(myHandler);

    ShowWindow(myHandler, SW_SHOW);
  }

  HWND Window::handler()
  {
    return myHandler;
  }

  void Window::swapBuffer()
  {
    SwapBuffers(myDeviceContext);
  }

  void Window::registerClasses()
  {
    WNDCLASSEX wc;
    wc.cbSize = sizeof(wc);
    wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = windowProcedure;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = myInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = NULL;
    wc.lpszMenuName = 0;
    wc.lpszClassName = myClassName.c_str();
    wc.hIconSm = NULL;

    if (!RegisterClassEx(&wc))
    {
      std::cout << "Failed to register window class" << std::endl;
    }
  }
}