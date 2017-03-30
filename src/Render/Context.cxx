#include <Render/Context.h>
#include <Render/RenderState.h>
#include <Render/Drawable.h>
#include <Render/DrawState.h>
#include <Render/ClearState.h>
namespace vrv
{
	Context::Context()
		: myCachedRenderState(new RenderState())
		, myCachedClearState(new ClearState())
		, myScene(0)
	{
	
	}

	void Context::draw(Drawable* drawable)
	{
		drawable->buildGeometryIfNeeded();
		myCachedRenderState->applyIfChanged(drawable->drawState()->renderState());
		drawable->drawState()->update(myScene);
		drawable->drawImplementation();
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