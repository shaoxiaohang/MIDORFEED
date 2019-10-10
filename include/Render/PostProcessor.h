#pragma once

#include <string>

namespace vrv
{
	class FrameBuffer;
	class Drawable;
	class RenderState;
	class Program;
	class StateSet;

	class PostProcessor
	{
	public:
		PostProcessor();
		virtual void run(Drawable* quad, FrameBuffer* frameBuffer);
		void drawQuad(Drawable* quad, FrameBuffer* frameBuffer);
	protected:
      StateSet* myStateSet;
	};

	class DefaultPostProcessor : public PostProcessor
	{
	public:
		DefaultPostProcessor();
	};

	class ConfigurableProcessor : public PostProcessor
	{
	public:
		ConfigurableProcessor();
		void run(Drawable* quad, FrameBuffer* frameBuffer);
		void setPostEffectType(int);
	protected:
		int myPostEffectType;
	};

}