#include <Render/Context.h>
#include <Render/RenderState.h>
namespace vrv
{
	Context::Context()
		: myCachedRenderState(new RenderState())
	{
		forceSynRenderState();
	}

	void Context::draw(const RenderState& renderState)
	{
		myCachedRenderState->applyIfChanged(renderState);
	}

	void Context::forceSynRenderState()
	{
		myCachedRenderState->apply();
	}
}