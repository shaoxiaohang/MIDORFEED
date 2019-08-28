#pragma once

#include <Render/Node.h>

namespace vrv
{
   class Drawable;
   class GeometryNode : public Node
   {
   public:

      typedef std::vector<Drawable*> DrawableList;

      void addDrawable(Drawable* drawable);

      unsigned int numberOfDrawable();

      Drawable* getDrawable(unsigned int i);
   };
}