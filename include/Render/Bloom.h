#pragma once

namespace vrv
{
   class Geometry;
   class DrawState;
   class Texture2D;
   class GaussianBlur;
   class FrameBuffer;
   class Bloom
   {
   public:
      Bloom(int width, int height);

      void run(FrameBuffer* frameBuffer, Texture2D* frag, Texture2D* highLight);

   protected:
      int myWidth;
      int myHeight;
      GaussianBlur* myGaussianBlur;
      Geometry* myQuadGeometry;
      DrawState* myDrawState;
   };
}