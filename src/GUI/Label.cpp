#include <GUI/Label.h>
#include <Render/Program.h>
#include <Render/Material.h>
#include <Render/StateSet.h>
#include <Render/Geometry.h>
#include <Render/RenderState.h>
#include <GUI/FontManager.h>

namespace vrv
{
   void Label::setText(const std::string& text)
   {
      myText = text;
   }

   Label::Label(Widget* parent)
      : Widget(parent)
      , myFontSize(30)
   {

   }

   void Label::setFontSize(int size)
   {
      myFontSize = size;
   }

   int Label::fontSize()
   {
      return myFontSize;
   }

   void Label::setPosition(float x, float y)
   {
      myPositionX = x;
      myPositionY = y;
   }


   void Label::initializeGeometry()
   {
      FontManager& fontManager = FontManager::instance();

      float x = myPositionX;
      float y = myPositionY;
      float scale = myFontSize / 100.0;
      for (const char& c : myText)
      {
         Node* node = new Node();
         Geometry* geometry = new Geometry();
         Material* material = new Material();
         material->stateSet()->setProgram(new Program("../data/shader/text.vert", "../data/shader/text.frag"));
         material->stateSet()->renderState()->depthTest().setEnabled(false);
         geometry->setMaterial(material);
         FontManager::CharacterMetric& metric = fontManager.metric(c);
         material->setTexture(metric.myTexture, "fontTex");

         float xPos = x + metric.myBearing.x() * scale;
         float yPos = y - ( (metric.mySize.y() - metric.myBearing.y()) * scale);
         float width = metric.mySize.x() * scale;
         float height = metric.mySize.y() * scale;

         ArrayVec4 vert;
         vert.add(Vector4f(xPos, yPos + height, 0, 0));
         vert.add(Vector4f(xPos, yPos, 0, 1));
         vert.add(Vector4f(xPos + width, yPos, 1, 1));
         vert.add(Vector4f(xPos, yPos + height, 0, 0));
         vert.add(Vector4f(xPos + width, yPos, 1, 1));
         vert.add(Vector4f(xPos + width, yPos + height, 1, 0));



         geometry->addVertexAttribute(0, &vert);
         geometry->addPrimitiveSet(Drawable::TRIANGLES, 0, 6);

         x +=  ( metric.myAdvance   >> 6 ) * scale;

         node->addDrawable(geometry);

         myNode->addChild(node);
      }  
      
      
   }
}