#include <Core/WindowEvent.h>

namespace vrv
{
   WindowEvent::WindowEvent()
      : myEventType(NoneEvent)
      , myMouseButton(NoneMouseButton)
      , myKeyButton(NoneKeyButton)
      , myMousePositionX(0)
      , myMousePositionY(0)
   {

   }

   void WindowEvent::setEventType(EventType eventType)
   {
      myEventType = eventType;
   }

   WindowEvent::EventType WindowEvent::eventType() const
   {
      return myEventType;
   }

   void WindowEvent::setMousePosition(int x, int y)
   {
      myMousePositionX = x;
      myMousePositionY = y;
   }

   int WindowEvent::mousePositionX() const
   {
      return myMousePositionX;
   }

   int WindowEvent::mousePositionY() const
   {
      return myMousePositionY;
   }

   void WindowEvent::setMouseButton(MouseButton button)
   {
      myMouseButton = button;
   }

   WindowEvent::MouseButton WindowEvent::mouseButton() const
   {
      return myMouseButton;
   }

   void WindowEvent::setKeyButton(KeyButton button)
   {
      myKeyButton = button;
   }

   WindowEvent::KeyButton WindowEvent::keyButton() const
   {
      return myKeyButton;
   }

   void WindowEvent::setWheelDelta(int delta)
   {
      myWheelDelta = delta;
   }

   int WindowEvent::wheelDelta() const
   {
      return myWheelDelta;
   }

   int WindowEvent::GetResizeX() {
     return resize_X_;
   }

   int WindowEvent::GetResizeY() {
     return resize_Y_;
   }

   void WindowEvent::SetResizeX(int x) {
     resize_X_ = x;
   }

   void WindowEvent::SetResizeY(int y) {
     resize_Y_ = y;
   }
}