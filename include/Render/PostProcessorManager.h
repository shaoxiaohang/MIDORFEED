#pragma once

#include <vector>

namespace vrv
{
	class PostProcessor;
	class PostProcessorManager
	{
	public:
		typedef std::vector<PostProcessor*> PostProcessorVector;
	public:
		PostProcessorManager();
		void addProcessor(PostProcessor* postProcessor);
		void run();
	protected:
		PostProcessorVector myPostProcessors;
	};
}