#pragma once

namespace vrv
{
	class Light;
	class Scene;
	class RenderQueue;

	class ShadowSystem
	{
	public:
		ShadowSystem();

		void setShadowCaster(Light* light);

		void run(RenderQueue*);

	protected:
		Light * myCaster;
	};
}