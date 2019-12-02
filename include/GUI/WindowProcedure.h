#pragma once

#include <windows.h>

namespace vrv
{
   // window procedure router
   LRESULT CALLBACK windowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
}