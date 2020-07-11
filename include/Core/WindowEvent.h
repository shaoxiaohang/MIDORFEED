#pragma once

namespace vrv
{
   class WindowEvent
   {
   public:
      enum EventType
      {
         MouseDown,
         MouseUp,
         MouseMove,
         KeyBoardUp,
         KeyBoardDown,
         Wheel,
         WindowResize,
         NoneEvent
      };

      enum MouseButton
      {
         LeftMouseButton,
         RightMouseButton,
         NoneMouseButton
      };

      enum KeyButton
      {
         A = 0x41,
         B,
         C,
         D,
         E,
         F,
         G,
         H,
         I,
         J,
         K,
         L,
         M,
         N,
         O,
         P,
         Q,
         R,
         S,
         T,
         U,
         V,
         W,
         X,
         Y,
         Z,
         NoneKeyButton
      };

      WindowEvent();

      void setEventType(EventType eventType);

      EventType eventType() const;

      void setMousePosition(int x, int y);

      int mousePositionX() const;
      int mousePositionY() const;

      void setMouseButton(MouseButton button);
      MouseButton mouseButton() const;

      void setKeyButton(KeyButton button);
      KeyButton keyButton() const;

      void setWheelDelta(int);
      int wheelDelta() const;

      int GetResizeX();
      int GetResizeY();

      void SetResizeX(int x);
      void SetResizeY(int y);

   protected:
      EventType myEventType;
      int myMousePositionX;
      int myMousePositionY;
      MouseButton myMouseButton;
      KeyButton myKeyButton;
      int myWheelDelta;
      int resize_X_;
      int resize_Y_;
   };
};