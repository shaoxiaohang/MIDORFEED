#include <GUI/WindowProcedure.h>
#include <GUI/WindowEventHandler.h>

namespace vrv
{
  // window procedure router
  LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
    LRESULT ret = 0;

    WindowEventHandler* event_handler = 0;
    event_handler = (WindowEventHandler*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

    if (msg == WM_NCCREATE)
    {
      // WM_NCCREATE message is called before non-client parts(border,
      // titlebar, menu,etc) are created. This message comes with a pointer
      // to CREATESTRUCT in lParam. The lpCreateParams member of CREATESTRUCT
      // actually contains the value of lpPraram of CreateWindowEX().
      // First, retrieve the pointrer to the controller specified when
      // Win::Window is setup.
      event_handler = (WindowEventHandler*)(((CREATESTRUCT*)lParam)->lpCreateParams);
      event_handler->SetWindowHandle(hwnd);

      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)event_handler);

      return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    if (!event_handler)
      return DefWindowProc(hwnd, msg, wParam, lParam);

    switch (msg)
    {
    case WM_CREATE:
      ret = event_handler->Create();
      break;

    case WM_SIZE:
      ret = event_handler->Resize(LOWORD(lParam), HIWORD(lParam), (int)wParam);  // width, height, type
      break;

    case WM_PAINT:
      event_handler->Paint();
      ret = DefWindowProc(hwnd, msg, wParam, lParam);
      break;

    case WM_CLOSE:
      ret = event_handler->Close();
      break;

    case WM_DESTROY:
      ret = event_handler->Destroy();
      break;

    case WM_MOUSEWHEEL:
      ret = event_handler->MouseWheel(wParam, LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
      ret = event_handler->KeyDown((int)wParam, lParam);                       // keyCode, keyDetail
      break;

    case WM_KEYUP:
    case WM_SYSKEYUP:
      ret = event_handler->KeyUp((int)wParam, lParam);                         // keyCode, keyDetail
      break;

    case WM_LBUTTONDOWN:
      ret = event_handler->LeftButtonDown(wParam, LOWORD(lParam), HIWORD(lParam)); // state, x, y
      break;

    case WM_LBUTTONUP:
      ret = event_handler->LeftButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
      break;

    case WM_RBUTTONDOWN:
      ret = event_handler->RightButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));// state, x, y
      break;

    case WM_RBUTTONUP:
      ret = event_handler->RightButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
      break;

    case WM_MBUTTONDOWN:
      ret = event_handler->MiddleButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));// state, x, y
      break;

    case WM_MBUTTONUP:
      ret = event_handler->MiddleButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
      break;

    case WM_MOUSEMOVE:
      ret = event_handler->MouseMove(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
      break;

    default:
      ret = DefWindowProc(hwnd, msg, wParam, lParam);
      break;
    }

    return ret;
  }
}