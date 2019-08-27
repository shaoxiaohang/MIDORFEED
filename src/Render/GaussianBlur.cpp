#include <Render/GaussianBlur.h>
#include <Render/Geometry.h>
#include <Render/DrawState.h>
#include <Render/Program.h>
#include <Render/RenderState.h>
#include <Render/FrameBuffer.h>
#include <Render/Texture2D.h>
#include <sstream>

namespace vrv
{
   GaussianBlur::GaussianBlur(int width, int height, int Filtersize, ArrayFloat filters, int times)
      : myFilterSize(Filtersize)
      , myFilters(filters)
      , myFilterTime(times)
      , myWidth(width)
      , myHeight(height)
   {
      RenderState* renderState = new RenderState();
      renderState->depthTest().setEnabled(false);
      myDrawState = new DrawState(renderState
         , new Program("../data/shader/defaultQuad.vert", "../data/shader/gaussianBlur.frag"));
      myPingFrameBuffer = new FrameBuffer(myWidth, myHeight);
      myPongFrameBuffer = new FrameBuffer(myWidth, myHeight);
      FrameBufferAttachment* attatchment1 = new FrameBufferAttachment(myWidth, myHeight, FrameBufferAttachment::Texture,
         FrameBufferAttachment::Color, Texture::FLOAT16);
      FrameBufferAttachment* attatchment2 = new FrameBufferAttachment(myWidth, myHeight, FrameBufferAttachment::Texture,
         FrameBufferAttachment::Color, Texture::FLOAT16);
      myPingFrameBuffer->addAttachment(attatchment1);
      myPingFrameBuffer->initialize();
      myPongFrameBuffer->addAttachment(attatchment2);
      myPongFrameBuffer->initialize();

      myQuadGeometry = new Geometry();
      ArrayVec2* pos = new ArrayVec2();
      pos->add(Vector2f(-1, -1));
      pos->add(Vector2f(1, -1));
      pos->add(Vector2f(1, 1));
      pos->add(Vector2f(-1, 1));
      myQuadGeometry->setVertex(pos);

      ArrayVec2* tex = new ArrayVec2();
      tex->add(Vector2f(0, 0));
      tex->add(Vector2f(1, 0));
      tex->add(Vector2f(1, 1));
      tex->add(Vector2f(0, 1));

      myQuadGeometry->setTextureCoordinate(tex);
      myQuadGeometry->addPrimitiveSet(Drawable::QUADS, 0, 4);
      myQuadGeometry->buildGeometry();
   }

   Texture2D* GaussianBlur::blur(Texture2D* texture)
   {
      Program* program = myDrawState->program();
      program->set("texture", 0);
      program->set("filterSize", myFilterSize );
      for (int i=0; i < myFilterSize; ++i)
      {
         std::stringstream ss;
         ss << "weight[" << i << "]";
         std::string weight = ss.str();
         program->set(weight, myFilters.get(i));
      }


      for (int i = 0; i < myFilterTime; ++i)
      {
         myPingFrameBuffer->bind();
         program->set("horizontal", true);
         if (i == 0)
         {
            texture->bindToPoint(0);
         }
         else
         {
            myPongFrameBuffer->textureBuffer()->bindToPoint(0);
         }
         myQuadGeometry->drawImplementation(myDrawState);

         myPongFrameBuffer->bind();
         program->set("horizontal", false);
         myPingFrameBuffer->textureBuffer()->bindToPoint(0);
         
         myQuadGeometry->drawImplementation(myDrawState);
      }

      myPongFrameBuffer->unbind();

      return myPongFrameBuffer->textureBuffer();

   }
}