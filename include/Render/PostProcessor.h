#pragma once

#include <string>

namespace vrv
{
	class FrameBuffer;
	class Drawable;
	class RenderState;

	class PostProcessor
	{
	public:
		PostProcessor();
		virtual void run(Drawable*, FrameBuffer* frameBuffer) = 0;
	protected:
	};

	class DefaultPostProcessor : public PostProcessor
	{
	public:
		DefaultPostProcessor();
		void run(Drawable*, FrameBuffer* frameBuffer);
	protected:
		RenderState* myRenderState;
	};


}