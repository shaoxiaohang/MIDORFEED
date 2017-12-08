#pragma once

namespace vrv
{
	class Light;
	class Scene;
	class RenderQueue;
	class DrawState;

	class ShadowSystem
	{
	public:
		ShadowSystem();

		void setShadowCaster(Light* light);

		void run(RenderQueue*);

		void updateProgram();

	protected:
		Light * myCaster;
		DrawState* myDrawState;
	};
}