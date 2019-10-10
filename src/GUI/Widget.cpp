#include <Gui/Widget.h>
#include <Render/Node.h>
#include <Render/Geometry.h>
#include <Render/Material.h>
#include <Render/StateSet.h>
#include <Render/RenderState.h>
#include <Render/Program.h>
#include <GUI/DtGuiManager.h>

namespace vrv
{
   Widget::Widget(Widget* parent)
      : myParent(parent)
      , myGeometry(0)
      , myNode(0)
      , myMaterial(0)
      , myInitialized(false)
   {
      myNode = new Node();
     
      myMaterial = new Material();
      StateSet* ss = new StateSet(new Program("../data/shader/hud.vert",
         "../data/shader/hud.frag"));
      ss->renderState()->depthTest().setEnabled(false);

      myMaterial->setStateSet(ss);
      
      DtGuiManager::instance().registerWidget(this);
   }

   Node* Widget::node()
   {
      return myNode;
   }
}