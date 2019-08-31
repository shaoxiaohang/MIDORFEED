#pragma once

namespace vrv
{
	class Light;
	class Scene;
	struct RenderQueue;
	class DrawState;
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
		DrawState* myDrawState;
		FrameBuffer* myFrameBuffer;
	};
}