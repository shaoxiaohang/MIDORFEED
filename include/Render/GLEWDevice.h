#pragma once

#include <Render/Device.h>
#include <Core/Singleton.h>

namespace vrv
{
	class GLEWDevice : public Device, public Singleton<GLEWDevice>
	{
		friend class Viewer;

	public:
		virtual GraphicsWindow* createGraphcisWindow(WindowConfiguration cofig);
		virtual Program* createProgram(const std::string& vertFile, const std::string& fragFile);
	protected:
		GLEWDevice();
		virtual bool initialize();

	protected:
		bool myGLEWInitialized;
	};
}