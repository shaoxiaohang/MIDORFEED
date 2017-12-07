#include <Render/Context.h>
#include <Render/RenderState.h>
#include <Render/Drawable.h>
#include <Render/DrawState.h>
#include <Render/ClearState.h>
#include <Render/Scene.h>
#include <Render/Program.h>
namespace vrv
{
	Context::Context()
		: myCachedRenderState(new RenderState())
		, myCachedClearState(new ClearState())
		, myScene(0)
	{
		//nop
	}

	void Context::draw(RenderInfo& renderInfo, DrawState* drawState)
	{
		Program* program = drawState->program();
		myCachedRenderState->applyIfChanged(drawState->renderState());
		program->set("vrv_model_matrix", renderInfo.myModelMatrix);
		renderInfo.myDrawable->updateProgram(program);
		renderInfo.myDrawable->drawImplementation(drawState);
	}

	void Context::forceSynGL()
	{
		myCachedRenderState->apply();
		myCachedClearState->apply();
	}

	void Context::clear(ClearState* clear)
	{
		myCachedClearState->applyIfChanged(*clear);
		myCachedClearState->clear();
	}

	void Context::setScene(Scene* scene)
	{
		myScene = scene;
	}

}