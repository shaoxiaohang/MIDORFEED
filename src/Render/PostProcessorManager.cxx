#include <Render/PostProcessorManager.h>

namespace vrv
{
	PostProcessorManager::PostProcessorManager()
	{

	}

	void PostProcessorManager::addProcessor(PostProcessor* postProcessor)
	{
		myPostProcessors.push_back(postProcessor);
	}

	void PostProcessorManager::run()
	{
	}
}