#include <Render/PostProcessorManager.h>
#include <Render/FrameBuffer.h>
#include <Render/DrawState.h>
#include <Render/Geometry.h>
#include <Render/PostProcessor.h>
#include <Render/RenderState.h>
#include <Render/Program.h>
#include <Render/OpenGLContext.h>
namespace vrv
{
	PostProcessorManager::PostProcessorManager(int width, int height)
	{
		myFrameBuffer = new FrameBuffer(width, height);
		myFrameBuffer->addAttachment(new FrameBufferAttachment(width, height, FrameBufferAttachment::Texture,
			FrameBufferAttachment::Color, Texture::FLOAT16), 0);
		myFrameBuffer->addAttachment(new FrameBufferAttachment(width, height, FrameBufferAttachment::RenderBuffer,
			FrameBufferAttachment::Depth_Stencil, FrameBufferAttachment::DEPTH24_STENCIL8));
		myFrameBuffer->initialize();

		myRenderState = new RenderState;
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

		myDefaultProcessor = new DefaultPostProcessor();

	}

	void PostProcessorManager::addProcessor(PostProcessor* postProcessor)
	{
		myPostProcessors.push_back(postProcessor);
	}


	void PostProcessorManager::run()
	{
		for (int i = 0; i < myPostProcessors.size(); ++i)
		{
			myPostProcessors[i]->run(myQuadGeometry, myFrameBuffer);
		}

		myFrameBuffer->unbind();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myDefaultProcessor->run(myQuadGeometry, myFrameBuffer);
	}

	void PostProcessorManager::bind()
	{
		myFrameBuffer->bind();
	}

	void PostProcessorManager::unbind()
	{
		myFrameBuffer->unbind();
	}

	FrameBuffer* PostProcessorManager::frameBuffer()
	{
		return myFrameBuffer;
	}
}