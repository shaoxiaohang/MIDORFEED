//#include <GUI/Button.h>
//#include <GUI/GuiManager.h>
//#include <Render/Geometry.h>
//#include <Render/Array.h>
//#include <Render/Program.h>
//#include <Render/Material.h>
//#include <Render/StateSet.h>
//#include <Render/RenderState.h>
//
//namespace vrv
//{
//   Button::Button(Widget* parent)
//      : Widget(parent)
//   {
//      GuiManager::instance().registerWidget(this);
//   }
//
//
//
//   void Button::initializeGeometry()
//   {
//      Material* material = new Material();
//      material->stateSet()->renderState()->depthTest().setEnabled(false);
//      material->stateSet()->setProgram(new Program("../data/shader/button.vert", "../data/shader/button.frag"));
//
//      myGeometry = new Geometry();
//
//      ArrayVec2 pos;
//
//      pos.add(Vector2f(-1, -1));
//      pos.add(Vector2f(-0.9f, -1));
//      pos.add(Vector2f(-1, -0.9f));
//
//      pos.add(Vector2f(-1, -0.9f));
//      pos.add(Vector2f(-0.9f, -1));
//      pos.add(Vector2f(-0.9f, -0.9f));
//
//      myGeometry->addVertexAttribute(0, &pos);
//      myGeometry->addPrimitiveSet(Drawable::TRIANGLES, 0, 6);
//
//      myGeometry->setMaterial(material);
//
//      myNode->addDrawable(myGeometry);
//   }
//}