#include <GUI/WindowResource.h>

namespace vrv
{
   WindowResource::WindowResource(int id, ResourceType type)
      : myResourceType(type)
      , myID(id)
   {
      myResourceName = MAKEINTRESOURCE(id);
   }
}