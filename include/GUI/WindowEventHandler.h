#pragma once

#include <Windows.h>

namespace vrv {

  class DisplayEngine;

  class WindowEventHandler {
  public:

    WindowEventHandler(DisplayEngine& de);

    void SetWindowHandle(HWND handler);

    LRESULT Create();

    LRESULT Resize(int width, int height, int type);

    LRESULT Paint();

    LRESULT Close();

    LRESULT Destroy();

    LRESULT KeyDown(int key_code, LPARAM key_detail);

    LRESULT KeyUp(int key_code, LPARAM key_detail);

    LRESULT LeftButtonDown(WPARAM state, int x, int y);

    LRESULT LeftButtonUp(WPARAM state, int x, int y);

    LRESULT RightButtonDown(WPARAM state, int x, int y);

    LRESULT RightButtonUp(WPARAM state, int x, int y);

    LRESULT MiddleButtonDown(WPARAM state, int x, int y);

    LRESULT MiddleButtonUp(WPARAM state, int x, int y);

    LRESULT MouseMove(WPARAM state, int x, int y);

    LRESULT MouseWheel(WPARAM state, int x, int y);

  protected:
    DisplayEngine& de_;
    HWND window_handler_;
  };
}