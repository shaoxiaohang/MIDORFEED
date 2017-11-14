#include <Render/PostProcessorManager.h>
#include <Render/FrameBuffer.h>
#include <Render/Geometry.h>
#include <Render/PostProcessor.h>
#include <Render/QtContext.h>
namespace vrv
{
	PostProcessorManager::PostProcessorManager()
	{
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

		addProcessor(new DefaultPostProcessor());
	}

	void PostProcessorManager::addProcessor(PostProcessor* postProcessor)
	{
		myPostProcessors.push_back(postProcessor);
	}

	void PostProcessorManager::run(FrameBuffer* frameBuffer)
	{
		frameBuffer->unbind();

		QtContext::instance().glActiveTexture(GL_TEXTURE0 + 0);
		QtContext::instance().glBindTexture(GL_TEXTURE_2D, frameBuffer->textureID());



		QtContext::instance().glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		QtContext::instance().glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < myPostProcessors.size();++i)
		{
			myPostProcessors[i]->run(myQuadGeometry,frameBuffer);
		}
	}
}