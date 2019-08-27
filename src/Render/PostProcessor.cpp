#include <Render/PostProcessor.h>
#include <Core/NodeVisitor.h>
#include <Core/Node.h>
#include <Render/Program.h>
#include <Render/RenderState.h>
#include <Render/DrawState.h>
#include <Render/Drawable.h>
#include <Render/Shader.h>
#include <Render/FrameBuffer.h>
#include <Render/Scene.h>
#include <Render/FrameBuffer.h>
#include <Render/Texture2D.h>
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
		frameBuffer->textureBuffer(0)->bindToPoint(0);
		myDrawState->program()->set("scene",0);
		quad->drawImplementation(myDrawState);
	}

	DefaultPostProcessor::DefaultPostProcessor()
	{
		RenderState* renderState = new RenderState();
		renderState->depthTest().setEnabled(false);
		myDrawState = new DrawState(renderState
			,new Program("../data/shader/defaultQuad.vert", "../data/shader/defaultQuad.frag"));
	}

	ConfigurableProcessor::ConfigurableProcessor()
		: myPostEffectType(0)
	{
		myDrawState = new DrawState(new Program("../data/shader/configurablePostEffect.vert",
			"../data/shader/configurablePostEffect.frag"));
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