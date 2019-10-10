#pragma once

#include <Core/Singleton.h>
#include <vector>

namespace vrv
{
   class Widget;
   class Scene;
   class DtGuiManager : public Singleton<DtGuiManager>
   {
   public:
      DtGuiManager(Scene* scene);

      void update(double dt);

      void registerWidget(Widget*);

   protected:
      Scene* myScene;
      std::vector<Widget*> myWidgets;
   };
}