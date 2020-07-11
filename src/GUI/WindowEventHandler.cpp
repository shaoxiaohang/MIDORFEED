#include <GUI/WindowEventHandler.h>
#include <Render/DisplayEngine.h>
#include <Core/WindowEvent.h>

namespace vrv {

  WindowEventHandler::WindowEventHandler(DisplayEngine& de)
    : de_(de) {
  }

  void WindowEventHandler::SetWindowHandle(HWND handler) {
    window_handler_ = handler;
  }

  LRESULT WindowEventHandler::Create() {
    return 0;
  }

  LRESULT WindowEventHandler::Resize(int width, int height, int type) {
    WindowEvent e;
    e.setEventType(WindowEvent::WindowResize);
    e.SetResizeX(width);
    e.SetResizeY(height);
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::Paint() {
    return 0;
  }

  LRESULT WindowEventHandler::Close() {
    DestroyWindow(window_handler_);
    return 0;
  }

  LRESULT WindowEventHandler::Destroy() {
    PostQuitMessage(0);
    return 0;
  }

  LRESULT WindowEventHandler::KeyDown(int key_code, LPARAM key_detail) {
    WindowEvent e;
    e.setEventType(WindowEvent::KeyBoardDown);
    e.setKeyButton((WindowEvent::KeyButton)key_code);
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::KeyUp(int key_code, LPARAM key_detail) {
    WindowEvent e;
    e.setEventType(WindowEvent::KeyBoardUp);
    e.setKeyButton((WindowEvent::KeyButton)key_code);
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::LeftButtonDown(WPARAM state, int x, int y) {
    WindowEvent e;
    e.setEventType(WindowEvent::MouseDown);
    e.setMouseButton(WindowEvent::LeftMouseButton);
    e.setMousePosition(x, y);
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::LeftButtonUp(WPARAM state, int x, int y) {
    WindowEvent e;
    e.setEventType(WindowEvent::MouseUp);
    e.setMouseButton(WindowEvent::LeftMouseButton);
    e.setMousePosition(x, y);
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::RightButtonDown(WPARAM state, int x, int y) {
    WindowEvent e;
    e.setEventType(WindowEvent::MouseDown);
    e.setMouseButton(WindowEvent::RightMouseButton);
    e.setMousePosition(x, y);
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::RightButtonUp(WPARAM state, int x, int y) {
    WindowEvent e;
    e.setEventType(WindowEvent::MouseUp);
    e.setMouseButton(WindowEvent::RightMouseButton);
    e.setMousePosition(x, y);
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::MiddleButtonDown(WPARAM state, int x, int y) {
    WindowEvent e;
    e.setEventType(WindowEvent::MouseDown);
    e.setMouseButton(WindowEvent::RightMouseButton);
    e.setMousePosition(x, y);
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::MiddleButtonUp(WPARAM state, int x, int y) {
    WindowEvent e;
    e.setEventType(WindowEvent::MouseDown);
    e.setMouseButton(WindowEvent::RightMouseButton);
    e.setMousePosition(x, y);
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::MouseMove(WPARAM state, int x, int y) {
    WindowEvent e;
    e.setEventType(WindowEvent::MouseMove);
    e.setMousePosition(x, y);
    if (state & MK_LBUTTON)
    {
      e.setMouseButton(WindowEvent::LeftMouseButton);
    }
    else if (state & MK_RBUTTON)
    {
      e.setMouseButton(WindowEvent::RightMouseButton);
    }
    else
    {
      e.setMouseButton(WindowEvent::NoneMouseButton);
    }
    de_.handleWindowEvent(e);
    return 0;
  }

  LRESULT WindowEventHandler::MouseWheel(WPARAM state, int x, int y) {
    short zDelta = GET_WHEEL_DELTA_WPARAM(state);
    WindowEvent e;
    e.setEventType(WindowEvent::Wheel);
    e.setWheelDelta(zDelta);
    de_.handleWindowEvent(e);
    return 0;
  }
}