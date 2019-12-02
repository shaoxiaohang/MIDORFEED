#include <GUI/WindowProcedure.h>
#include <GUI/Controller.h>

namespace vrv
{
   // window procedure router
   LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      LRESULT ret = 0;

      Controller* ctrl = 0;
      ctrl = (Controller*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

      if (msg == WM_NCCREATE)
      {
         // WM_NCCREATE message is called before non-client parts(border,
         // titlebar, menu,etc) are created. This message comes with a pointer
         // to CREATESTRUCT in lParam. The lpCreateParams member of CREATESTRUCT
         // actually contains the value of lpPraram of CreateWindowEX().
         // First, retrieve the pointrer to the controller specified when
         // Win::Window is setup.
         ctrl = (Controller*)(((CREATESTRUCT*)lParam)->lpCreateParams);
         ctrl->setHandle(hwnd);

         SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)ctrl);

         return DefWindowProc(hwnd, msg, wParam, lParam);
      }

      if (!ctrl)
         return DefWindowProc(hwnd, msg, wParam, lParam);

      switch (msg)
      {
      case WM_CREATE:
         ret = ctrl->create();
         break;

      case WM_SIZE:
         ret = ctrl->size(LOWORD(lParam), HIWORD(lParam), (int)wParam);  // width, height, type
         break;

      case WM_PAINT:
         ctrl->paint();
         ret = DefWindowProc(hwnd, msg, wParam, lParam);
         break;

      case WM_CLOSE:
         ret = ctrl->close();
         break;

      case WM_DESTROY:
         ret = ctrl->destroy();
         break;

      case WM_KEYDOWN:
      case WM_SYSKEYDOWN:
         ret = ctrl->keyDown((int)wParam, lParam);                       // keyCode, keyDetail
         break;

      case WM_KEYUP:
      case WM_SYSKEYUP:
         ret = ctrl->keyUp((int)wParam, lParam);                         // keyCode, keyDetail
         break;

      case WM_LBUTTONDOWN:
         ret = ctrl->lButtonDown(wParam, LOWORD(lParam), HIWORD(lParam)); // state, x, y
         break;

      case WM_LBUTTONUP:
         ret = ctrl->lButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
         break;

      case WM_RBUTTONDOWN:
         ret = ctrl->rButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));// state, x, y
         break;

      case WM_RBUTTONUP:
         ret = ctrl->rButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
         break;

      case WM_MBUTTONDOWN:
         ret = ctrl->mButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));// state, x, y
         break;

      case WM_MBUTTONUP:
         ret = ctrl->mButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
         break;

      case WM_MOUSEMOVE:
         ret = ctrl->mouseMove(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
         break;

      default:
         ret = DefWindowProc(hwnd, msg, wParam, lParam);
         break;
      }

      return ret;
   }
}