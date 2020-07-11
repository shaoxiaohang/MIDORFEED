//#include <Gui/GuiManager.h>
//#include <Render/Scene.h>
//#include <Render/Node.h>
//#include <Gui/Widget.h>
//
//namespace vrv
//{
//   GuiManager* GuiManager::myInstance = 0;
//
//   GuiManager::GuiManager(Scene* scene)
//      : myScene(scene)
//   {
//
//   }
//
//   void GuiManager::update(double dt)
//   {
//      for (Widget* widget : myWidgets)
//      {
//         if (widget)
//         {
//            widget->initialize();
//         }
//      }
//   }
//
//   void GuiManager::registerWidget(Widget* widget)
//   {
//      myScene->guiRoot()->addChild(widget->node());
//      myWidgets.push_back(widget);
//   }
//}