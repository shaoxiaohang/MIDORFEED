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
      friend class DtGuiManager;

      Widget(Widget* parent);

      virtual void initialize() = 0;

   protected:
      
      
      virtual void initializeGeometry() = 0;
      Node* node();

   protected:
      Widget* myParent;
      Vector2f myPosition;
      float myWidth;
      float myHeight;
      Node* myNode;
      Geometry* myGeometry;
      Matrix3f myTransform;
      bool myInitialized;
      Material* myMaterial;
   };
}