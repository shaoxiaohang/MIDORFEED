#include <Render/Context.h>
#include <Render/RenderState.h>
#include <Render/Drawable.h>
#include <Render/DrawState.h>
namespace vrv
{
	Context::Context()
		: myCachedRenderState(new RenderState())
	{
		forceSynRenderState();
	}

	void Context::draw(Drawable* drawable)
	{
		myCachedRenderState->applyIfChanged(drawable->drawState()->renderState());
		drawable->drawImplementation();
	}

	void Context::forceSynRenderState()
	{
		myCachedRenderState->apply();
	}
}