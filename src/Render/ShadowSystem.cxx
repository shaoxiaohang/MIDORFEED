#include <Render/ShadowSystem.h>
#include <Render/Scene.h>

namespace vrv
{
	ShadowSystem::ShadowSystem()
		: myCaster(0)
	{}

	void ShadowSystem::setShadowCaster(Light* light)
	{
		myCaster = light;
	}

	void ShadowSystem::run(RenderQueue*)
	{

	}
}
