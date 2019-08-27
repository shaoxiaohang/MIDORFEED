#include <Render/Bloom.h>
#include <Render/GaussianBlur.h>
#include <Render/Geometry.h>
#include <Render/DrawState.h>
#include <Render/Program.h>
#include <Render/RenderState.h>
#include <Render/Texture2D.h>
#include <Render/FrameBuffer.h>
namespace vrv
{
   Bloom::Bloom(int width, int height)
      : myWidth(width)
      , myHeight(height)
   {
      ArrayFloat filters(5);
      filters.add(0.227027);
      filters.add(0.1945946);
      filters.add(0.1216216);
      filters.add(0.054054);
      filters.add(0.016216);

      myGaussianBlur = new GaussianBlur(myWidth, myHeight, 5, filters, 5);

      RenderState* renderState = new RenderState();
      renderState->depthTest().setEnabled(false);
      myDrawState = new DrawState(renderState
         , new Program("../data/shader/defaultQuad.vert", "../data/shader/bloom.frag"));

      myQuadGeometry = new Geometry();
      ArrayVec2* pos = new ArrayVec2(4);
      pos->add(Vector2f(-1, -1));
      pos->add(Vector2f(1, -1));
      pos->add(Vector2f(1, 1));
      pos->add(Vector2f(-1, 1));
      myQuadGeometry->setVertex(pos);

      ArrayVec2* tex = new ArrayVec2(4);
      tex->add(Vector2f(0, 0));
      tex->add(Vector2f(1, 0));
      tex->add(Vector2f(1, 1));
      tex->add(Vector2f(0, 1));

      myQuadGeometry->setTextureCoordinate(tex);
      myQuadGeometry->addPrimitiveSet(Drawable::QUADS, 0, 4);
      myQuadGeometry->buildGeometry();
   }

   void Bloom::run(FrameBuffer* frameBuffer, Texture2D* frag, Texture2D* highLight)
   {
      Texture2D* blur = myGaussianBlur->blur(highLight);

      frameBuffer->bind();
      Program* program = myDrawState->program();
      frag->bindToPoint(0);
      blur->bindToPoint(1);
      program->set("fragColor", 0);
      program->set("highLightColor", 1);
      myQuadGeometry->drawImplementation(myDrawState);
   }
}