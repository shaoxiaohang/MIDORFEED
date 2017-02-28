#pragma once

#include <Render/Device.h>
#include <Core/Singleton.h>

namespace vrv
{
	class GLEWDevice : public Device, public Singleton<GLEWDevice>
	{
		friend class Application;

	public:
		virtual GraphicsWindow* createGraphcisWindow(WindowConfiguration cofig);
	protected:
		GLEWDevice();
		virtual bool initialize();

	protected:
		bool myGLEWInitialized;
	};
}