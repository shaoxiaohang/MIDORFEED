#include <Render/Context.h>
#include <Render/RenderState.h>
#include <Render/Drawable.h>
#include <Render/DrawState.h>
#include <Render/ClearState.h>
#include <Render/Scene.h>
namespace vrv
{
	Context::Context()
		: myCachedRenderState(new RenderState())
		, myCachedClearState(new ClearState())
		, myScene(0)
	{
		//nop
	}

	void Context::draw(RenderInfo& renderInfo)
	{
		renderInfo.drawable->buildGeometryIfNeeded();
		myCachedRenderState->applyIfChanged(renderInfo.drawable->drawState()->renderState());
		renderInfo.drawable->drawState()->update(myScene, renderInfo);
		renderInfo.drawable->drawImplementation();
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