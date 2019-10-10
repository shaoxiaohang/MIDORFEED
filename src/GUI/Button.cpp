#include <GUI/Button.h>
#include <GUI/DtGuiManager.h>
#include <Render/Geometry.h>
#include <Render/Array.h>

namespace vrv
{
   Button::Button(Widget* parent)
      : Widget(parent)
   {
      DtGuiManager::instance().registerWidget(this);
   }

   void Button::initialize()
   {
      if (!myInitialized)
      {
         initializeGeometry();
         myInitialized = true;
      }
   }

   void Button::initializeGeometry()
   {
      myGeometry = new Geometry();

      ArrayVec2 pos;

      pos.add(Vector2f(-1, -1));
      pos.add(Vector2f(-0.9f, -1));
      pos.add(Vector2f(-1, -0.9f));

      pos.add(Vector2f(-1, -0.9f));
      pos.add(Vector2f(-0.9f, -1));
      pos.add(Vector2f(-0.9f, -0.9f));

      myGeometry->setVertex(&pos);
      myGeometry->addPrimitiveSet(Drawable::TRIANGLES, 0, 6);

      myGeometry->setMaterial(myMaterial);

      myNode->addDrawable(myGeometry);
   }
}