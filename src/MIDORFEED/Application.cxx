#include<MIDORFEED/Application.h>
#include<Render/GLFWGraphicsWindow.h>
#include<Render/GLEWDevice.h>
namespace vrv
{

	Application::Application()
		: myMainWindow(0)
	{	
		myDevice = new GLEWDevice();
	}

	void Application::run()
	{
		myMainWindow->show();
		while (!myMainWindow->shouldClose())
		{
			myMainWindow->pullEvents();
			myMainWindow->swapBuffer();
		}
	}

	void Application::initialize(int _width, int _height, const std::string& _title)
	{
		myDevice->initialize();
		WindowConfiguration config(_width, _height, _title);
		myMainWindow = GLEWDevice::instance().createGraphcisWindow(config);
	}
}