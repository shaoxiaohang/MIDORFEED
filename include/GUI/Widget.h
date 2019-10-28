#pragma once

#include <Core/Vector2f.h>
#include <Core/Matrix3f.h>
namespace vrv
{
   class Geometry;
   class Node;
   class Material;
   class Widget
   {
   public:
      friend class GuiManager;

      Widget(Widget* parent);

      virtual void initialize();

   protected:
      
      
      virtual void initializeGeometry() = 0;
      Node* node();

   protected:
      Widget* myParent;
      Vector2f myPosition;
      float myWidth;
      float myHeight;
      Node* myNode;
      Matrix3f myTransform;
      bool myInitialized;
      Material* myMaterial;
   };
}