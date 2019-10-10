#include <Gui/DtGuiManager.h>
#include <Render/Scene.h>
#include <Render/Node.h>
#include <Gui/Widget.h>

namespace vrv
{
   DtGuiManager* DtGuiManager::myInstance = 0;

   DtGuiManager::DtGuiManager(Scene* scene)
      : myScene(scene)
   {

   }

   void DtGuiManager::update(double dt)
   {

   }

   void DtGuiManager::registerWidget(Widget* widget)
   {
      myScene->guiRoot()->addChild(widget->node());
      myWidgets.push_back(widget);
   }
}