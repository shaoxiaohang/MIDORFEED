#include <Render/PostProcessorManager.h>
#include <Render/FrameBuffer.h>
#include <Render/DrawState.h>
#include <Render/Geometry.h>
#include <Render/PostProcessor.h>
#include <Render/QtContext.h>
#include <Render/RenderState.h>
#include <Render/ShaderManager.h>
#include <Render/Program.h>
namespace vrv
{
	PostProcessorManager::PostProcessorManager(int width, int height)
	{
		myFrameBuffer = new FrameBuffer(width, height);

		myRenderState = new RenderState;
		myQuadGeometry = new Geometry();
		ArrayVec3* pos = new ArrayVec3();
		pos->add(Vector3f(-1, -1,0));
		pos->add(Vector3f(1, -1,0));
		pos->add(Vector3f(1, 1,0));
		pos->add(Vector3f(-1, 1,0));
		myQuadGeometry->setVertex(pos);

		ArrayVec2* tex = new ArrayVec2();
		tex->add(Vector2f(0, 0));
		tex->add(Vector2f(1, 0));
		tex->add(Vector2f(1, 1));
		tex->add(Vector2f(0, 1));

		myQuadGeometry->setTextureCoordinate(tex);
		myQuadGeometry->addPrimitiveSet(Drawable::QUADS, 0,4);
		myQuadGeometry->buildGeometry();

		myDefaultProcessor = new DefaultPostProcessor();

		addProcessor(new ConfigurableProcessor);
	}

	void PostProcessorManager::addProcessor(PostProcessor* postProcessor)
	{
		myPostProcessors.push_back(postProcessor);
	}


	void PostProcessorManager::run()
	{
		for (int i = 0; i < myPostProcessors.size();++i)
		{
			 myPostProcessors[i]->run(myQuadGeometry,myFrameBuffer);
		}

		myFrameBuffer->unbind();
		myDefaultProcessor->run(myQuadGeometry, myFrameBuffer);
	}

	void PostProcessorManager::bind()
	{
		myFrameBuffer->bind();
	}
}