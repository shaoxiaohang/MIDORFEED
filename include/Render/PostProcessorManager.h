#pragma once

#include <vector>

namespace vrv
{
	class Geometry;
	class PostProcessor;
	class FrameBuffer;
	class RenderState;
	class PostProcessorManager
	{
	public:
		typedef std::vector<PostProcessor*> PostProcessorVector;
	public:
		PostProcessorManager(int width, int height);
		void addProcessor(PostProcessor* postProcessor);
		void run();
		void bind();
	protected:
		PostProcessorVector myPostProcessors;
		Geometry* myQuadGeometry;
		RenderState* myRenderState;
		FrameBuffer* myFrameBuffer;
		PostProcessor* myDefaultProcessor;
	};
}