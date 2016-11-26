#pragma once

#include <Render/Device.h>

namespace vrv
{
	class GLEWDevice : public Device
	{
	public:
		GLEWDevice();

		virtual void initialize();

		virtual GraphicsWindow* createWindow(int width, int height, const std::string& title,
			GraphicsWindow::WINDOWFLAG = GraphicsWindow::WINDOWED);
	};
}