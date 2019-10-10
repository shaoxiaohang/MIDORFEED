#include <Render/ShadowSystem.h>
#include <Render/Scene.h>
#include <Render/StateSet.h>
#include <Render/Program.h>
#include <Render/Light.h>
#include <Render/FrameBuffer.h>
#include <Render/Texture2D.h>
#include <Render/OpenGLContext.h>

namespace vrv
{
	ShadowSystem::ShadowSystem()
		: myCaster(0)
		, myFrameBuffer(0)
	{
		myStateSet = new StateSet(new Program("../data/shader/shadow.vert", "../data/shader/shadow.frag"));
	}

	void ShadowSystem::setShadowCaster(Light* light)
	{
		myCaster = light;
	}

	Light* ShadowSystem::shadowCaster()
	{
		return myCaster;
	}

	void ShadowSystem::run(RenderQueue* renderQueue)
	{
		if (myCaster)
		{
			myFrameBuffer->bind();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Program* program = myStateSet->program();
			updateProgram(program);

			RenderQueue::RenderList::iterator itor = renderQueue->myOpaqueList.begin();
			RenderQueue::RenderList::iterator end = renderQueue->myOpaqueList.end();
			for (; itor != end; ++itor)
			{
				renderQueue->updateModelMatrix(*itor);
				renderQueue->draw(*itor);
			}

			itor = renderQueue->myTransparentList.begin();
			end = renderQueue->myTransparentList.end();
			for (; itor != end; ++itor)
			{
				renderQueue->updateModelMatrix(*itor);
				renderQueue->draw(*itor);
			}

			myFrameBuffer->unbind();
		}
	}

	void ShadowSystem::updateProgram(Program* program)
	{
		Matrix4f s = myCaster->shadowMatrix();
		program->set("shadow_matrix", s);
	}

	void ShadowSystem::initializeFrameBuffer(int width, int height)
	{
		myFrameBuffer = new FrameBuffer(width, height);
		myFrameBuffer->addAttachment(new FrameBufferAttachment(width, height, FrameBufferAttachment::Texture,
			FrameBufferAttachment::Color, Texture::FLOAT16));
		myFrameBuffer->addAttachment(new FrameBufferAttachment(width, height, FrameBufferAttachment::RenderBuffer,
			FrameBufferAttachment::Depth_Stencil, FrameBufferAttachment::DEPTH24_STENCIL8));
		myFrameBuffer->initialize();

		if (myFrameBuffer->textureBuffer())
		{
			myFrameBuffer->textureBuffer()->setTextureWrapMode(Texture::CLAMP_TO_BORDER);
			myFrameBuffer->textureBuffer()->setBorderColor(Vector4f(1, 1, 1, 1));
		}

	}

	Texture2D* ShadowSystem::shadowTexture()
	{
		return myFrameBuffer->getColorAttachment(0)->textureBuffer();
	}

}
