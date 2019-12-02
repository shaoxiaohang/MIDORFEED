#pragma once

#include <windows.h>

namespace vrv
{
   class WindowResource
   {
   public:

      enum ResourceType
      {
         Resource_Menu
      };

      WindowResource(int id, ResourceType type);



   protected:
      ResourceType myResourceType;
      int myID;
      LPCSTR myResourceName;
   };
}