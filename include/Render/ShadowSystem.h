#pragma once

namespace vrv
{
	class Light;
	class Scene;
	struct RenderQueue;
	class StateSet;
	class Program;
	class FrameBuffer;
	class Texture2D;

	class ShadowSystem
	{
	public:
		ShadowSystem();

		void setShadowCaster(Light* light);

		Light* shadowCaster();

		void run(RenderQueue*);

		void updateProgram(Program*);

		void initializeFrameBuffer(int width, int height);

		Texture2D* shadowTexture();

	protected:
		Light * myCaster;
      StateSet* myStateSet;
		FrameBuffer* myFrameBuffer;
	};
}