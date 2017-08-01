#include <Render/PostProcessor.h>
#include <Core/NodeVisitor.h>
#include <Core/Node.h>
#include <Render/Program.h>
#include <Render/RenderState.h>
#include <Render/DrawState.h>
#include <Render/Drawable.h>
#include <Render/Shader.h>
#include <Render/ShaderManager.h>
namespace vrv
{
	PostProcessor::PostProcessor(std::string name)
		: myName(name)
	{}

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
				drawable->drawState()->setProgram(ShaderManager::instance().getProgram(ShaderManager::NoLighting));
				drawable->drawState()->setRenderState(myRenderState);
			}
		}
	protected:
		RenderState* myRenderState;
	};

	OutlinePostProcessor::OutlinePostProcessor()
		: PostProcessor("Outline")
	{

	}

	void OutlinePostProcessor::run(Node* root)
	{

	}
}