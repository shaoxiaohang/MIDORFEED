#pragma once

#include <windows.h>

namespace vrv
{
   class Controller
   {
   public:

      Controller();

      ~Controller();

      void setHandle(HWND handle);

      virtual int close();                                    // for WM_CLOSE
      virtual int create();                                   // for WM_CREATE
      virtual int destroy();                                  // for WM_DESTROY

      virtual int keyDown(int key, LPARAM lParam);            // for WM_KEYDOWN
      virtual int keyUp(int key, LPARAM lParam);              // for WM_KEYUP
      virtual int lButtonDown(WPARAM state, int x, int y);    // for WM_LBUTTONDOWN: state, x, y
      virtual int lButtonUp(WPARAM state, int x, int y);      // for WM_LBUTTONUP: state, x, y
      virtual int mButtonDown(WPARAM state, int x, int y);    // for WM_MBUTTONDOWN: state, x, y
      virtual int mButtonUp(WPARAM state, int x, int y);      // for WM_MBUTTONUP: state, x, y
      virtual int rButtonDown(WPARAM wParam, int x, int y);   // for WM_RBUTTONDOWN: state, x, y
      virtual int rButtonUp(WPARAM wParam, int x, int y);     // for WM_RBUTTONUP: state, x, y
      virtual int mouseMove(WPARAM state, int x, int y);      // for WM_MOUSEMOVE: state, x, y
      virtual int paint();                                    // for WM_PAINT
      virtual int size(int w, int h, WPARAM wParam);          // for WM_SIZE: width, height, type(SIZE_MAXIMIZED...)
   protected:
      HWND myHandle;

   };
}