#include <MIDORFEED/Application.h>
#include <Render/GLEWDevice.h>
#include <Render/GLFWGraphicsWindow.h>
 
namespace vrv
{
	Application::Application(int width, int height, 
							const std::string& title,GraphicsWindow::WINDOWFLAG flag)
	{
		myDevice = new GLEWDevice();
		myDevice->initialize();
		myWindow = myDevice->createWindow(width, height, title, flag);
	}

	Application::~Application()
	{
		delete myWindow;
	}

	void Application::run()
	{
		while (!myWindow->isClosed())
		{
			myWindow->pollEvents();
			myWindow->swapBuffers();
		}
	}
}