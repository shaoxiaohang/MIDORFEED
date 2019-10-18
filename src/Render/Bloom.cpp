#include <Render/Bloom.h>
#include <Render/GaussianBlur.h>
#include <Render/Geometry.h>
#include <Render/StateSet.h>
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
      filters.add(0.227027f);
      filters.add(0.1945946f);
      filters.add(0.1216216f);
      filters.add(0.054054f);
      filters.add(0.016216f);

      myGaussianBlur = new GaussianBlur(myWidth, myHeight, 5, filters, 5);

      RenderState* renderState = new RenderState();
      renderState->depthTest().setEnabled(false);
      myStateSet = new StateSet(renderState
         , new Program("../data/shader/defaultQuad.vert", "../data/shader/bloom.frag"));

      myQuadGeometry = new Geometry();
      ArrayVec2* pos = new ArrayVec2(4);
      pos->add(Vector2f(-1, -1));
      pos->add(Vector2f(1, -1));
      pos->add(Vector2f(1, 1));
      pos->add(Vector2f(-1, 1));
      myQuadGeometry->addVertexAttribute(0, pos);

      ArrayVec2* tex = new ArrayVec2(4);
      tex->add(Vector2f(0, 0));
      tex->add(Vector2f(1, 0));
      tex->add(Vector2f(1, 1));
      tex->add(Vector2f(0, 1));

      myQuadGeometry->addVertexAttribute(1,tex);
      myQuadGeometry->addPrimitiveSet(Drawable::QUADS, 0, 4);
   }

   void Bloom::run(FrameBuffer* frameBuffer, Texture2D* frag, Texture2D* highLight)
   {
      Texture2D* blur = myGaussianBlur->blur(highLight);

      frameBuffer->bind();
      Program* program = myStateSet->program();
      frag->bindToPoint(0);
      blur->bindToPoint(1);
      program->set("fragColor", 0);
      program->set("highLightColor", 1);
      myQuadGeometry->drawImplementation();
   }
}