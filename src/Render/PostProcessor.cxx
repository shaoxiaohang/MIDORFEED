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
namespace vrv
{
	PostProcessor::PostProcessor()
	{}

	DefaultPostProcessor::DefaultPostProcessor()
	{
		myRenderState = new RenderState;
		//myRenderState->depthTest().setEnabled(false);
	}

	void DefaultPostProcessor::run(Drawable* geometry, FrameBuffer* frameBuffer)
	{
		geometry->setProgram(ShaderManager::instance().getProgram(ShaderManager::DefaultQuadShader));
		geometry->setRenderState(myRenderState);
		myRenderState->apply();
		Uniform* texture = geometry->drawState()->program()->getUniform("scene");
		if (texture)
		{
			texture->set(0);

			texture->synGL();
		}

		geometry->drawImplementation();
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