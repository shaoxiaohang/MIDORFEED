#include <Render/GLEWDevice.h>
#define  GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Render/GLFWGraphicsWindow.h>
#include <Render/Program.h>
#include <Core/UsefulMarco.h>

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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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
				glewExperimental = GL_TRUE;
				if (glewInit() == GLEW_OK)
				{
					myGLEWInitialized = true;
				}
				else
				{
					VRV_ERROR("glew initialized failed!")
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

	Program* GLEWDevice::createProgram(const std::string& vertFile, const std::string& fragFile)
	{
		return new Program(vertFile, fragFile);
	}
}