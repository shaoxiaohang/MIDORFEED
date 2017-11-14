#pragma once

#include <vector>

namespace vrv
{
	class Geometry;
	class PostProcessor;
	class FrameBuffer;
	class PostProcessorManager
	{
	public:
		typedef std::vector<PostProcessor*> PostProcessorVector;
	public:
		PostProcessorManager();
		void addProcessor(PostProcessor* postProcessor);
		void run(FrameBuffer* framBuffer);
	protected:
		PostProcessorVector myPostProcessors;
		Geometry* myQuadGeometry;
	};
}