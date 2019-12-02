#include <GUI/Controller.h>

namespace vrv
{
   Controller::Controller() : myHandle(0)
   {

   }

   Controller::~Controller()
   {
      DestroyWindow(myHandle);
   }

   void Controller::setHandle(HWND handle)
   {
      myHandle = handle;
   }

   int Controller::close()
   {
      return 0;
   }

   int Controller::create()
   {
      return 0;
   }

   int Controller::destroy()
   {
      return 0;
   }

   int Controller::hScroll(WPARAM wParam, LPARAM lParam)
   {
      return 0;
   }

   int Controller::keyDown(int key, LPARAM lParam)
   {
      return 0;
   }

   int Controller::keyUp(int key, LPARAM lParam)
   {
      return 0;
   }

   int Controller::lButtonDown(WPARAM state, int x, int y)
   {
      return 0;
   }

   int Controller::lButtonUp(WPARAM state, int x, int y)
   {
      return 0;
   }

   int Controller::mButtonDown(WPARAM state, int x, int y)
   {
      return 0;
   }

   int Controller::mButtonUp(WPARAM state, int x, int y)
   {
      return 0;
   }

   int Controller::rButtonDown(WPARAM wParam, int x, int y) 
   {
      return 0;
   }

   int Controller::rButtonUp(WPARAM wParam, int x, int y)
   {
      return 0;
   }

   int Controller::mouseMove(WPARAM state, int x, int y) 
   {
      return 0;
   }

   int Controller::paint()
   {
      return 0;
   }

   int Controller::size(int w, int h, WPARAM type)
   {
      return 0;
   }
}