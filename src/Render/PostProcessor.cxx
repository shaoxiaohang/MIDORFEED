#include <Render/PostProcessor.h>
#include <Core/NodeVisitor.h>
#include <Core/Node.h>
#include <Render/Program.h>
#include <Render/RenderState.h>
#include <Render/DrawState.h>
#include <Render/Drawable.h>
#include <Render/Shader.h>
#include <Render/ShaderManager.h>
#include <Render/FrameBuffer.h>
#include <Render/QtContext.h>
#include <Render/Scene.h>
#ifdef DrawState
#undef DrawState
#endif
namespace vrv
{
	PostProcessor::PostProcessor()
		: myDrawState(0)
	{
	}

	void PostProcessor::run(Drawable* quad, FrameBuffer* frameBuffer)
	{
		drawQuad(quad, frameBuffer);
	}

	void PostProcessor::drawQuad(Drawable* quad, FrameBuffer* frameBuffer)
	{
		QtContext::instance().glActiveTexture(GL_TEXTURE0 + 0);
		QtContext::instance().glBindTexture(GL_TEXTURE_2D, frameBuffer->textureID());
		myDrawState->program()->set("scene",0);
		quad->drawImplementation(myDrawState);
	}

	DefaultPostProcessor::DefaultPostProcessor()
	{
		myDrawState = new DrawState(ShaderManager::instance().getProgram(ShaderManager::DefaultQuadShader));
	}

	ConfigurableProcessor::ConfigurableProcessor()
		: myPostEffectType(0)
	{
		myDrawState = new DrawState(ShaderManager::instance().getProgram(ShaderManager::ConfigurablePostEffectShader));
	}

	void ConfigurableProcessor::run(Drawable* quad, FrameBuffer* frameBuffer)
	{
		myPostEffectType = Scene::instance().postEffectType();
		myDrawState->program()->set("effectType", myPostEffectType);
		PostProcessor::run(quad, frameBuffer);
	}

	void ConfigurableProcessor::setPostEffectType(int type)
	{
		myPostEffectType = type;
	}


	class OutlineNodeVisitor : public NodeVisitor
	{
	public:
		OutlineNodeVisitor()
		{
			myRenderState = new RenderState();
			myRenderState->stencilTest().setStencilRef(1);
			myRenderState->stencilTest().setStencilFucntion(StencilTest::STENCIL_FUNC_LEQUAL);
		}

		void doSomething(Node* node)
		{
			for (size_t i = 0; i < node->numberOfDrawable(); ++i)
			{
				Drawable* drawable = node->getDrawable(i);
			}
		}
	protected:
		RenderState* myRenderState;
	};
}