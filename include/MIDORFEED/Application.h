#pragma once

#include<string>
#include<Render/GraphicsWindow.h>

namespace vrv
{
	class Device;
	class GraphicsWindow;

	class Application
	{
	public:

		Application(int width, int height, const std::string& title, 
					GraphicsWindow::WINDOWFLAG flag = GraphicsWindow::WINDOWED);

		~Application();

		virtual void run();

	protected:
		Device* myDevice;
		GraphicsWindow* myWindow;
	};
}