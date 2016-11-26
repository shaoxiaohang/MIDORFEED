#pragma once

#include <string>
#include <Render/GraphicsWindow.h>

namespace vrv
{
	class GraphicsWindow;

	class Device
	{
	public:

		static Device* instance();

		virtual void initialize() = 0;

		virtual GraphicsWindow* createWindow(int width, int height, const std::string& title,
			GraphicsWindow::WINDOWFLAG = GraphicsWindow::WINDOWED) = 0;
		
	protected:

		Device();

		static Device* myInstance;

	};
}