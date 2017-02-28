#include <Render/GLEWDevice.h>
#define  GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Render/GLFWGraphicsWindow.h>

namespace vrv
{
	GLEWDevice* Singleton<GLEWDevice>::myInstance = 0;

	GLEWDevice::GLEWDevice()
		: Device(), Singleton<GLEWDevice>()
		, myGLEWInitialized(false)
	{
		
	}

	bool GLEWDevice::initialize()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return true;
	}

	GraphicsWindow* GLEWDevice::createGraphcisWindow(WindowConfiguration config)
	{
		GLFWGraphicsWindow* window = new GLFWGraphicsWindow(config);
		if (window->initialize())
		{
			if (!myGLEWInitialized)
			{
				window->makeContexCurrent();
				glewExperimental = true;
				if (glewInit() == GLEW_OK)
				{
					myGLEWInitialized = true;
				}
			}
			return window;
		}
		else
		{
			delete window;
			return 0;
		}
	}
}