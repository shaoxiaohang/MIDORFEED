#pragma once
#include <Render/Array.h>
namespace vrv
{
   class Geometry;
   class Texture2D;
   class StateSet;
   class FrameBuffer;
   class GaussianBlur
   {
   public:
      GaussianBlur(int width, int height, int Filtersize, ArrayFloat filters, int times);

      Texture2D* blur(Texture2D* orig);

   protected:
      Geometry* myQuadGeometry;
      int myFilterSize;
      ArrayFloat myFilters;
      int myFilterTime;
      StateSet* myStateSet;
      FrameBuffer* myPingFrameBuffer;
      FrameBuffer* myPongFrameBuffer;
      int myWidth;
      int myHeight;
   };
}