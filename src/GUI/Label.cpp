#include <GUI/Label.h>
#include <Render/Program.h>
#include <Render/Material.h>
#include <Render/StateSet.h>
#include <Render/Geometry.h>
#include <GUI/FontManager.h>

namespace vrv
{
   void Label::setText(const std::string& text)
   {
      myText = text;
   }

   Label::Label(Widget* parent)
      : Widget(parent)
   {

   }

   void Label::initializeGeometry()
   {
      myMaterial->stateSet()->setProgram(new Program("../data/shader/label.vert", "../data/shader/label.frag"));

      FontManager& fontManager = FontManager::instance();

      float x = 0;
      float y = 0;
      for (const char& c : myText)
      {
         Node* node = new Node();
         Geometry* geometry = new Geometry();
         geometry->setMaterial(myMaterial);
         FontManager::CharacterMetric& metric = fontManager.metric(c);

         float xPos = x + metric.myBearing.x();
         float yPos = y - (metric.mySize.y() - metric.myBearing.y());
         float width = metric.mySize.x();
         float height = metric.mySize.y();

         ArrayVec4 vert;
         vert.add(Vector4f(xPos, yPos, 0, 0));
         vert.add(Vector4f(xPos + width, yPos, 1, 0));
         vert.add(Vector4f(xPos, yPos + height, 0, 1));
         vert.add(Vector4f(xPos, yPos + height, 0, 1));
         vert.add(Vector4f(xPos + width, yPos, 1, 0));
         vert.add(Vector4f(xPos + width, yPos + height, 1, 1));

         geometry->addVertexAttribute(0, &vert);

         x += metric.myAdvance >> 6;

         node->addDrawable(geometry);

         myNode->addChild(node);
      }  
      
      
   }
}