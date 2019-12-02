#pragma once

#include <GUI/Controller.h>

namespace vrv
{
   class ControllerMain :public Controller
   {
   public:
      ControllerMain();
      ~ControllerMain() {};

      int close();
      int create();                            
      int destroy();
      int size(int w, int h, WPARAM wParam);
   };
}