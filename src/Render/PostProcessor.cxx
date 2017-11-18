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
namespace vrv
{
	PostProcessor::PostProcessor()
		: myProgram(0)
	{
		myRenderState = new RenderState();
	}

	void PostProcessor::run(Drawable* quad, FrameBuffer* frameBuffer)
	{
		drawQuad(quad, frameBuffer);
	}

	void PostProcessor::drawQuad(Drawable* quad, FrameBuffer* frameBuffer)
	{
		QtContext::instance().glActiveTexture(GL_TEXTURE0 + 0);
		QtContext::instance().glBindTexture(GL_TEXTURE_2D, frameBuffer->textureID());

		quad->setProgram(myProgram);
		quad->setRenderState(myRenderState);
		myRenderState->apply();

		Uniform* texture = myProgram->getUniform("scene");
		if (texture)
		{
			texture->set(0);
			texture->synGL();
		}

		quad->drawImplementation();
	}

	DefaultPostProcessor::DefaultPostProcessor()
	{
		myProgram = ShaderManager::instance().getProgram(ShaderManager::DefaultQuadShader);
	}

	ConfigurableProcessor::ConfigurableProcessor()
		: myPostEffectType(0)
	{
		myProgram = ShaderManager::instance().getProgram(ShaderManager::ConfigurablePostEffectShader);
	}

	void ConfigurableProcessor::run(Drawable* quad, FrameBuffer* frameBuffer)
	{
		myPostEffectType = Scene::instance().postEffectType();
		Uniform* type = myProgram->getUniform("effectType");
		myProgram->use();
		if (type)
		{
			type->set(myPostEffectType);
			type->synGL();
		}

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
				drawable->setProgram(ShaderManager::instance().getProgram(ShaderManager::OutLineObject));
				drawable->setRenderState(myRenderState);
			}
		}
	protected:
		RenderState* myRenderState;
	};
}